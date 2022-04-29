#include <iostream>

class Point
{
public:
//    Point(){ x_ = 0; y_ = 0;}
    Point(int x = 0, int y = 0):x_(x), y_(y){}
    Point(const Point &p){ x_ = p.x(); y_ = p.y(); }
    int x() const { return x_; }
    int y() const { return y_; }
    void x(int x) { x_ = x; }
    void y(int y) { y_ = y; }

private:
    int x_;
    int y_;
};

class UPoint
{
    friend class Handle;
    Point p;
    int u;

    UPoint():u(1){}
    UPoint(int x, int y): p(x, y), u(1){}
    UPoint(const Point& point): p(point), u(1){}
};

class Handle
{
public:
    Handle(): up(new UPoint){};
    Handle(const Handle &h): up(h.up) { ++up->u; };
    Handle(const Point &p): up(new UPoint(p)) { };
    Handle(int x, int y): up(new UPoint(x, y)) { };
    ~Handle();
    Handle& operator=(const Handle &);
    int x() const;
    int y() const;
    Handle& x(int x);
    Handle& y(int y);

private:
    UPoint *up;
};

Handle::~Handle()
{
    if(--up->u == 0)
        delete up;
}

Handle& Handle::operator=(const Handle& h)
{
    ++h.up->u;
    if(--up->u == 0)
        delete up;
    up = h.up;
    return *this;
}

int Handle::x() const
{
    return up->p.x();
}

int Handle::y() const
{
    return up->p.y();
}

Handle& Handle::x(int x)
{
    if(up->u !=1)
    {
        --up->u;
        up = new UPoint(up->p);
    }
    up->p.x(x);
    return *this;
}

Handle& Handle::x(int y)
{
    if(up->u !=1)
    {
        --up->u;
        up = new UPoint(up->p);
    }
    up->p.y(y);
    return *this;
}

