#include "AlphabetExtractor.h"

QString AlphabetExtractor::extractAlphabet(QString rawAlphabet)
{
    QString alphabet("");
    for (int i = 0; i < rawAlphabet.length(); i++)
    {
        if (rawAlphabet[i] != "\\") alphabet.append(rawAlphabet[i]);
        else
        {
            if (rawAlphabet[i + 1] == 'n') alphabet.append('\n');
            i++;
        }
    }
    return alphabet;
}
