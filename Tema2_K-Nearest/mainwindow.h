#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QVector>
#include<QPoint>
#include <stdlib.h>
#include <time.h>
#include <QVector3D>
#include "neighbor.h"
#include <QInputDialog>
#include <QtMath>
#include "qmath.h"
#include <float.h>
#include "QMessageBox"

namespace Ui {
class MainWindow;
}

enum AlgorithmType
{
    E_WITH_WEIGHT,
    E_WITHOUT_WEIGHT
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    Neighbor knearest;
    AlgorithmType type;
};

#endif // MAINWINDOW_H
