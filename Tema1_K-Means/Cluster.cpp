#include "Cluster.h"
#include <stdlib.h>
#include <time.h>

//srand(time(NULL));

Cluster::Cluster()
{
}

Cluster::Cluster(QPoint clusterPosition) : position(clusterPosition)
{
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    color = QColor(r, g, b, 255);

    boundingBox = QPair<QPoint, QPoint>( QPoint(INT_MAX, INT_MAX), QPoint(-1, -1));
}


Cluster::~Cluster()
{
}

const QSet<uint>& Cluster::GetPoints()
{
    return points;
}

QColor Cluster::GetColor()
{
    return color;
}

QPoint Cluster::GetPosition()
{
    return position;
}

void Cluster::SetPosition(QPoint &pos)
{
    position = pos;
}

void Cluster::AddPoint(uint pointIndex, QPoint pointPosition) // adauga punct la Cluster
{
    points.insert(pointIndex); // recalculeaza bounding box-ul

    if (pointPosition.x() < boundingBox.first.x())
        boundingBox.first.setX(pointPosition.x());
    if (pointPosition.y() < boundingBox.first.y())
        boundingBox.first.setY(pointPosition.y());

    if (pointPosition.x() > boundingBox.second.x())
        boundingBox.second.setX(pointPosition.x());
    if (pointPosition.y() > boundingBox.second.y())
        boundingBox.second.setY(pointPosition.y());
}

void Cluster::ClearPoints()
{
    points.clear();
    boundingBox = QPair<QPoint, QPoint>(QPoint(INT_MAX, INT_MAX), QPoint(-1, -1));
}

double Cluster::GetDensity()
{
    int l = boundingBox.second.x() - boundingBox.first.x();
    int L = boundingBox.second.y() - boundingBox.first.y();
    double nrOfPoints = points.size();
    double area = L * l;
    return nrOfPoints/area; // nr de puncte / aria cutiei
}

QPair<QPoint, QPoint>& Cluster::GetBoundingBox()
{
    return boundingBox;
}
