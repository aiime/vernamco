#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MaskEncryptionDialog.h"
#include "MaskDecryptionDialog.h"


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

void MainWindow::on_MaskEncryption_triggered()
{
    MaskEncryptionDialog maskEncryptionDialog(this);
    maskEncryptionDialog.setModal(true);
    maskEncryptionDialog.exec();
}

void MainWindow::on_MaskDecryption_triggered()
{
    MaskDecryptionDialog maskDecryptionDialog(this);
    maskDecryptionDialog.setModal(true);
    maskDecryptionDialog.exec();
}
