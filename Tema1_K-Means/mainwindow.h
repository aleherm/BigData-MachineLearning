#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include <QPoint>
#include <cluster.h>

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
    QVector<cluster> clusterPoints;
    bool mustPrintBox;

    // events
    //virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    //virtual void paintEvent(QPaintEvent *event) override;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
