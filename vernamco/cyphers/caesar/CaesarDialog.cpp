#include <QMessageBox>
#include "CaesarDialog.h"
#include "ui_CaesarDialog.h"
#include "../../MainWindow.h"
#include "../Cyphers.h"
#include "ui_MainWindow.h"

CaesarDialog::CaesarDialog(QWidget *parent, Ui::EncryptionMode encryptionMode) :
    QDialog(parent),
    ui(new Ui::CaesarDialog),
    mainWindow(static_cast<MainWindow*>(parent)),
    encryptionMode(encryptionMode)
{
    ui->setupUi(this);

    if (encryptionMode == Ui::EncryptionMode::Encrypt)
    {
        ui->EncryptionPushButton->setText("Encrypt");
    }
    else
    {
        ui->EncryptionPushButton->setText("Decrypt");
    }
}

CaesarDialog::~CaesarDialog()
{
    delete ui;
}

void CaesarDialog::on_EncryptionPushButton_clicked()
{
    QString text     = mainWindow->ui->TextEdit->toPlainText();
    QString alphabet = ui->AlphabetLineEdit->text();
    int     shift    = ui->ShiftSpinBox->value();

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

    if (encryptionMode == Ui::EncryptionMode::Encrypt)
    {
        QString encryptedText = Cyphers::Caesar(text, alphabet, shift);
        mainWindow->ui->TextEdit->setText(encryptedText);
    }
    else
    {
        QString decryptedText = Cyphers::Caesar(text, alphabet, -shift);
        mainWindow->ui->TextEdit->setText(decryptedText);
    }

    accept();
}
