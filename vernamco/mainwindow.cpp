#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "cyphers/Cyphers.h"
#include "cyphers/caesar/CaesarDialog.h"

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

void MainWindow::on_Caesar_triggered()
{
    CaesarDialog caesarDialog(this);
    caesarDialog.setModal(true);
    caesarDialog.exec();
}
