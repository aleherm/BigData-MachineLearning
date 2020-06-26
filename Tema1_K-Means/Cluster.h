#pragma once
#include <stdlib.h>
#include <time.h>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPoint>
#include <QVector3D>
#include <QSet>

class Cluster
{
public:
    Cluster();
    Cluster(QPoint ClusterPosition);
    ~Cluster();

public:
    const QSet<uint>& GetPoints();
    void AddPoint(uint pointIndex, QPoint pointPosition);
    void ClearPoints();

    QPoint GetPosition();
    void SetPosition(QPoint & position);

    double GetDensity();
    QColor GetColor();

    QPair<QPoint, QPoint>& GetBoundingBox();

private:
    QSet<uint> points;
    QColor color;
    QPoint position;
    QPair<QPoint, QPoint> boundingBox;
};
