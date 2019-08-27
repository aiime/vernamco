#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>

#include "MaskEncryption.h"
#include "MaskEncryptionDialog.h"

#include "ui_MaskEncryptionDialog.h"
#include "ui_MainWindow.h"

MaskEncryptionDialog::MaskEncryptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaskEncryptionDialog),
    mainWindow(static_cast<MainWindow*>(parent)),
    fileAsMask(false)
{
    ui->setupUi(this);
}

MaskEncryptionDialog::~MaskEncryptionDialog()
{
    delete ui;
}
#include <QDebug>
void MaskEncryptionDialog::on_EncryptionPushButton_clicked()
{
    // Get text.
    QString text = mainWindow->ui->TextEdit->toPlainText();

    // Get alphabet.
    QString alphabet = ui->AlphabetLineEdit->text();

    // Get mask.
    QVector<int> mask;
    qDebug() << fileAsMask;
    if (fileAsMask)
    {
        for (QByteArray::iterator it = fileAsByteArray.begin(); it != fileAsByteArray.end(); it++)
        {
            mask.push_back(*it);
        }
    }
    else
    {
        QVector<QString> strMask = ui->MaskLineEdit->text().split("-").toVector();
        mask = strVectorToIntVector(strMask);
    }

    // Check for errors.
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

void MaskEncryptionDialog::on_AlphabetFromIniPushButton_clicked()
{
    QSettings setting(QCoreApplication::applicationDirPath() + "/vernamco.ini", QSettings::IniFormat);
    QString alphabet = setting.value("alphabet", "").toString();
    ui->AlphabetLineEdit->setText(alphabet);
}

void MaskEncryptionDialog::on_MaskFromIniPushButton_clicked()
{
    QSettings setting(QCoreApplication::applicationDirPath() + "/vernamco.ini", QSettings::IniFormat);
    QString mask = setting.value("mask", "").toString();
    ui->MaskLineEdit->setText(mask);
}

void MaskEncryptionDialog::on_MaskFromFilePushButton_clicked()
{
    // Get path of file.
    QFileDialog openDialog(this);
    openDialog.setFileMode(QFileDialog::ExistingFile);
    if (!openDialog.exec()) return;
    QString textFilePath = openDialog.selectedFiles()[0];

    // Open file.
    QFile file(textFilePath);
    file.open(QIODevice::ReadOnly);
    fileAsByteArray = file.readAll();

    // Set flag for future encryption.
    fileAsMask = true;

    // Print bytes of file.
    QString maskAsString;
    if (fileAsByteArray.size() > 20)
    {
        // Print only first 20 bytes.
        QByteArray::iterator it = fileAsByteArray.begin();
        for (int i = 0; i < 20; i++)
        {
            maskAsString.append(QString::number(static_cast<unsigned char>(*it)));
            maskAsString.append("-");
            it++;
        }
        maskAsString.truncate(maskAsString.size() - 1); // Delete trailing "-".
        maskAsString.append("...");
    }
    else
    {
        // Print all bytes.
        for (QByteArray::iterator it = fileAsByteArray.begin(); it != fileAsByteArray.end(); it++)
        {
            maskAsString.append(QString::number(static_cast<unsigned char>(*it)));
            maskAsString.append("-");
        }
        maskAsString.truncate(maskAsString.size() - 1); // Delete trailing "-".
    }

    ui->MaskLineEdit->setText(maskAsString);
}
