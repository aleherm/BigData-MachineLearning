#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        srand(time(NULL));

        QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Nr. of points:"), QLineEdit::Normal);

        int k = text.toInt();

        for (int i = 0; i < k; i++)
        {
            int pozx = rand() % 1900 + 2;
            int pozy = rand() % 1000 + 2;
            points.push_back(QPoint(pozx, pozy));
        }
    }

    repaint();
}
