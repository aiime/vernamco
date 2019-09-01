#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MaskEncryptionDialog.h"
#include "MaskDecryptionDialog.h"
#include "SymbolReplacementDialog.h"

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

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

void MainWindow::on_SymbolReplacement_triggered()
{
    SymbolReplacementDialog symbolReplacementDialog(this);
    symbolReplacementDialog.setModal(true);
    symbolReplacementDialog.exec();
}

void MainWindow::on_MaskDecryption_triggered()
{
    MaskDecryptionDialog maskDecryptionDialog(this);
    maskDecryptionDialog.setModal(true);
    maskDecryptionDialog.exec();
}

void MainWindow::on_Open_triggered()
{
    // Get path of text file.
    QFileDialog openDialog(this);
    openDialog.setFileMode(QFileDialog::ExistingFile);
    openDialog.setNameFilter(tr("Text (*.txt)"));
    if (!openDialog.exec()) return;
    QString textFilePath = openDialog.selectedFiles()[0];

    // Open text file.
    QFile textFile(textFilePath);
    textFile.open(QIODevice::ReadOnly);
    QTextStream in(&textFile);
    openedFile = textFilePath;

    // Print text from file.
    ui->TextEdit->setText(in.readAll());
}

void MainWindow::on_Save_triggered()
{
    if(openedFile != "")
    {
        QFile textFile(openedFile);
        textFile.open(QIODevice::WriteOnly);
        textFile.write(ui->TextEdit->toPlainText().toUtf8());
    }
    else
    {
        emit on_SaveAs_triggered();
    }
}

void MainWindow::on_SaveAs_triggered()
{
    QString textFilePath = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("Text file (*.txt)"));

    if(textFilePath == "") return;

    QFile textFile(textFilePath);
    textFile.open(QIODevice::WriteOnly);
    textFile.write(ui->TextEdit->toPlainText().toUtf8());
}

void MainWindow::on_Close_triggered()
{
    openedFile = "";
    ui->TextEdit->setText("");
}

void MainWindow::on_Exit_triggered()
{
    if(openedFile != "")
    {
        QMessageBox::StandardButton buttonClicked = QMessageBox::information(this,
                                                                             "Save",
                                                                             "Save file \"" + QFileInfo(openedFile).baseName() + "\" ?",
                                                                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                                                             QMessageBox::Yes);
        switch (buttonClicked)
        {
            case QMessageBox::Yes : emit on_Save_triggered(); QApplication::quit(); break;
            case QMessageBox::No : QApplication::quit(); break;
            case QMessageBox::Cancel : return;
            default: return;
        }
    }

    else if(ui->TextEdit->toPlainText() != "")
    {
        QMessageBox::StandardButton buttonClicked = QMessageBox::information(this,
                                                                             "Save",
                                                                             "Save file?",
                                                                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                                                             QMessageBox::Yes);
        switch (buttonClicked)
        {
            case QMessageBox::Yes : emit on_SaveAs_triggered(); QApplication::quit(); break;
            case QMessageBox::No : QApplication::quit(); break;
            case QMessageBox::Cancel : return;
            default: return;
        }
    }

    else
    {
        QApplication::quit();
    }
}
