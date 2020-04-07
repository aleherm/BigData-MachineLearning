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

class cluster
{
public:
    cluster();
    cluster(const QPoint& clusterPosition);
    ~cluster();

public:
    const QSet<uint>& GetPointsIndex() const;
    void AddPointIndex(uint pointIndex, QPoint pointPosition);
    void ClearPointsIndex();

    QPoint GetPosition() const;
    void SetPosition(const QPoint & position);

    double GetDensity() const;
    QColor GetColor() const;

    const QPair<QPoint, QPoint>& GetBoundingBox() const;

private:
    QSet<uint> pointsIndex;
    QColor color;
    QPoint position;
    QPair<QPoint, QPoint> boundingBox;
};
