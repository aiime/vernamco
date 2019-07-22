#ifndef CAESAR_H
#define CAESAR_H

#include <string>

using namespace std;

class Caesar
{
public:
    Caesar();
    static string Encrypt(string text, string alphabet );
};

#endif // CAESAR_H
