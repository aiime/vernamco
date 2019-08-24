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

private:
    MainWindow *mainWindow;
    QVector<int> strVectorToIntVector(QVector<QString> strVector);
};

#endif
