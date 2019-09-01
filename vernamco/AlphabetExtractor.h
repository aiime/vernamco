#ifndef ALPHABETEXTRACTOR_H
#define ALPHABETEXTRACTOR_H

#include <QString>

class AlphabetExtractor
{
public:
    static QString extractAlphabet(QString rawAlphabet);
private:
    AlphabetExtractor(); // Static class.
};

#endif // ALPHABETEXTRACTOR_H
