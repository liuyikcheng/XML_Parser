#ifndef xmlParcer_H
#define xmlParcer_H
#include "Token.h"


Tag checkToken(int numToken);

OperatorToken *createOperatorToken(char* symbol);
StringToken *createStringToken(char* str);
IdentifierToken *createIdentifierToken(char* str);

#endif // xmlParcer_H
