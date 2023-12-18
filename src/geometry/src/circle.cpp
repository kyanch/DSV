#include "circle.hpp"
#include <cassert>
#include "aabb.hpp"
#include "geometry.hpp"
#include "glm/fwd.hpp"
#include <cmath>

using Geo::AxisAlignedBoundingBox;
using Geo::Circle;
using Geo::Point;

Circle::Circle(const double x, const double y, const double r)
    : _center(Point(x, y, 1)), _radius(r) {}

Circle::Circle(const Point &point, const double r)
    : _center(point), _radius(r) {}

const Point &Circle::center() const { return _center; }
const double Circle::radius() const { return _radius; }

const double Circle::area() const { return Geo::PI * _radius * _radius; }

void Circle::transform(const glm::dmat3x3 mat) { _center = mat * _center; }

void Circle::translate(const double dx, const double dy) {
    _center = glm::dmat3x3(glm::dvec3(1, 0, dx), glm::dvec3(0, 1, dy),
                           glm::dvec3(0, 0, 1)) *
              _center;
}

void Circle::rotate(const double rad, const Point &point) {
    glm::dmat3x3 trans_to_center_mat(glm::dvec3(1, 0, -point.x),
                                     glm::dvec3(0, 1, -point.y),
                                     glm::dvec3(0, 0, 1)),
        trans_back_mat(glm::dvec3(1, 0, point.x), glm::dvec3(0, 1, point.y),
                       glm::dvec3(0, 0, 1)),
        rotate_mat(glm::dvec3(std::cos(rad), -std::sin(rad), 0),
                   glm::dvec3(std::sin(rad), cos(rad), 0), glm::dvec3(0, 0, 1));
    _center = trans_back_mat * rotate_mat * trans_to_center_mat * _center;
}
void Circle::scale(const double x, const double y) {
    assert(x == y);
    _radius *= x;
    _center *= x;
}

AxisAlignedBoundingBox Circle::bounding_box() const {
    return AABB(_center - Point(_radius, _radius, 0), 2 * radius(),
                2 * radius());
}

// move center point
Circle Circle::operator+(const Point &point) const {
    return Circle(center() + point, radius());
}
Circle Circle::operator-(const Point &point) const {
    return Circle(center() - point, radius());
}
void Circle::operator+=(const Point &point) { _center += point; }
void Circle::operator-=(const Point &point) { _center -= point; }