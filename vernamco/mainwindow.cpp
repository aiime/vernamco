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

void MainWindow::on_CaesarEncryption_triggered()
{
    CaesarDialog caesarDialog(this, Ui::EncryptionMode::Encrypt);
    caesarDialog.setModal(true);
    caesarDialog.exec();
}

void MainWindow::on_CaesarDecryption_triggered()
{
    CaesarDialog caesarDialog(this, Ui::EncryptionMode::Decrypt);
    caesarDialog.setModal(true);
    caesarDialog.exec();
}
