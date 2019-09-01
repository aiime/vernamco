#include "TextInSymbolsWindow.h"
#include "ui_TextInSymbolsWindow.h"
#include <QFileDialog>

TextInSymbolsWindow::TextInSymbolsWindow(QWidget *parent, QImage textInSymbols) :
    QWidget(parent),
    ui(new Ui::TextInSymbolsWindow)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    ui->TextInSymbolsImage->setPixmap(QPixmap::fromImage(textInSymbols));
    this->resize(textInSymbols.width(), textInSymbols.height());
}

TextInSymbolsWindow::~TextInSymbolsWindow()
{
    delete ui;
}

void TextInSymbolsWindow::on_SaveImagePushButton_clicked()
{
    const QPixmap* textInSymbols = ui->TextInSymbolsImage->pixmap();
    QString textInSymbolsPath = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("Image (*.png)"));

    if(textInSymbolsPath == "") return;

    textInSymbols->save(textInSymbolsPath);
}
