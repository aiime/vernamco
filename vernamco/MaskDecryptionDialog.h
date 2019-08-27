#ifndef MASKDECRYPTIONDIALOG_H
#define MASKDECRYPTIONDIALOG_H

#include <QDialog>
#include "MainWindow.h"

namespace Ui {
class MaskDecryptionDialog;
}

class MaskDecryptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaskDecryptionDialog(QWidget *parent = nullptr);
    ~MaskDecryptionDialog();
    Ui::MaskDecryptionDialog *ui;

private slots:
    void on_DecryptionPushButton_clicked();

    void on_AlphabetFromIniPushButton_clicked();

    void on_MaskFromIniPushButton_clicked();

    void on_MaskFromFilePushButton_clicked();

private:
    MainWindow *mainWindow;
    QVector<int> strVectorToIntVector(QVector<QString> strVector);
    QByteArray fileAsByteArray;
    bool fileAsMask;
};

#endif
