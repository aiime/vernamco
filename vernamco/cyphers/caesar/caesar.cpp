#include <algorithm>
#include "../Cyphers.h"

QString Cyphers::Caesar(QString text, QString alphabet, int shift)
{
    // Check if decryption required
    if (shift < 0)
    {
        std::reverse(alphabet.begin(), alphabet.end());
        shift = -shift;
    }

    QString encryptedText = "";

    for (int i = 0; i < text.length(); i++)
    {
        QChar symbol = text[i];

        if(!symbol.isLetterOrNumber())
        {
            encryptedText.push_back(symbol);
            continue;
        }

        int symbolPosition = alphabet.indexOf(symbol.toLower());
        QChar newSymbol = alphabet[(symbolPosition + shift) % alphabet.length()];
        if (symbol.isUpper()) newSymbol = newSymbol.toUpper();

        encryptedText.push_back(newSymbol);
    }

    return encryptedText;
}
