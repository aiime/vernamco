#include <QMessageBox>
#include <QImage>
#include <QFileDialog>
#include <QSettings>

#include <TextInSymbolsWindow.h>
#include <SymbolReplacementDialog.h>
#include <SymbolReplacement.h>
#include <ui_MainWindow.h>
#include <ui_SymbolReplacementDialog.h>
#include <AlphabetExtractor.h>

SymbolReplacementDialog::SymbolReplacementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SymbolReplacementDialog),
    mainWindow(static_cast<MainWindow*>(parent))
{
    ui->setupUi(this);
}

SymbolReplacementDialog::~SymbolReplacementDialog()
{
    delete ui;
}

void SymbolReplacementDialog::on_EncryptionPushButton_clicked()
{
    // Collect values from window.
    QString text       = mainWindow->ui->TextEdit->toPlainText();
    QString alphabet   = AlphabetExtractor::extractAlphabet(ui->AlphabetLineEdit->text());
    int symbolsPerLine = ui->SymbolsPerLineSpinBox->value();

    // Check values for errors.
    if (text == "")
    {
        QMessageBox::critical(this, "Error", "Text required"); return;
    }
    if (alphabet == "")
    {
        QMessageBox::critical(this, "Error", "Alphabet required"); return;
    }
    if (symbolsPerLine == 0)
    {
        QMessageBox::critical(this, "Error", "Symbols per line required"); return;
    }
    if (symbols.size() == 0)
    {
        QMessageBox::critical(this, "Error", "Symbols required"); return;
    }

    // Get symbol representation of text.
    QImage textInSymbols = SymbolReplacement::replaceCharactersWithSymbols(text, alphabet, symbols, symbolsPerLine);

    // Create window with text in symbols.
    TextInSymbolsWindow *textInSymbolsWindow = new TextInSymbolsWindow(nullptr, textInSymbols);
    textInSymbolsWindow->show();

    accept();
}

void SymbolReplacementDialog::on_SelectSymbolPushButton_clicked()
{
    // Get paths of symbols.
    QFileDialog openDialog(this);
    openDialog.setFileMode(QFileDialog::ExistingFiles);
    openDialog.setNameFilter(tr("Images (*.png)"));
    if (!openDialog.exec()) return;
    QStringList symbolPaths = openDialog.selectedFiles();

    // Create symbol vector.
    for (int i = 0; i < symbolPaths.size(); i++)
    {
        symbols.append(QImage(symbolPaths[i]));
    }
}

void SymbolReplacementDialog::on_AlphabetFromIniPushButton_clicked()
{
    QSettings setting(QCoreApplication::applicationDirPath() + "/vernamco.ini", QSettings::IniFormat);
    QString alphabet = setting.value("alphabet", "").toString();
    ui->AlphabetLineEdit->setText(alphabet);
}
