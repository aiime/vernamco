#ifndef CYPHERS_H
#define CYPHERS_H

#include <QMainWindow>

using namespace std;

class Cyphers
{
public:
    static QString Caesar(QString text, QString alphabet, int shift);
};

#endif
