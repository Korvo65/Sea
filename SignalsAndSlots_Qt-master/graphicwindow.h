#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QMainWindow>

namespace Ui {
class GraphicWindow;
}

class GraphicWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphicWindow(QWidget *parent = 0);
    ~GraphicWindow();

public slots:
    void slotRewriteGraph(double x, double y);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::GraphicWindow *ui;
    double centerX_;
    double centerY_;

};

#endif // GRAPHICWINDOW_H
