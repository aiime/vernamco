#ifndef SYMBOLREPLACEMENTDIALOG_H
#define SYMBOLREPLACEMENTDIALOG_H

#include <QDialog>
#include <MainWindow.h>

namespace Ui {
class SymbolReplacementDialog;
}

class SymbolReplacementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SymbolReplacementDialog(QWidget *parent = nullptr);
    ~SymbolReplacementDialog();

private slots:
    void on_EncryptionPushButton_clicked();

    void on_SelectSymbolPushButton_clicked();

    void on_AlphabetFromIniPushButton_clicked();

private:
    Ui::SymbolReplacementDialog *ui;
    MainWindow *mainWindow;
    QVector<QImage> symbols;
};

#endif // SYMBOLREPLACEMENTDIALOG_H
