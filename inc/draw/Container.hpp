#pragma once
#include "base/Geometry.hpp"
#include <QString>


class Container : public Geo::Polygon // id:0
{
private:
    QString _txt;

public:
    Container(){};

    Container(const Geo::Polygon &shape);

    Container(const QString &txt, const Geo::Polygon &shape);

    Container(const Container &container);

    Container(const Container &&container);

    Container &operator=(const Container &container);

    Container &operator=(const Container &&container);

    Geo::Polygon &shape();

    const Geo::Polygon &shape() const;

    const QString &text() const;

    void set_text(const QString &txt);

    void clear_text();

    const Geo::Point center() const;

    virtual const bool empty() const;

    virtual Container *clone() const;
};

class CircleContainer : public Geo::Circle // id:1
{
private:
    QString _txt;

public:
    CircleContainer(){};

    CircleContainer(const Geo::Circle &shape);

    CircleContainer(const QString &txt, const Geo::Circle &shape);

    CircleContainer(const QString &txt, const double x, const double y, const double r);

    CircleContainer(const CircleContainer &container);

    CircleContainer(const CircleContainer &&container);

    CircleContainer &operator=(const CircleContainer &container);

    CircleContainer &operator=(const CircleContainer &&container);

    Geo::Circle &shape();

    const Geo::Circle &shape() const;

    const QString &text() const;

    void set_text(const QString &txt);

    void clear_text();

    virtual const bool empty() const;

    virtual CircleContainer *clone() const;
};

class Link : public Geo::Polyline // id:2
{
private:
    Geo::Geometry *_tail = nullptr;
    Geo::Geometry *_head = nullptr;

public:
    Link(std::vector<Geo::Point>::const_iterator begin, std::vector<Geo::Point>::const_iterator end, Geo::Geometry *tail, Geo::Geometry *head);

    Link(const Geo::Polyline &polyline, Geo::Geometry *tail, Geo::Geometry *head);

    Link(const Link &link);

    Link(const Link &&link);

    Link &operator=(const Link &link);

    Link &operator=(const Link &&link);

    virtual const double length() const;

    const bool empty() const;

    virtual void clear();

    virtual Link *clone() const;

    virtual Geo::Rectangle bounding_rect() const;

    Geo::Geometry *tail();

    const Geo::Geometry *tail() const;

    void set_tail(Geo::Geometry *geo);

    Geo::Geometry *head();

    const Geo::Geometry *head() const;

    void set_head(Geo::Geometry *geo);
};

class ContainerGroup : public Geo::Geometry
{
private:
    std::vector<Geo::Geometry *> _containers;
    double _ratio = 1; // 缩放系数
    bool _visible = true;

public:
    ContainerGroup(){};

    ContainerGroup(const ContainerGroup &containers);

    ContainerGroup(const ContainerGroup &&containers);

    ContainerGroup(const std::initializer_list<Geo::Geometry *> &containers);

    ContainerGroup(std::vector<Geo::Geometry *>::const_iterator begin, std::vector<Geo::Geometry *>::const_iterator end);

    ~ContainerGroup();

    const bool &visible() const;

    void show();

    void hide();

    ContainerGroup *clone() const;

    ContainerGroup &operator=(const ContainerGroup &group);

    ContainerGroup &operator=(const ContainerGroup &&group);

    std::vector<Geo::Geometry *>::iterator begin();

    std::vector<Geo::Geometry *>::const_iterator begin() const;

    std::vector<Geo::Geometry *>::const_iterator cbegin() const;

    std::vector<Geo::Geometry *>::iterator end();

    std::vector<Geo::Geometry *>::const_iterator end() const;

    std::vector<Geo::Geometry *>::const_iterator cend() const;

    std::vector<Geo::Geometry *>::reverse_iterator rbegin();

    std::vector<Geo::Geometry *>::const_reverse_iterator rbegin() const;

    std::vector<Geo::Geometry *>::const_reverse_iterator crbegin() const;

    std::vector<Geo::Geometry *>::reverse_iterator rend();

    std::vector<Geo::Geometry *>::const_reverse_iterator rend() const;

    std::vector<Geo::Geometry *>::const_reverse_iterator crend() const;

    Geo::Geometry *operator[](const size_t index);

    const Geo::Geometry *operator[](const size_t index) const;

    virtual void clear();

    virtual void transform(const double a, const double b, const double c, const double d, const double e, const double f);

    virtual void transform(const double mat[6]);

    virtual void translate(const double tx, const double ty);

    virtual void rotate(const double x, const double y, const double rad); // 弧度制

    virtual void scale(const double x, const double y, const double k);

    void rescale(const double x, const double y);

    virtual Geo::Rectangle bounding_rect() const;

    const size_t size() const;

    void append(Container *container);

    void append(CircleContainer *container);

    void append(Link *container);

    void append(Geo::Polyline *container);

    void append(Geo::Bezier *bezier);

    std::vector<Geo::Geometry *>::iterator remove(const size_t index);

    std::vector<Geo::Geometry *>::iterator remove(const std::vector<Geo::Geometry *>::iterator &it);

    std::vector<Geo::Geometry *>::iterator remove(const std::vector<Geo::Geometry *>::reverse_iterator &it);

    Geo::Geometry *pop(const size_t index);

    Geo::Geometry *pop(const std::vector<Geo::Geometry *>::iterator &it);

    Geo::Geometry *pop(const std::vector<Geo::Geometry *>::reverse_iterator &it);

    Geo::Geometry *pop_front();

    Geo::Geometry *pop_back();

    const bool empty() const;

    Geo::Geometry *front();

    const Geo::Geometry *front() const;

    Geo::Geometry *back();

    const Geo::Geometry *back() const;

    void remove_front();

    void remove_back();
};