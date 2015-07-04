#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "xmlParcer.h"
#include "Token.h"
#include "CException.h"
#include "ErrorObject.h"
#include <string.h>


Tag checkToken(int numToken){
	Tag lol;
	Token *token = malloc(sizeof(Token));
	Token *nextToken = malloc(sizeof(Token));
	OperatorToken* operator = malloc(sizeof(OperatorToken));
	StringToken* content = malloc(sizeof(StringToken));
	IdentifierToken* tag = malloc(sizeof(IdentifierToken));
	int expectTokenType;
  
	
	token = getToken();
	numToken--;
	if(token->type == TOKEN_OPERATOR_TYPE){
		operator = (OperatorToken*)token;
		printf("%s", operator->symbol);
		if(strcmp(operator->symbol, "<") == -1){ // Check whether the first token is "<"  
			Throw(ERR_NO_OPEN_BRACKET);
		}
	}
	else
		throwError("Missing left angle bracket.",ERR_NO_OPEN_BRACKET);
	
  while (numToken > 0){  
		nextToken = getToken();
			switch (token->type){
				printf("%d", nextToken->type);
				case TOKEN_OPERATOR_TYPE:
					operator = (OperatorToken*)token;
					if ((strcmp(operator->symbol, "<") == 0) && nextToken->type == TOKEN_IDENTIFIER_TYPE){
						tag = (IdentifierToken*)nextToken;
						printf("%s", tag->str);
					}
					else if ((strcmp(operator->symbol, ">") == 0) && nextToken->type == TOKEN_STRING_TYPE){
						content = (StringToken*)nextToken;
						printf("%s", content->str);
					}
					else if ((strcmp(operator->symbol, "<") == 0) && nextToken->type == TOKEN_OPERATOR_TYPE){
						operator = (OperatorToken*)nextToken;
						printf("%s", operator->symbol);
					}
					else if ((strcmp(operator->symbol, "/") == 0) && nextToken->type == TOKEN_IDENTIFIER_TYPE){
						tag = (IdentifierToken*)nextToken;
						printf("%s", tag->str);
					}
					else if ((strcmp(operator->symbol, "/") == 0) && nextToken->type == TOKEN_OPERATOR_TYPE){
						tag = (IdentifierToken*)nextToken;
						printf("%s", tag->str);
					}
					
					else if ((strcmp(operator->symbol, "<") == 0) && nextToken->type == TOKEN_STRING_TYPE)
						Throw(ERR_NO_TAG);
					else if ((strcmp(operator->symbol, ">") == 0) && nextToken->type == TOKEN_IDENTIFIER_TYPE)
						Throw(ERR_NO_OPEN_BRACKET);
					else {
						Throw(ERR_NO_OPEN_BRACKET);
					}
					break;
					
				case TOKEN_IDENTIFIER_TYPE:
					tag = (IdentifierToken*)token;
					if(nextToken->type == TOKEN_OPERATOR_TYPE){
						operator = (OperatorToken*)nextToken;
						printf("%s", operator->symbol);
					}
					else {
						Throw(ERR_NO_OPEN_BRACKET);
					}
					break;
					
				case TOKEN_STRING_TYPE:
					content = (StringToken*)token;
					if(nextToken->type == TOKEN_OPERATOR_TYPE){
						operator = (OperatorToken*)nextToken;
						printf("%s", operator->symbol);
					}
					else if(nextToken->type == TOKEN_STRING_TYPE){
						content = (StringToken*)nextToken;
						printf("%s", content->str);
					}
					else {
						Throw(ERR_NO_OPEN_BRACKET);
					}
					break;
			}
		token = nextToken;	
		numToken--;
  }
	if(token->type == TOKEN_OPERATOR_TYPE){
		operator = (OperatorToken*)token;
		if(strcmp(operator->symbol, ">") == -1){ // Check whether the last token is ">"  
			Throw(ERR_NO_OPEN_BRACKET);
		}
	}
	else
		Throw(ERR_NO_OPEN_BRACKET);
	return lol;
}

void printIntegerNumberError(int errorCode){
    switch(errorCode){
    case ERR_NO_OPEN_BRACKET:
      printf("\nMissing a left angle bracket.\n");
      break;
    case ERR_NO_CLOSING_BRACKET:
      printf("\nMissing a right angle bracket.\n");
      break;
    case ERR_NO_TAG:
      printf("\nMissing a tag.\n\n");
      break;
    default:
      printf("Error caught! Error code is: %d\n", errorCode);
      break;
    }

}


OperatorToken *createOperatorToken(char* symbol){
  OperatorToken* op = malloc(sizeof(OperatorToken));
  op->symbol = symbol;
  op->type = TOKEN_OPERATOR_TYPE;
  return op;
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
