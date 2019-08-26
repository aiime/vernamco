#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private:
    QString openedFile;

private slots:
    void on_MaskEncryption_triggered();
    void on_MaskDecryption_triggered();
    void on_Open_triggered();
    void on_Save_triggered();
    void on_SaveAs_triggered();
    void on_Close_triggered();
    void on_Exit_triggered();
};

#endif
