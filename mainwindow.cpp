#include <QFileDialog>
#include <QImage>
#include <cassert>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QObject::connect(ui->resetButton, SIGNAL(clicked()),
                     this, SLOT(reset()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()),
                     this, SLOT(resetSlider()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()),
                     this, SLOT(on_actionQuit_triggered()));
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),
                     this, SLOT(setAngle(int)));
    resetSlider();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionQuit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered() {
    QString fileName =
            QFileDialog::getOpenFileName(this,
                                         "Open Image",
                                         ".",
                                         "Image Files (*.png *.jpg *.bmp)");
    QImage image(fileName);
    assert(!image.isNull());
    m_image = QPixmap::fromImage(image);
    QPixmap scaled = m_image.scaled(ui->image->size(), Qt::KeepAspectRatio);
    m_scene.addPixmap(scaled);
    ui->image->setScene(&m_scene);

}

void MainWindow::resizeEvent(QResizeEvent* event) {
    //if (ui->image->pixmap().isNull()) return;
    if(m_scene.items().isEmpty()) return;
    QPixmap scaled = m_image.scaled(ui->image->size(), Qt::KeepAspectRatio);
    m_scene.clear();
    m_scene.addPixmap(scaled);
    ui->image->setScene(&m_scene);
    ui->image->fitInView(m_scene.sceneRect(), Qt::KeepAspectRatio);
    reset();
}

void MainWindow::reset(){
    ui->image->rotate(m_angle*-1);
    m_angle = 0;
}

void MainWindow::setAngle(int value){
    reset();
    ui->image->rotate(value);
    m_angle = value;
}

void MainWindow::resetSlider(){
    ui->horizontalSlider->setValue(0);
}
