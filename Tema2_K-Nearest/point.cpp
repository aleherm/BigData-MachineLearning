#include "point.h"

Point::Point()
{

}

Point::Point(int x, int y, QColor color) : point(QPoint(x,y)), color(color)
{

}

Point::Point(QPoint p, QColor color) :point(p), color(color)
{

}

void Point::operator =( Point &p)
{
    color = p.color;
    point = p.point;
}

QPoint Point::GetPoint() const
{
    return point;
}

QColor Point::GetColor() const
{
    return color;
}
