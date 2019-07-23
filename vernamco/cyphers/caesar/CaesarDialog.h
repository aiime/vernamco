#ifndef CAESARDIALOG_H
#define CAESARDIALOG_H

#include <QDialog>
#include "../../MainWindow.h"

namespace Ui {
    enum EncryptionMode { Encrypt, Decrypt };

    class CaesarDialog;
    }

    class CaesarDialog : public QDialog
    {
        Q_OBJECT

    public:
        explicit CaesarDialog(QWidget *parent, Ui::EncryptionMode encryptionMode);
        ~CaesarDialog();

    private slots:
        void on_EncryptionPushButton_clicked();

    private:
        Ui::CaesarDialog *ui;
        MainWindow *mainWindow;
        Ui::EncryptionMode encryptionMode;
};

#endif // CAESARDIALOG_H
