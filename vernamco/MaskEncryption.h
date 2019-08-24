#ifndef MASKENCRYPTION_H
#define MASKENCRYPTION_H

#include <QString>

using namespace std;

class MaskEncryption
{
public:
    static QString encryptText(QString text, QString alphabet, QVector<int> mask);
private:
    MaskEncryption(); // Static class.
};

#endif
