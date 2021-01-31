/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    if (!t)
      return;
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here

    Node * tr = t->right;
    t->right = tr->left;
    if (t->right){
      int nhl = heightOrNeg1(t->right->left) + 1;
      int nhr = heightOrNeg1(t->right->right) + 1;
      t->right->height = nhl>nhr? nhl:nhr;
    }
    tr->left = t;

    if (tr->left){
      int nhl = heightOrNeg1(tr->left->left) + 1;
      int nhr = heightOrNeg1(tr->left->right) + 1;
      tr->left->height = nhl>nhr? nhl:nhr;
    }
    t = tr;
    // print();
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    if (!t)
      return;
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here

    Node * tl = t->left;
    t->left = tl->right;
    if (t->left){
      int nhl = heightOrNeg1(t->left->left) + 1;
      int nhr = heightOrNeg1(t->left->right) + 1;
      t->left->height = nhl>nhr? nhl:nhr;
    }
    tl->right = t;

    if (tl->right){
      int nhl = heightOrNeg1(tl->right->left) + 1;
      int nhr = heightOrNeg1(tl->right->right) + 1;
      tl->right->height = nhl>nhr? nhl:nhr;
    }
    t = tl;
    // print();
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  if (subtree){
    int balance = (heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right)) + 1;
    if(balance == 3)
    {
      int lbalance = (heightOrNeg1(subtree->left->left)-heightOrNeg1(subtree->left->right))+1;
      if (lbalance != 2) {
        rotateLeftRight(subtree);
      } else {
        rotateRight(subtree);
      }
    }
    if(balance == -1)
    {
      int rbalance = (heightOrNeg1(subtree->right->left)-heightOrNeg1(subtree->right->right))+1;
      if (rbalance != 0) {
        rotateRightLeft(subtree);
      } else {
        rotateLeft(subtree);
      }
    }
    int nhl = heightOrNeg1(subtree->left) + 1;
    int nhr = heightOrNeg1(subtree->right) + 1;
    subtree->height = nhl>nhr? nhl:nhr;
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  if (subtree == NULL){
    subtree = new Node(key, value);
  }
  else {
    if (subtree->key < key){
      insert(subtree->right, key, value);
      // rebalance(subtree->right);
    }
    else {
      insert(subtree->left, key, value);
      // rebalance(subtree->left);
    }
  }
  rebalance(subtree);
    // your code here
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        // rebalance(subtree->left);
    } else if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        // rebalance(subtree->right);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            clear(subtree);
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node * iop = subtree->left;
            while (iop->right != NULL){
              iop = iop->right;
            }
            swap(subtree, iop);
            remove(subtree->left, key);

            // needs to be finished
            /* two-child remove */
            // your code here
        } else {
            Node * t = NULL;
            if (subtree->left){
              t = subtree->left;
            }
            else {
              t = subtree->right;
            }
            delete subtree;
            subtree = t;
            /* one-child remove */
            // your code here
        }
        // your code here
    }
    rebalance(subtree);
}
