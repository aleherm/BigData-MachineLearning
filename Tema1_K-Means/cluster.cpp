#include "cluster.h"
#include <stdlib.h>
#include <time.h>

//srand(time(NULL));

cluster::cluster()
{
}

cluster::cluster(const QPoint& clusterPosition) : position(clusterPosition)
{
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    color = QColor(r, g, b, 255);

    boundingBox = QPair<QPoint, QPoint>( QPoint(INT_MAX, INT_MAX), QPoint(-1, -1));
}


cluster::~cluster()
{
}
