#include <QMessageBox>

#include "MaskEncryption.h"
#include "MaskEncryptionDialog.h"

#include "ui_MaskEncryptionDialog.h"
#include "ui_MainWindow.h"

MaskEncryptionDialog::MaskEncryptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaskEncryptionDialog),
    mainWindow(static_cast<MainWindow*>(parent))
{
    ui->setupUi(this);
}

MaskEncryptionDialog::~MaskEncryptionDialog()
{
    delete ui;
}

void MaskEncryptionDialog::on_EncryptionPushButton_clicked()
{
    // Get text.
    QString text = mainWindow->ui->TextEdit->toPlainText();

    // Get alphabet.
    QString alphabet = ui->AlphabetLineEdit->text();

    // Get mask.
    QVector<QString> strMask = ui->MaskLineEdit->text().split("-").toVector();
    QVector<int> mask = strVectorToIntVector(strMask);

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

    if (mask.size() == 0)
    {
        QMessageBox::critical(this, "Error", "Mask required");
        return;
    }

    QString encryptedText = MaskEncryption::encryptText(text, alphabet, mask);
    mainWindow->ui->TextEdit->setText(encryptedText);

    accept();
}

QVector<int> MaskEncryptionDialog::strVectorToIntVector(QVector<QString> strVector)
{
    QVector<int> intVector;
    for (int i = 0; i < strVector.size(); i++)
    {
       intVector.append(strVector[i].toInt());
    }
    return intVector;
}
