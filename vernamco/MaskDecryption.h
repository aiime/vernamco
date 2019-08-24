#ifndef MASKDECRYPTION_H
#define MASKDECRYPTION_H

#include <QString>

using namespace std;

class MaskDecryption
{
public:
    static QString decryptText(QString text, QString alphabet, QVector<int> mask);
private:
    MaskDecryption(); // Static class.
};

#endif
