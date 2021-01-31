/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include <stack>

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (empty())
    return;

  ListNode * temp = head_;
  ListNode * tempNext;
  while (temp != NULL){
    // if (temp->prev != NULL){
    //   delete temp->prev;
    //   temp->prev = NULL;
    // }
    tempNext = temp->next;
    delete temp;
    temp = NULL;
    temp = tempNext;
  }


  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1

  ListNode * newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = NULL;

  if (head_ != NULL) {
    head_->prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {

  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;
  newNode->prev = tail_;

  if (tail_ != NULL) {
    tail_->next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL && curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (size() < 3)
    return;
  ListNode * first = head_;
  ListNode * second;
  ListNode * third;
  head_ = head_->next;
  for (int i = 0; i < size(); i += 3){
    // assignment of second and third
    if (i + 3 > size())
      return;
    second = first->next;
    // second->prev = first;
    third = second->next;
    // third->prev = second;

    // pointer reassignment
    first->next = third->next;
    if (first->next != NULL){
      first->next->prev = first;
    }
    second->prev = first->prev;
    if (first->prev != NULL)
      first->prev->next = second;
    first->prev = third;
    third->next = first;
    first = first->next;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  // You can use queues and stacks
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  // @todo Graded in MP3.2
  // can use stacks and queues
  if (startPoint == NULL || endPoint == NULL || startPoint == endPoint){
    return;
  }

  ListNode * tempEnd = endPoint->next;
  ListNode * curr = startPoint;
  ListNode * temp = NULL;

  while (curr != tempEnd){
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = curr->prev;
  }

  if (startPoint->next == NULL){
    endPoint->prev = NULL;
  }
  else {
    endPoint->prev = startPoint->next;
    endPoint->prev->next = endPoint;
  }

  if (tempEnd == NULL){
    startPoint->next = NULL;
  }
  else{
    startPoint->next = tempEnd;
    startPoint->next->prev = startPoint;
  }

  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  // @todo Graded in MP3.2

  if (length_ < 2)
    return;

  ListNode * tempStart = head_;
  if (tempStart == NULL){
    return;
  }

  while (tempStart){
    ListNode * tempEnd = tempStart;
    for (int i = 1; i < n; i++){
      if (tempEnd && tempEnd->next)
        tempEnd = tempEnd->next;
    }
    if (head_ == tempStart)
      head_ = tempEnd;

    ListNode * t = tempEnd->next;
    if (t == NULL)
      tail_ = tempStart;
    reverse (tempStart, tempEnd);
    tempStart = t;
  }


}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL && second == NULL)
    return NULL;
  if (first == NULL)
    return second;
  if (second == NULL)
    return first;

  return NULL;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start == NULL || start->next == NULL || chainLength < 2)
    return start;
  return NULL;
}
