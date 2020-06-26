#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    , knearest (Neighbor(3))
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);

    knearest.GetData("../nodes.csv");

    QString text = QInputDialog::getText(this, tr("Input"), tr("N-Normal \nW-Weight"), QLineEdit::Normal);

    if (text == "N")
    {
        type = AlgorithmType::E_WITHOUT_WEIGHT;
    }
    else
    {
        type = AlgorithmType::E_WITH_WEIGHT;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    QPoint point(event->pos().x(), event->pos().y());
    if(type == E_WITH_WEIGHT)
        knearest.AddPoint(point);
    else
        knearest.AddPointWeight(point);

    repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        int k = knearest.CalculateMaxK();
        QString s = QString::number(k);

        QMessageBox::information(this, tr("Best K"), s, QMessageBox::Ok);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter p;
    p.begin(this);

    auto points = knearest.GetPoints();
    for(auto point : points)
    {
        p.setPen(QPen(point.GetColor()));
        p.drawEllipse(point.GetPoint(), 5, 5);
    }
}
