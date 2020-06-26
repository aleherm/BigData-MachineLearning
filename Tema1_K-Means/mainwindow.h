#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPoint>
#include <QtMath>
#include <Cluster.h>
#include <float.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // members
    QVector<QPoint> points;
    QVector<Cluster> clusterPoints;
    bool printBoundingBox;

    // events
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    double EuclidianDistance(QPoint point1, QPoint point2);
    void DetermineCluster();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
