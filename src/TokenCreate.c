#include "TokenCreate.h"
#include <malloc.h>
#include "Token.h"
#include "xmlParcer.h"

OperatorToken *createOperatorToken(char* symbol){
  OperatorToken* op = malloc(sizeof(OperatorToken));
  op->symbol = symbol;
  op->type = TOKEN_OPERATOR_TYPE;
  return op;
}

IntegerToken *createIntegerToken(int value){
  IntegerToken *number = malloc(sizeof(IntegerToken));
  number->value = value;
  number->type = TOKEN_INTEGER_TYPE;
  return number;
}

FloatToken *createFloatToken(float value){
  FloatToken *number = malloc(sizeof(FloatToken));
  number->value = value;
  number->type = TOKEN_FLOAT_TYPE;
  return number;
}

StringToken *createStringToken(char* str){
  StringToken* st = malloc(sizeof(StringToken));
  st->str = str;
  st->type = TOKEN_STRING_TYPE;
  return st;
}

IdentifierToken *createIdentifierToken(char* str){
  IdentifierToken* id = malloc(sizeof(IdentifierToken));
  id->str = str;
  id->type = TOKEN_IDENTIFIER_TYPE;
  return id;
}