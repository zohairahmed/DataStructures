/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    double firstDim = first[curDim], secondDim = second[curDim];
    if (first[curDim] == second[curDim])
        return first < second;

    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double d1 = 0, d2 = 0;
    for (size_t i = 0; i < Dim; i++){
      d1 += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      d2 += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    /**
     * @todo Implement this function!
     */
     if (d1 == d2){
       return potential < currentBest;
     }
     return d2 < d1;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    if (newPoints.empty()){
      size = 0;
      root = NULL;
      // return *this;
    }
    else {
      size = newPoints.size();
      vector<Point<Dim>> pCopy;
      for (unsigned i = 0; i < size; i++){
        pCopy.push_back(newPoints[i]);
      }
      makeTree(pCopy, 0, size - 1, 0, root);
    }
}

template <int Dim>
void KDTree<Dim>::copy_(const KDTree<Dim> &other){
  size = other.size;
  copyNodes(other.root, root);
}

template <int Dim>
void KDTree<Dim>::copyNodes(const KDTreeNode * sroot, KDTreeNode *& toCopy){
  toCopy = new KDTreeNode(sroot->point);
  copyNodes(sroot->left, toCopy->left);
  copyNodes(sroot->right, toCopy->right);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  copy_(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  clear(root);
  copy_(rhs);

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(root);
  size = 0;
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode *& kdtn){
    if (!kdtn){
      return;
    }
    clear(kdtn->left);
    clear(kdtn->right);
    delete kdtn;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query,
                                            const KDTreeNode * sroot, int d) const
{
    if (!sroot->left && !sroot->right)
        return sroot->point;

    d = d % Dim;
    Point<Dim> currBest;

    KDTreeNode * branched;
    bool isSmaller = smallerDimVal(query, sroot->point, d);
    branched = sroot->left;
    if (isSmaller)
      branched = sroot->right;

    if (isSmaller && sroot->left){
      currBest = findNearestNeighbor(query, sroot->left, d + 1);
    }
    else if (isSmaller){
      currBest = findNearestNeighbor(query, sroot->right, d + 1);
    }
    else if (!isSmaller && sroot->right) {
      currBest = findNearestNeighbor(query, sroot->right, d + 1);
    }
    else if (!isSmaller){
      currBest = findNearestNeighbor(query, sroot->left, d + 1);
    }

    // this should get me to a leaf node, now recurse back up

    if (shouldReplace(query, currBest, sroot->point)){
        currBest = sroot->point;
    }

    double split = (sroot->point[d] - query[d]) * (sroot->point[d] - query[d]);
    double currBestDist = 0;

    for (size_t i = 0; i < Dim; i++){
      currBestDist += (query[i] - currBest[i]) * (query[i] - currBest[i]);
    }

    Point<Dim> possBest = currBest;
    if (currBestDist >= split && branched){
        possBest = findNearestNeighbor(query, branched, d + 1);
    }
    return shouldReplace(query, currBest, possBest)? possBest : currBest;
}

template <int Dim>
int KDTree<Dim>::part(vector<Point<Dim>>& points, int lBound, int pivot, int rBound,
                      int dCount){
    dCount = dCount % Dim;
    Point<Dim> pValue = points[pivot];
    points[pivot] = points[rBound];
    points[rBound] = pValue;
    int storeIndex = lBound;
    for (int i = storeIndex; i < rBound; i++){
      if (smallerDimVal(points[i], pValue, dCount)){ // needs to be changed
        Point<Dim> temp = points[i];
        points[i] = points[storeIndex];
        points[storeIndex] = temp;
        storeIndex++;
      }
    }
    pValue = points[rBound];
    points[rBound] = points[storeIndex];
    points[storeIndex] = pValue;

    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quick(vector<Point<Dim>>& points, int lBound, int k, int rBound,
                        int dCount){
    if (lBound == rBound)
      return points[rBound];

    dCount = dCount % Dim;
    int pIndex = part(points, lBound, (lBound+rBound)/2, rBound, dCount);

    if (k == pIndex)
      return points[k];
    else if (k < pIndex)
      return quick(points, lBound, k, pIndex - 1, dCount);
    else
      return quick(points, pIndex + 1, k, rBound, dCount);

}

template <int Dim>
void KDTree<Dim>::makeTree(vector<Point<Dim>>& points, int lBound, int rBound,
                           int dCount, KDTreeNode *& sroot){
    if (lBound > rBound)
      return;

    dCount = dCount % Dim;
    sroot = new KDTreeNode(quick(points, lBound, (lBound+rBound)/2, rBound, dCount));
    makeTree(points, lBound, (lBound+rBound)/2 - 1, dCount + 1, sroot->left);
    makeTree(points, (lBound+rBound)/2 + 1, rBound, dCount + 1, sroot->right);
}
