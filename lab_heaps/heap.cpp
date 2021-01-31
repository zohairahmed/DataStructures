
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2 * currentIdx + 1 - root();
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2 * currentIdx + 2 - root();
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return (currentIdx - 1 + root())/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return currentIdx * 2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (rightChild(currentIdx) >= _elems.size())
      return leftChild(currentIdx);
    if (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]))
      return leftChild(currentIdx);

    return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (!hasAChild(currentIdx)){
      return;
    }
    size_t childIdx = maxPriorityChild(currentIdx);
    if (!higherPriority(_elems[currentIdx], _elems[childIdx])){
      std::swap(_elems[currentIdx], _elems[childIdx]);
      heapifyDown(childIdx);
    }
    // @TODO Implement the heapifyDown algorithm.
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    _elems.push_back(T());
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{

    _elems.push_back(T());

    for (const T& el : elems){
      _elems.push_back(el);
    }
    for (size_t i = _elems.size() - 1; i > 0; i--){
      heapifyDown(i);
    }


    // @TODO Construct a heap using the buildHeap algorithm
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (!empty()){
      T temp = _elems[root()];
      _elems[root()] = _elems.back();
      _elems.pop_back();
      heapifyDown(root());
      return temp;
    }
    // @TODO Remove, and return, the element with highest priority
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (_elems.size() <= root())
      return T();

    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
    // @TODO Add elem to the heap
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    if (elem > _elems[idx]){
      _elems[idx] = elem;
      heapifyDown(idx);
      return;
    }
    _elems[idx] = elem;
    heapifyUp(idx);
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() <= root();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
