
#pragma once

#include <vector>
#include "aabb.hpp"
#include "geometry.hpp"
// #include "polygon.hpp"

namespace Geo {
class Polyline : public Geometry {
   private:
    std::vector<Point> _points;

   public:
    Polyline();
    Polyline(std::vector<Point>::const_iterator begin,
             std::vector<Point>::const_iterator end);
    Polyline(const std::initializer_list<Point> &points);

    void transform(const glm::dmat3x3) override;
    void translate(const double tx, const double ty) override;
    void rotate(const double rad,const Point& point) override;
    void scale(const double x, const double y) override;
    AxisAlignedBoundingBox bounding_box()const override;

    // virtual Polygon convex_hull() const;
    

    // 点的操作重载

    Polyline *clone() const ;
    const size_t size() const;
    const bool empty() const;
    const double length() const;
    void clear();

    Point &operator[](const size_t index);
    const Point &operator[](const size_t index) const;

    Polyline operator+(const Point &point) const;

    Polyline operator-(const Point &point) const;

    void operator+=(const Point &point);

    void operator-=(const Point &point);

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

    Point &front();
    const Point &front() const;

    Point &back();
    const Point &back() const;

    std::vector<Point>::iterator begin();
    std::vector<Point>::const_iterator begin() const;
    std::vector<Point>::const_iterator cbegin() const;

    std::vector<Point>::iterator end();
    std::vector<Point>::const_iterator end() const;
    std::vector<Point>::const_iterator cend() const;

    std::vector<Point>::reverse_iterator rbegin();
    std::vector<Point>::const_reverse_iterator rbegin() const;
    std::vector<Point>::const_reverse_iterator crbegin() const;
    std::vector<Point>::reverse_iterator rend();
    std::vector<Point>::const_reverse_iterator rend() const;
    std::vector<Point>::const_reverse_iterator crend() const;

    std::vector<Point>::iterator find(const Point &point);
    std::vector<Point>::const_iterator find(const Point &point) const;
};
}  // namespace Geo