#ifndef MASKENCRYPTIONDIALOG_H
#define MASKENCRYPTIONDIALOG_H

#include <QDialog>
#include "MainWindow.h"

namespace Ui {
class MaskEncryptionDialog;
}

class MaskEncryptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaskEncryptionDialog(QWidget *parent = nullptr);
    ~MaskEncryptionDialog();
    Ui::MaskEncryptionDialog *ui;

private slots:
    void on_EncryptionPushButton_clicked();

    void on_AlphabetFromIniPushButton_clicked();

    void on_MaskFromIniPushButton_clicked();

private:
    MainWindow *mainWindow;
    QVector<int> strVectorToIntVector(QVector<QString> strVector);
};

#endif
