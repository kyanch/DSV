#pragma once

#include "aabb.hpp"
#include "geometry.hpp"
#include <glm/glm.hpp>

namespace Geo {
class Circle : public Geometry {
   private:
    Point _center;
    double _radius;

   public:
    Circle(const double x, const double y, const double r);
    Circle(const Point &point, const double r);

    const Point &center() const;
    const double radius() const;

    const double area() const;

    void transform(const glm::dmat3x3 mat) override;
    void translate(const double dx, const double dy) override;
    void rotate(const double rad,const Point& center) override;
    void scale(const double x, const double y) override;
    AxisAlignedBoundingBox bounding_box() const override;

    // move center point
    Circle operator+(const Point &point) const;
    Circle operator-(const Point &point) const;
    void operator+=(const Point &point);
    void operator-=(const Point &point);
};
}  // namespace Geo