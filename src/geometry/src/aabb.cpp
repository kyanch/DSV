#include "aabb.hpp"
#include <algorithm>

using Geo::AxisAlignedBoundingBox;

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Point &top_left,
                                               const double height,
                                               const double width)
    : _topLeft(top_left), _height(height), _width(width) {}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const double x0, const double y0,
                                               const double x1, const double y1)
    : _topLeft(Point(std::min(x0, x1), std::min(y0, y1), 1)),
      _width(std::abs(x1 - x0)),
      _height(std::abs(y1 - y0)) {}

// 委托构造
AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Point &point0,
                                               const Point &point1)
    : AxisAlignedBoundingBox(point0.x, point0.y, point1.x, point1.y) {}