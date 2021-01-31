#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance): ImageTraversal(png, start, tolerance) {
  s.push(start);
  /** @todo [Part 1] */
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this->getStart(), this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  s.push(point);
  // do i add the point given to me here?
  // push to the stack in the given order, checking to see if the pixel is already there
  // alternate method, use list to implement stack and use unique?
  /** @todo [Part 1] */
  //pseudocode
  // if (validDelta(pointright) && notVisited(pointright)){
  //   s.push(pointright);
  //   setvisited(pointright);
  // }
  // same for other 3 directions
  //
  //
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  Point p = s.top();
  s.pop();

  /** @todo [Part 1] */
  return p;
}
/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  if (!s.empty())
    return s.top();
  /** @todo [Part 1] */
  return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return s.empty();
}
