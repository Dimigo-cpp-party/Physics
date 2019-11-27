#include "Polygon.h"

namespace Physics {

double Area(const points &p) {
  double A = 0.0;
  for(int i=0; i<p.size()-1; ++i) {
    A += p[i].x*p[i+1].y-p[i+1].x*p[i].y;
  }
  return A/2.0;
}

glm::dvec2 COG(const points &p) {
  double x=0.0, y=0.0, A = Area(p)*6.0;
  for(int i=0; i<p.size()-1; ++i) {
    x += (p[i].x + p[i+1].x)*(p[i].x*p[i+1].y-p[i+1].x*p[i].y);
    y += (p[i].y + p[i+1].y)*(p[i].x*p[i+1].y-p[i+1].x*p[i].y);
  }
  return glm::dvec2(x/A, y/A);
}

Polygon::Polygon()
:_p(), _area(0.0) {
  ;
}

Polygon::Polygon(const Physics::points &p)
:_p(p), _area(Area(p)) {
  reorderByCOG();
}

Polygon::Polygon(const Physics::Polygon &other)
:_p(other._p), _area(other._area) {
  ;
}

Polygon::~Polygon() {
  ;
}

Polygon& Polygon::operator=(const Physics::Polygon &other) {
  assert(&other != this);
  this->_p = other._p;
  this->_area = other._area;
  return (*this);
}

void Polygon::setPoint(int idx, const glm::dvec2 p) {
  _p[idx] = p;
  recalculateArea();
  reorderByCOG();
}

void Polygon::setPoints(const Physics::points &p) {
  _p = p;
  recalculateArea();
  reorderByCOG();
}

const glm::vec2 Polygon::getPoint(int idx) const {
  return _p[idx];
}

double Polygon::getArea() const {
  return _area;
}

void Polygon::recalculateArea() {
  _area = Area(_p);
}

void Polygon::reorderByCOG() {
  auto cog = COG(_p);
  for(int i=0; i<_p.size(); ++i) {
    _p[i] = _p[i] - cog;
  }
}

}