#ifndef TEXTINSYMBOLSWINDOW_H
#define TEXTINSYMBOLSWINDOW_H

#include <QWidget>

namespace Ui {
class TextInSymbolsWindow;
}

class TextInSymbolsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TextInSymbolsWindow(QWidget *parent, QImage textInSymbols);
    ~TextInSymbolsWindow();

private slots:
    void on_SaveImagePushButton_clicked();

private:
    Ui::TextInSymbolsWindow *ui;
};

#endif // TEXTINSYMBOLSWINDOW_H
