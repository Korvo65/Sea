#include "graphicwindow.h"
#include "ui_graphicwindow.h"

#include <QPainter>

GraphicWindow::GraphicWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphicWindow)
{
    ui->setupUi(this);
}

GraphicWindow::~GraphicWindow()
{
    delete ui;
}

void GraphicWindow::slotRewriteGraph(double x, double y)
{
    centerX_ = x;
    centerY_ = y;
    repaint();
}

void GraphicWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawEllipse(centerX_*200, 100+centerY_*200, 50, 50);
}
