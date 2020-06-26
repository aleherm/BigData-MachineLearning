#ifndef NEIGHBOR_H
#define NEIGHBOR_H
#include<point.h>
#include "neighbor.h"
#include <fstream>
#include "qmath.h"
#include "QDebug"

class Neighbor
{
public:
    Neighbor(int k);

    std::vector<Point> GetPoints() const;

    bool GetData(std::string csv_file_path);

    void AddPoint(QPoint point);
    void AddPointWeight(QPoint point);

    int CalculateMaxK();

private:
    std::vector<std::string> Tokenize(const std::string &str, const char delim);
    QColor GetColor(int poz);

private:
    double EuclidianDistance(QPoint point1, QPoint point2);
    double EuclidianDistanceWeight(QPoint point1, QPoint point2);

private:
    std::vector<Point> points;
    int k;
};

#endif // NEIGHBOR_H
