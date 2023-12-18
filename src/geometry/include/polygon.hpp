
#pragma once

#include "aabb.hpp"
#include "polyline.hpp"
#include <vector>

namespace Geo {
class Polygon : public Polyline {
   public:
    Polygon();
    Polygon(std::vector<Point>::const_iterator begin,
            std::vector<Point>::const_iterator end);
    Polygon(const std::initializer_list<Point> &points);

    Polygon(const Polyline &polyline);

    Polygon(const AxisAlignedBoundingBox &box);

    virtual Polygon *clone() const;

    virtual void append(const Point &point);

    virtual void append(const Polyline &polyline);

    virtual void append(std::vector<Point>::const_iterator begin,
                        std::vector<Point>::const_iterator end);

    virtual void insert(const size_t index, const Point &point);

    virtual void insert(const size_t index, const Polyline &polyline);

    virtual void insert(const size_t index,
                        std::vector<Point>::const_iterator begin,
                        std::vector<Point>::const_iterator end);

    virtual void remove(const size_t index);

    virtual Point pop(const size_t index);

    Polygon operator+(const Point &point) const;

    Polygon operator-(const Point &point) const;

    void operator+=(const Point &point);

    void operator-=(const Point &point);

    const double area() const;
};
}  // namespace Geo