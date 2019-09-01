#ifndef SYMBOLREPLACEMENT_H
#define SYMBOLREPLACEMENT_H

#include <QImage>

class SymbolReplacement
{
public:
    static QImage replaceCharactersWithSymbols(QString text, QString alphabet, QVector<QImage> symbols, int symbolsPerLine);
private:
    SymbolReplacement(); // Static class.
};

#endif // SYMBOLREPLACEMENT_H
