#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Filters.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_BlackandWhite_clicked();

    void on_btnLoad_clicked();

    void on_RotateImage_clicked();

    void on_DetectImageEdges_clicked();

    void on_Scanline_clicked();

private:
    Ui::MainWindow *ui;
    Image myImage;
};
#endif // MAINWINDOW_H
