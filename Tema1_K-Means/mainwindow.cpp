#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    printBoundingBox = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setBrush(Qt::black);
    for (int i = 0; i < points.size(); i++)
        painter.drawEllipse(points[i].x(), points[i].y(), 5, 5);

    for (auto cluster : clusterPoints)
    {
        painter.setPen(QPen(cluster.GetColor()));
        painter.drawEllipse(cluster.GetPosition().x() - 5, cluster.GetPosition().y() - 5, 10, 10);

        for (auto pointIndex : cluster.GetPoints())
            painter.drawLine(points[pointIndex].x(), points[pointIndex].y(), cluster.GetPosition().x(), cluster.GetPosition().y());

        if (printBoundingBox)
        {
            auto boundingBox=cluster.GetBoundingBox();

            painter.drawRect(boundingBox.first.x(),boundingBox.first.y(),boundingBox.second.x() - boundingBox.first.x(),boundingBox.second.y() - boundingBox.first.y());
            painter.drawText(boundingBox.first,QString::number(cluster.GetDensity()));
        }
    }
    printBoundingBox = false;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        clusterPoints.push_back(QPoint(event->pos().x(), event->pos().y()));

        DetermineCluster();
    }
    else if (event->buttons() == Qt::RightButton)
    {
        double minDistance = DBL_MAX;
        int clusterPosition = -1;
        for (int i = 0; i < clusterPoints.size(); i++)
        {
            QPoint point(event->pos().x(), event->pos().y());
            double dist = EuclidianDistance(point, clusterPoints[i].GetPosition());
            if (dist < minDistance)
            {
                minDistance = dist;
                clusterPosition = i;
            }
        }

        clusterPoints.erase(clusterPoints.begin() + clusterPosition);

        DetermineCluster();
    }

    repaint();
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        bool isRunning = true;
        while (isRunning)
        {
            for (auto cluster : clusterPoints)
                cluster.ClearPoints();

            QPair<QPoint, int> pair = qMakePair(QPoint(0, 0), 0);
            QVector<QPair<QPoint, int>> sumPosition(clusterPoints.size(), pair);

            for (uint i = 0; i < points.size(); i++)
            {
                double minDist = DBL_MAX;
                int  poz = -1;
                for (int j = 0; j < clusterPoints.size(); j++)
                {
                    double dist = EuclidianDistance(points[i], clusterPoints[j].GetPosition());
                    if (dist < minDist)
                    {
                        minDist = dist;
                        poz = j;
                    }
                }
                clusterPoints[poz].AddPoint(i, points[i]);
                sumPosition[poz].first.setX(sumPosition[poz].first.x() + points[i].x());
                sumPosition[poz].first.setY(sumPosition[poz].first.y() + points[i].y());
                sumPosition[poz].second++;
            }

            isRunning = false;
            for (int j = 0; j < clusterPoints.size(); j++)
            {
                QPoint newPosition = sumPosition[j].first / sumPosition[j].second;
                if (newPosition == clusterPoints[j].GetPosition())
                    isRunning = true;
                clusterPoints[j].SetPosition(newPosition);
            }
        }
    }
    else if (event->key() == Qt::Key_Shift)
        printBoundingBox = true;

    repaint();
}

void MainWindow::on_pushButton_clicked()
{
    srand(time(NULL));

    QString text = QInputDialog::getText(this, tr("Puncte"), tr("Numarul de puncte:"), QLineEdit::Normal);

    int k = text.toInt();

    for (int i = 0; i < k; i++)
    {
        int pozx = rand() % 1900 + 2;
        int pozy = rand() % 1000 + 2;
        points.push_back(QPoint(pozx, pozy));
    }
    repaint();
}

double MainWindow::EuclidianDistance(QPoint point1, QPoint point2)
{
    return qSqrt(((point1.x() - point2.x())*(point1.x() - point2.x())) + ((point1.y() - point2.y())*(point1.y() - point2.y())));
}

void MainWindow::DetermineCluster()
{
    for (auto& cluster : clusterPoints)
        cluster.ClearPoints();
    for (uint i = 0; i < points.size(); i++)
    {
        double minDist = DBL_MAX;
        int  poz = -1;
        for (int j = 0; j < clusterPoints.size(); j++)
        {
            double dist = EuclidianDistance(points[i], clusterPoints[j].GetPosition());
            if (dist < minDist)
            {
                minDist = dist;
                poz = j;
            }
        }
        clusterPoints[poz].AddPoint(i, points[i]);
    }
}
