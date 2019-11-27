#ifndef PHYSICS_POLYGON_H
#define PHYSICS_POLYGON_H

#include <glm/vec2.hpp>
#include <vector>

namespace Physics {

typedef std::vector<glm::dvec2> points;

double Area(const points &p);

glm::dvec2 COG(const points &p);

class Polygon {
 private:
  points _p;
  double _area;

 public:
  Polygon();

  Polygon(const points &p);

  Polygon(const Polygon &other);

  ~Polygon();

  Polygon &operator=(const Polygon &other);

  void setPoint(int idx, const glm::dvec2 p);

  void setPoints(const points &p);

  const glm::vec2 getPoint(int idx) const;

  double getArea() const;

 private:
  void recalculateArea();
  void reorderByCOG();
};

}

#endif //PHYSICS_POLYGON_H
