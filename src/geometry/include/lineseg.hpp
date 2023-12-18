
#pragma once

#include "aabb.hpp"
#include "geometry.hpp"

namespace Geo {
class LineSeg : public Geometry {
   private:
    Point _start_point;
    Point _end_point;

   public:
    LineSeg(const double x0, const double y0, const double x1, const double y1);
    LineSeg(const Point &start, const Point &end);

    LineSeg operator+(const Point &point);
    LineSeg operator-(const Point &point);
    void operator+=(const Point &point);
    void operator-=(const Point &point);

    virtual const double length() const;

    void transform(glm::dmat3x3 mat) override;
    void translate(const double tx, const double ty) override;
    void rotate(const double rad, const Point &point) override;
    void scale(const double x, const double y) override;
    AxisAlignedBoundingBox bounding_box() const override;

    const Point &front() const;
    const Point &back() const;
};
}  // namespace Geo