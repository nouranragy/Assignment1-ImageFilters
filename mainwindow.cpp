#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>
#include <QFileInfo>

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
void MainWindow ::on_greyScale_clicked()
{
    if(myImage.width == 0 || myImage.height == 0) return;
    greyScale(myImage);

    myImage.saveImage("temp_output.jpg");

    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}
void MainWindow::on_flipImage_clicked()//filter5
{
    if (myImage.width == 0 || myImage.height == 0) return;

    bool ok;
    QString choice = QInputDialog::getItem(this, "Flip Image", "Direction (h/v):", {"h", "v"}, 0, false, &ok);
    if (!ok || choice.isEmpty()) return;

    flipImage(myImage, choice.at(0).toLatin1());
    myImage.saveImage("temp_output.jpg");
    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void MainWindow::on_addFrame_clicked()
{
    if (myImage.width == 0 || myImage.height == 0) return;
    QStringList options = {"1", "2"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "Add Frame", "Select Frame Type:", options, 0, false, &ok);
    if (ok && !choice.isEmpty()) {
        int frameType = choice.toInt();
        addFrame(myImage, frameType);
    }
    myImage.saveImage("temp_output.jpg");

    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void MainWindow::on_setBlur_clicked()
{
    if (myImage.width == 0 || myImage.height == 0) return;
    bool ok;
    int level = QInputDialog::getInt(this, "Set Blur", "Enter Blur Level (1 - 20):", 3, 1, 20, 1, &ok);
    if (ok)
    {
        setBlur(myImage, level);
        myImage.saveImage("temp_output.jpg");
        ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}
void MainWindow::on_applyInfrared_clicked()
{
    if (myImage.width == 0 || myImage.height == 0) return;
    applyInfrared(myImage);
    myImage.saveImage("temp_output.jpg");
    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void MainWindow::on_resizePhoto_clicked()
{
    if (myImage.width == 0 || myImage.height == 0) return;

    bool okWidth, okHeight;
    int newWidth = QInputDialog::getInt(this, "Resize Image", "Enter New Width:", myImage.width, 1, 10000, 1, &okWidth);
    if (!okWidth) return;

    int newHeight = QInputDialog::getInt(this, "Resize Image", "Enter New Height:", myImage.height, 1, 10000, 1, &okHeight);
    if (!okHeight) return;

    myImage = resizePhoto(myImage, newWidth, newHeight);
    myImage.saveImage("temp_output.jpg");

    QPixmap pix("temp_output.jpg");
    ui->lblProcessed->setPixmap(pix);
    ui->lblProcessed->setAlignment(Qt::AlignCenter);

    statusBar()->showMessage(QString("New size: %1 x %2").arg(myImage.width).arg(myImage.height), 5000);
}
void MainWindow::on_mergeImage_clicked()
{
    if (myImage.width == 0 || myImage.height == 0) return;

    QString fileName = QFileDialog::getOpenFileName(this, "Select image to merge", "", "Image Files (*.png *.jpg *.bmp *.jpeg)");
    if (fileName.isEmpty()) return;

    Image otherImage;
    try { otherImage.loadNewImage(fileName.toStdString()); }
    catch (...) { QMessageBox::warning(this, "Error", "Image is not loaded"); return; }

    int option = 1, x = (myImage.width - otherImage.width) / 2, y = (myImage.height - otherImage.height) / 2;
    if (myImage.width != otherImage.width || myImage.height != otherImage.height)
    {
        bool ok;
        QString choice = QInputDialog::getItem(this, "Different sizes", "1: resize both, 2: merge the common area",
                                               {"1", "2"}, 0, false, &ok);
        if (!ok) return;
        option = choice.toInt();
        if (option == 2)
        {
            bool ok1, ok2;
            x = QInputDialog::getText(this, "Position", "x of the other image:", QLineEdit::Normal, "0", &ok1).toInt();
            y = QInputDialog::getText(this, "Position", "y of the other image:", QLineEdit::Normal, "0", &ok2).toInt();
            if (!ok1 || !ok2) return;
        }
    }

    int left = std::max(0, x), top = std::max(0, y);
    int right = std::min(myImage.width, x + otherImage.width), bottom = std::min(myImage.height, y + otherImage.height);
    if (option == 2 && (right <= left || bottom <= top))
    {
        QMessageBox::warning(this, "Error", "There is no overlapping");
        return;
    }
    if (option == 1)
    {
        int w = std::max(myImage.width, otherImage.width), h = std::max(myImage.height, otherImage.height);
        Image a = resizePhoto(myImage, w, h);
        Image b = resizePhoto(otherImage, w, h);
        myImage = a;
        otherImage = b;
        left = top = x = y = 0;
        right = w;
        bottom = h;
    }

    Image merging(right - left, bottom - top);
    for (int i = 0; i < merging.width; ++i)
        for (int j = 0; j < merging.height; ++j)
            for (int k = 0; k < 3; ++k)
                merging(i, j, k) = (myImage(left + i, top + j, k) + otherImage(left + i - x, top + j - y, k)) / 2;
    myImage = merging;

    myImage.saveImage("temp_output.jpg");
    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(
        ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
        originalPath = fileName; //added

        ui->lblOriginal->setPixmap(QPixmap(fileName).scaled(ui->lblOriginal->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::on_btnSave_clicked()
{
    if(myImage.width ==0 || myImage.height == 0) return;
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Image(*.png * .jpg * bmp)");
    if(fileName.isEmpty()) return;
    if (QFileInfo(fileName).suffix().isEmpty()) fileName += ".png";
    myImage.saveImage(fileName.toStdString());
    statusBar()->showMessage("Saved to " + fileName,3000);
}
void MainWindow::on_revertToOriginal_clicked() //fiexed
{
    if (originalPath.isEmpty()) return;

    myImage.loadNewImage(originalPath.toStdString());   // reload untouched file
    myImage.saveImage("temp_output.jpg");
    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    statusBar()->showMessage("Image reset to original", 3000);
}

void MainWindow::on_RotateImage_clicked()
{
     if(myImage.width == 0 || myImage.height == 0) return;

     QStringList options = {"90" , "180" , "270"};

     bool ok;

     QString choice = QInputDialog:: getItem(this,"Rotate Image" , "Select Angle:", options,0,false,&ok);

     if(ok && !choice .isEmpty()){
         int angle = choice.toInt();

         applyRotateImage(myImage , angle);

         myImage.saveImage("temp_output.jpg");

         ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


     }
}
void MainWindow::on_DetectImageEdges_clicked()
{
    if(myImage.width == 0 || myImage.height == 0) return;
    applyDetectImageEdges(myImage);

    myImage.saveImage("temp_output.jpg");

    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}


void MainWindow::on_Scanline_clicked()
{

    if(myImage.width == 0 || myImage.height == 0) return;
    applyScanlineFilter(myImage);

    myImage.saveImage("temp_output.jpg");

    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}
void MainWindow::on_sunLight_clicked()
{
    if(myImage.width == 0 || myImage.height == 0) return;
    sunlight(myImage);
    myImage.saveImage("temp_output.jpg");
    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}
void MainWindow::on_skewImage_clicked()
{
    if (myImage.width == 0|| myImage.height == 0) return;
    bool ok;
    double degrees = QInputDialog::getDouble(this, tr("Skew Image"), tr("Enter angle in gegrees: "), 0, -89.0, 89.0, 1, &ok);
    if (!ok) return;
    skewImage(myImage, degrees);
    myImage.saveImage("temp_output.jpg");
    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void MainWindow::on_OilPainting_clicked()
{
    if(myImage.width == 0 || myImage.height == 0) return;
    applyOilPainting(myImage);

    myImage.saveImage("temp_output.jpg");

    ui->lblProcessed->setPixmap(QPixmap("temp_output.jpg").scaled(ui->lblProcessed->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

