#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include <QString>
#include <QFileInfo>
#include <QFileDialog>
#include <QImageReader>
#include <QImage>
#include <QMessageBox>
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


void MainWindow::on_pushButton_clicked()
{
    QDir dir = QFileDialog::getExistingDirectory(this, "Open a directory", QDir::homePath());
    QStringList images = dir.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.gif" << "*.GIF" << "*.tif" << "*.TIF"  << "*.bmp" << "*.BMP" << "*.png" << "*.PNG" << "*.pcx" << "*.PCX",QDir::Files);
    QImageReader reader;

    reader.setAutoDetectImageFormat(true);
    int rows = 0;
    foreach(QString filename, images)
    {
        QImage image = QImage(dir.path() + "/" + filename);
        QTableWidgetItem *res = new QTableWidgetItem(QString::number(image.width()) + " x " + QString::number(image.height()));
        QTableWidgetItem *name = new QTableWidgetItem(QString(filename));
        QTableWidgetItem *dpi = new QTableWidgetItem(QString::number(image.dotsPerMeterX() * 0.0254));
        QTableWidgetItem *depth = new QTableWidgetItem(QString::number(image.depth()));
        rows++;
        ui->table->setRowCount(rows);
        ui->table->setItem(rows - 1, 0, name);
        ui->table->setItem(rows - 1, 1, res);
        ui->table->setItem(rows - 1, 2, dpi);
        ui->table->setItem(rows - 1, 3, depth);
    }
}

