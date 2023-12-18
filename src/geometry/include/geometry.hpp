#pragma once

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include "aabb.hpp"

namespace Geo {
const static double PI = 3.14159265358979323846L;
const static double EPSILON = 1e-10L;

class Geometry {
   public:
    virtual ~Geometry(){};

    virtual void transform(const glm::dmat3x3 mat) = 0;
    virtual void translate(const double dx, const double dy) = 0;
    virtual void rotate(const double rad, const Point& center) = 0;
    virtual void scale(const double x, const double y) = 0;

    // virtual Polygon convex_hull() const;
    virtual AxisAlignedBoundingBox bounding_box() const = 0;
};

};  // namespace Geo