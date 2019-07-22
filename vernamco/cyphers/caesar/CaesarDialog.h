#ifndef CAESARDIALOG_H
#define CAESARDIALOG_H

#include <QDialog>
#include "../../MainWindow.h"

namespace Ui {
class CaesarDialog;
}

class CaesarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CaesarDialog(QWidget *parent = nullptr);
    ~CaesarDialog();

private slots:
    void on_EncryptPushButton_clicked();

private:
    Ui::CaesarDialog *ui;
    MainWindow *mainWindow;
};

#endif // CAESARDIALOG_H
