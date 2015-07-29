#ifndef TokenCreate_H
#define TokenCreate_H
#include "Token.h"

OperatorToken *createOperatorToken(char* symbol);
StringToken *createStringToken(char* str);
IdentifierToken *createIdentifierToken(char* str);

#endif // TokenCreate_H
