#ifndef ErrorObject_H
#define ErrorObject_H

#include "Token.h"

typedef enum {
  ERR_NO_OPEN_BRACKET,
  ERR_NO_CLOSING_BRACKET,
  ERR_NO_SLASH,
  ERR_WRONG_TAG,
  ERR_NO_TAG,
  ERR_TOKEN_TYPE,
  ERR_NO_ELEMENT
} ErrorCode;

typedef struct{
  char *errorMsg;
  ErrorCode errorCode;
} ErrorObject;


void throwError(char *message, ErrorCode errCode, Token *token);


#endif // ErrorObject_H
