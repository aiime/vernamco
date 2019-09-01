#include "SymbolReplacement.h"
#include <QPainter>
#include <QBrush>
#include <math.h>

QImage SymbolReplacement::replaceCharactersWithSymbols(QString text,
                                                       QString alphabet,
                                                       QVector<QImage> symbols,
                                                       int symbolsPerLine)
{
    QPainter painter;
    int x = 0; // Coordinate for painter.
    int y = 0; // Coordinate for painter.
    int symbolSideLength = symbols[0].width(); // Increment for coordinates.
    int textInSymbolsWidth = symbolSideLength * symbolsPerLine;
    int textInSymbolsHeight = symbolSideLength * static_cast<int>(ceil(text.length() / static_cast<double>(symbolsPerLine)));
    QImage textInSymbols(textInSymbolsWidth,textInSymbolsHeight, QImage::Format_RGB32);

    painter.begin(&textInSymbols);
    painter.fillRect(0,0, textInSymbolsWidth, textInSymbolsHeight, Qt::white);

    for (int i = 0; i < text.length();)
    {
        for (int j = 0; j < symbolsPerLine && i < text.length(); j++, i++)
        {
            int charIndex = alphabet.indexOf(text[i]);
            int symbolIndex = charIndex;
            painter.drawImage(x, y, symbols[symbolIndex]);
            x += symbolSideLength;
        }
        x = 0;
        y += symbolSideLength;
    }

    painter.end();

    return textInSymbols;
}
