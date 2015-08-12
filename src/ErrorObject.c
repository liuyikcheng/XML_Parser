#include <malloc.h>
#include <stdio.h>
#include "ErrorObject.h"
#include "CException.h"
#include "Token.h"

#define TokenOpSymbol   ((OperatorToken*)token)->symbol
#define TokenIdStr      ((IdentifierToken*)token)->str
#define TokenStrStr     ((StringToken*)token)->str
#define TokenIntVal     ((IntegerToken*)token)->value
#define TokenFloatVal   ((FloatToken*)token)->value

void throwError(char *message, ErrorCode errCode, Token *token){
  ErrorObject *errObj = malloc(sizeof(ErrorObject));
  char *msg = malloc(sizeof(char)*100);
  char *num = malloc(sizeof(char)*100);
  
  
  if (token->type == TOKEN_OPERATOR_TYPE)
    sprintf(msg, "%s but received '%s'.", message, TokenOpSymbol);
  else if (token->type == TOKEN_INTEGER_TYPE){
    sprintf(num, "%d", TokenIntVal);
    sprintf(msg, "%s but received '%s'.", message, num);
  }
  else if (token->type == TOKEN_FLOAT_TYPE){
    sprintf(num, "%.2f", TokenFloatVal);
    sprintf(msg, "%s but received '%s'.", message, num);
  }
  else if (token->type == TOKEN_STRING_TYPE)
    sprintf(msg, "%s but received '%s'.", message, TokenStrStr);
  else if (token->type == TOKEN_IDENTIFIER_TYPE)
    sprintf(msg, "%s but received '%s'.", message, TokenIdStr);
  else
    sprintf(msg, "%s but received unknown object.", message);
  
  errObj->errorMsg = msg;
  errObj->errorCode = errCode;
  Throw(errObj);
}
