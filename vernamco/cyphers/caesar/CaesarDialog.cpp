#include <QMessageBox>
#include "CaesarDialog.h"
#include "ui_CaesarDialog.h"
#include "../../MainWindow.h"
#include "../Cyphers.h"
#include "ui_MainWindow.h"

CaesarDialog::CaesarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaesarDialog),
    mainWindow(static_cast<MainWindow*>(parent))
{
    ui->setupUi(this);
}

CaesarDialog::~CaesarDialog()
{
    delete ui;
}

void CaesarDialog::on_EncryptPushButton_clicked()
{
    QString text     = mainWindow->ui->TextEdit->toPlainText();
    QString alphabet = ui->AlphabetLineEdit->text();
    int shift        = ui->ShiftSpinBox->value();

    if (text == "")
    {
        QMessageBox::critical(this, "Error", "Text required");
        return;
    }

    if (alphabet == "")
    {
        QMessageBox::critical(this, "Error", "Alphabet required");
        return;
    }

    if (shift == 0)
    {
        QMessageBox::critical(this, "Error", "Shift required");
        return;
    }


    QString encryptedText = Cyphers::Caesar(text, alphabet, shift);
    mainWindow->ui->TextEdit->setText(encryptedText);
    accept();
}
