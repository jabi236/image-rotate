#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override;



protected:

    void resizeEvent(QResizeEvent* event) override;

private slots:

    void on_actionQuit_triggered();

    void on_actionOpen_triggered();

    void reset();

    void setAngle(int);

    void resetSlider();

private:
    Ui::MainWindow* ui;
    QPixmap m_image;
    QGraphicsScene m_scene;
    int m_angle = 0;
};

#endif //MAINWINDOW_H
