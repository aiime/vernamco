#include "MaskDecryption.h"
#include <QVector>

using namespace std;

/*!
 * \brief ALWAYS check if text contains only symbols from alphabet before call this method.
 */
QString MaskDecryption::decryptText(QString text, QString alphabet, QVector<int> mask)
{
    text = text.toLower();
    text = text.simplified();

    QString decryptedText = "";

    int i = 0;
    int j = 0;
    while(i < text.length())
    {
        QChar currentSymbol = text[i];
        int   currentShift  = mask[j];

        int currentSymbolPosition = alphabet.indexOf(currentSymbol);
        int newSymbolPosition = (currentSymbolPosition - currentShift) % alphabet.length();
        if (newSymbolPosition < 0)
        {
            newSymbolPosition = alphabet.length() + newSymbolPosition;
        }
        QChar newSymbol = alphabet[newSymbolPosition];

        decryptedText.push_back(newSymbol);

        i++;
        j++;
        j = j % mask.size(); // loop j
    }

    return decryptedText;
}
