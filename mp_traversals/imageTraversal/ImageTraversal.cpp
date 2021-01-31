#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

ImageTraversal::ImageTraversal(const PNG & png, const Point start, double tolerance){
  base_ = png;
  start_ = start;
  tol_ = tolerance;
}

ImageTraversal::Iterator::~Iterator(){
  if (w > 0){
    for (unsigned i = 0; i < w; i++){
      delete[] visited[i];
      // visited[i] = NULL;
    }
    delete[] visited;
    visited = NULL;
  }
}
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

ImageTraversal::Iterator::Iterator(const Point & p, ImageTraversal * t){
  done = false;

  it = t;
  current = it->pop();
  // it->add(current);
  w = it->getBase().width();
  unsigned h = it->getBase().height();

  visited = new bool*[w];
  for (unsigned int i = 0; i < w; i++){
    visited[i] = new bool[h];
    for (unsigned int j = 0; j < h; j++){
      visited[i][j] = false;
    }
  }
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  done = true;
  w = 0;
  /** @todo [Part 1] */
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  // worry about pruning: check if things are visited when popping from the stack.
  // if not, pop and add neighbors.
  // if it is, pop it.
  // != end should handle the edge cases
  // you may need helper functions with this
  // current = it->pop();
  if (!checkVisited(current)){
    Point p2(current.x + 1, current.y);

    if (it->shouldVisit(p2) && !checkVisited(p2)){
      // setVisited(p, true);
      it->add(p2);
    }
    Point p3(current.x, current.y + 1);
    if (it->shouldVisit(p3) && !checkVisited(p3)){
      // setVisited(p, true);
      it->add(p3);
    }

    Point p4(current.x - 1, current.y);
    if (it->shouldVisit(p4) && !checkVisited(p4)){
      // setVisited(p, true);
      it->add(p4);
    }
    Point p5(current.x, current.y - 1);
    if (it->shouldVisit(p5) && !checkVisited(p5)){
      // setVisited(p, true);
      it->add(p5);
    }

    setVisited(current, true);
  }
  if (it->empty()){
    done = true;
    current = it->peek();
  }
  else {
    current = it->pop();
  }
  while (!it->empty() && checkVisited(current)){
    current = it->pop();
  }
  if (it->empty())
    done = true;
    /** @todo [Part 1] */
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  // bool thisEmpty = false;
  // bool otherEmpty = false;
  //
  // if (it == NULL) { thisEmpty = true; }
  // if (other.it == NULL) { otherEmpty = true; }
  //
  // if (!thisEmpty)  { thisEmpty = it->empty(); }
  // if (!otherEmpty) { otherEmpty = other.it->empty(); }
  //
  // if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  // else if ((!thisEmpty)&&(!otherEmpty)) return (it != other.it); //both not empty then compare the traversals
  // else return true; // one is empty while the other is not, return true
  return !(done == other.done);
}

bool ImageTraversal::Iterator::checkVisited(const Point p){
  return visited[p.x][p.y];
}

void ImageTraversal::Iterator::setVisited(const Point p, bool v){
  visited[p.x][p.y] = v;
}

PNG ImageTraversal::getBase() const {
  return base_;
}

Point ImageTraversal::getStart() const {
  return start_;
}

bool ImageTraversal::shouldVisit(const Point p){
  return (p.x < base_.width() && p.y < base_.height() &&
    calculateDelta(base_.getPixel(p.x, p.y), base_.getPixel(start_.x, start_.y)) <= tol_);
}
