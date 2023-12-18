#pragma once
#include <glm/glm.hpp>

namespace Geo {

using Point = glm::dvec3;

class AxisAlignedBoundingBox {
    Point _topLeft;
    double _height, _width;

   public:
    AxisAlignedBoundingBox(const Point &top_left, const double height,
                           const double width);
    AxisAlignedBoundingBox(const double x0, const double y0, const double x1,
                           const double y1);
    AxisAlignedBoundingBox(const Point &point0, const Point &point1);
};

using AABB = AxisAlignedBoundingBox;

}  // namespace Geo