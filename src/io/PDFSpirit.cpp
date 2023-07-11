#include "io/PDFSpirit.hpp"

#define ACTIVE if(!_active){return;}


PDFSpirit::PDFSpirit()
{
    const Scanner end = Scanner('\n') | Scanners::space;
    const Scanner skip_cmd = Scanner("cm") | Scanner('q') | Scanner('Q') | Scanner('W') | Scanner('J') 
        | Scanner('j') | Scanner('M') | Scanner('d') | Scanner("ri") | Scanner('i') | Scanner("gs");
    const Scanner key_cmd = Scanner('/') << Scanners::alphas;

    bind(Scanner('\n'), &PDFSpirit::pass);
    bind(Scanners::space, &PDFSpirit::pass);
    bind(Scanner("stream"), &PDFSpirit::on);
    bind(Scanner("endstream"), &PDFSpirit::off);
    
    bind(Scanners::num, &PDFSpirit::store_value);
    bind(Scanner('m') << end, &PDFSpirit::start);
    bind(Scanner('l') << end, &PDFSpirit::line);
    bind(Scanner('c') << end, &PDFSpirit::curve);
    bind(Scanner('S') << end, &PDFSpirit::store);
    bind(Scanner("re") << end, &PDFSpirit::rect);

    bind(Scanners::alphas, &PDFSpirit::skip);
    bind(key_cmd, &PDFSpirit::skip);
    bind(!Scanner('\n'), &PDFSpirit::pass);
}



void PDFSpirit::start(const std::string &value)
{
    ACTIVE
    if (_values.size() > 2)
    {
        _values.erase(_values.begin(), _values.begin() + _values.size() - 2);
    }
    _points.clear();
    _start_point.x = _values.front();
    _start_point.y = _values.back();
}

void PDFSpirit::store_value(const std::string &value)
{
    ACTIVE
    _values.push_back(std::atof(value.c_str()));
}

void PDFSpirit::skip(const std::string &value)
{
    ACTIVE
    _start_point.x = _start_point.y = 0;
    _values.clear();
}

void PDFSpirit::line(const std::string &value)
{
    ACTIVE
    _last_tool = _cur_tool;
    _cur_tool = Tool::Line;

    _points.emplace_back(Geo::Point(_values[_values.size() - 2], _values.back()));
    _values.erase(_values.begin(), _values.begin() + _values.size() - 2);
}

void PDFSpirit::curve(const std::string &value)
{
    ACTIVE
    _last_tool = _cur_tool;
    _cur_tool = Tool::Curve;
    
    std::vector<Geo::Point> points;
    for (int i = 0; i < 7; i += 2)
    {
        points.emplace_back(Geo::Point(_values[i], _values[i + 1]));
    }
    Geo::Bezier bezier(points.cbegin(), points.cend(), 3);
    _values.erase(_values.begin(), _values.begin() + _values.size() - 2);
    for (const Geo::Point &point : bezier.shape())
    {
        _points.emplace_back(point);
    }
}

void PDFSpirit::rect(const std::string &value)
{
    ACTIVE

    _points.clear();
    _points.emplace_back(Geo::Point(_values[_values.size() - 4], _values[_values.size() - 3]));
    _points.emplace_back(Geo::Point(_values[_values.size() - 4] + _values[_values.size() - 2], _values[_values.size() - 3]));
    _points.emplace_back(Geo::Point(_values[_values.size() - 4] + _values[_values.size() - 2], _values[_values.size() - 3] + _values.back()));
    _points.emplace_back(Geo::Point(_values[_values.size() - 4], _values[_values.size() - 3] + _values.back()));
    _points.emplace_back(Geo::Point(_values[_values.size() - 4], _values[_values.size() - 3]));

    _values.clear();
    _values.push_back(_points.back().coord().x);
    _values.push_back(_points.back().coord().y);
    _start_point.x = _values.front();
    _start_point.y = _values.back();
}



void PDFSpirit::store(const std::string &value)
{
    ACTIVE

    if (_start_point.x == _values[_values.size() - 2] 
        && _start_point.y == _values.back())
    {
        _graph->back().append(new Container(Geo::Polygon(_points.cbegin(), _points.cend())));
    }
    else
    {
        _graph->back().append(new Geo::Polyline(_points.cbegin(), _points.cend()));
    }

    _start_point.x = _start_point.y = 0;
    _values.clear();
    _points.clear();
}



void PDFSpirit::on(const std::string &value)
{
    _active = true;
}

void PDFSpirit::off(const std::string &value)
{
    _active = false;
}



void PDFSpirit::load_graph(Graph *g)
{
    _graph = g;
    if (_graph->container_groups().empty() || !_graph->back().empty())
    {
        _graph->append_group();
    }
}