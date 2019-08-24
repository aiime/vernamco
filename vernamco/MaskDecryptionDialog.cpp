#include <QMessageBox>
#include <QSettings>
#include <QDir>

#include "MaskDecryption.h"
#include "MaskDecryptionDialog.h"

#include "ui_MaskDecryptionDialog.h"
#include "ui_MainWindow.h"

MaskDecryptionDialog::MaskDecryptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaskDecryptionDialog),
    mainWindow(static_cast<MainWindow*>(parent))
{
    ui->setupUi(this);
}

MaskDecryptionDialog::~MaskDecryptionDialog()
{
    delete ui;
}

void MaskDecryptionDialog::on_DecryptionPushButton_clicked()
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

    QString encryptedText = MaskDecryption::decryptText(text, alphabet, mask);
    mainWindow->ui->TextEdit->setText(encryptedText);

    accept();
}

QVector<int> MaskDecryptionDialog::strVectorToIntVector(QVector<QString> strVector)
{
    QVector<int> intVector;
    for (int i = 0; i < strVector.size(); i++)
    {
       intVector.append(strVector[i].toInt());
    }
    return intVector;
}

void MaskDecryptionDialog::on_AlphabetFromIniPushButton_clicked()
{
    QSettings setting(QCoreApplication::applicationDirPath() + "/vernamco.ini", QSettings::IniFormat);
    QString alphabet = setting.value("alphabet", "").toString();
    ui->AlphabetLineEdit->setText(alphabet);
}

void MaskDecryptionDialog::on_MaskFromIniPushButton_clicked()
{
    QSettings setting(QCoreApplication::applicationDirPath() + "/vernamco.ini", QSettings::IniFormat);
    QString mask = setting.value("mask", "").toString();
    ui->MaskLineEdit->setText(mask);
}
