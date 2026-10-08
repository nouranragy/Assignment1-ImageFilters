#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BlackandWhite_clicked()
{
    if(myImage.width == 0 || myImage.height == 0) return;
    applyBlackandWhite(myImage);

    myImage.saveImage("temp_output.jpg");

     ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}


void MainWindow::on_btnLoad_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Image Files (*.png *.jpg *.bmp *.jpeg)" );
    if(!fileName.isEmpty()){

        myImage.loadNewImage(fileName.toStdString());

        ui->lblOriginal->setPixmap(QPixmap(fileName).scaled(ui->lblOriginal->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

