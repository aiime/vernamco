#include <QMessageBox>
#include <QSettings>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

#include "MaskDecryption.h"
#include "MaskDecryptionDialog.h"

#include "ui_MaskDecryptionDialog.h"
#include "ui_MainWindow.h"
#include <AlphabetExtractor.h>

MaskDecryptionDialog::MaskDecryptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaskDecryptionDialog),
    mainWindow(static_cast<MainWindow*>(parent)),
    fileAsMask(false)
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
    QString alphabet = AlphabetExtractor::extractAlphabet(ui->AlphabetLineEdit->text());

    // Get mask.
    QVector<int> mask;
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

void MaskDecryptionDialog::on_MaskFromFilePushButton_clicked()
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

    // Set flag for future decryption.
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
