#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "xmlParcer.h"
#include "Token.h"
#include "CException.h"
#include "ErrorObject.h"
#include <string.h>
#include "linkedlist.h"


/*
 * Function that start to received token.
 *
 */
void checkToken(XmlList *xmlList){
	Token *token = malloc(sizeof(Token));
	Token *nextToken = malloc(sizeof(Token));
	OperatorToken* operator = malloc(sizeof(OperatorToken));
	StringToken* content = malloc(sizeof(StringToken));
	IdentifierToken* tag = malloc(sizeof(IdentifierToken));
	XmlElement *xmlElement = malloc(sizeof(XmlElement));
  xmlElement = createXmlElement(NULL, 0); 
	
	token = getToken();     // check the first token whether it is "<" or not
	if(token->type == TOKEN_OPERATOR_TYPE){
		operator = (OperatorToken*)token;
		printf("%s", operator->symbol);
		if(strcmp(operator->symbol, "<") == -1){ // Check whether the first token is "<"  
			Throw(ERR_NO_OPEN_BRACKET);
		}
	}
	else
		throwError("Missing left angle bracket.",ERR_NO_OPEN_BRACKET);
  
  xmlList = createXmlList();
	checkLoop(xmlList, xmlElement, token, 0);
	
	printf("%d", xmlList->length);
 
	
}

/* 
 * Check the next token contains "/" or a tag after received "<" symbol.
 * Else throw error.  
 *  
 */
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement, int endTag){
  OperatorToken* operator = malloc(sizeof(OperatorToken));
  IdentifierToken* tag = malloc(sizeof(IdentifierToken));
  Token *token = malloc(sizeof(Token));
  token = getToken();
  
  if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if (strcmp(operator->symbol, "/") == 0)
      return GET_SLASH_CLOSE;
    else
      throwError("missing something", ERR_NO_TAG);
  }
  
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    tag = (IdentifierToken*)token;
    printf("%s", tag->str); // print
    if (endTag == 0) {
      xmlElement->data = tag->str;
			addList(xmlElement, newXmlElement, xmlList);
      return GET_TAG_OPEN;
    }
    else {
      if(strcmp(xmlElement->data, tag->str) != 0){
			newXmlElement->data = tag->str;
			addList(xmlElement, newXmlElement, xmlList);
			return GET_NEW_TAG;
			}
      else
        throwError("missing slash", ERR_NO_TAG);
    }
  }
  else 
    throwError("missing something", ERR_NO_TAG);
}

/* 
 * Check the next token contains ">" or "/" after received a tag.
 * Else throw error.  
 *  
 */
ElementType xmlTag(XmlList *xmlList, int closeTag){
  Token *token = malloc(sizeof(Token));
  OperatorToken* operator = malloc(sizeof(OperatorToken));
  token = getToken();
  if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if (strcmp(operator->symbol, "/") == 0){
      return GET_SLASH_SELFCLOSE;
    }
    else if (strcmp(operator->symbol, ">") == 0){
      if(closeTag == 1)
        return GET_END;
      else
        return GET_CLOSEANGLEBRACKET;
    }
  }
  else
    throwError("missing close bracket", ERR_NO_CLOSING_BRACKET);
}

/* 
 * Check the next token contains string content or "<" after received ">" symbol.
 * Else throw error.  
 *  
 */
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement){
  Token *token = malloc(sizeof(Token));
  StringToken *content = malloc(sizeof(StringToken));
  OperatorToken* operator = malloc(sizeof(OperatorToken));
	XmlElement *contentElement = malloc(sizeof(XmlElement));
  token = getToken();
	
  if(token->type == TOKEN_STRING_TYPE){
    content = (StringToken*)token;
    printf("%s", content->str); // print
		contentElement = createXmlElement(content->str, XML_CONTENT);
		addList(xmlElement, contentElement, xmlList);
    return GET_CONTENT;
  }
  else if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if (strcmp(operator->symbol, "<") == 0){
      return GET_OPENANGLEBRACKET;
    }
  }
}

/* 
 * Check the next token contains ">" or a tag after received "/" symbol.
 * Else throw error.  
 *  
 */
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, int closeTag, int selfClose){
  Token *token = malloc(sizeof(Token));
  IdentifierToken *tag = malloc(sizeof(IdentifierToken));
  OperatorToken* operator = malloc(sizeof(OperatorToken));
  token = getToken();
  
  if ((selfClose == 1) && (closeTag == 1)){
    throwError("contain two slash", ERR_NO_CLOSING_BRACKET);
  }
  else if ((selfClose == 1) && (token->type == TOKEN_OPERATOR_TYPE)){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if(strcmp(operator->symbol, ">") == 0){
      return GET_END;
    }
    else
      throwError("missing bracket", ERR_NO_CLOSING_BRACKET);
  }
  else if ((closeTag == 1) && (token->type == TOKEN_IDENTIFIER_TYPE)){
    tag = (IdentifierToken*)token;
    printf("%s", tag->str); // print
    if (strcmp(xmlElement->data, tag->str) == 0)
      return GET_END;
    else
      throwError("missing bracket", ERR_NO_CLOSING_BRACKET);
  }
  else
    throwError("what the", ERR_NO_CLOSING_BRACKET);
  
}

/* 
 * Check the next token contains string content or "<" after received a string content.
 * Else throw error.  
 *  
 */
ElementType xmlContent(XmlList *xmlList, XmlElement *xmlElement){
  Token *token = malloc(sizeof(Token));
  StringToken *content = malloc(sizeof(StringToken));
  OperatorToken* operator = malloc(sizeof(OperatorToken));
	XmlElement *contentElement = malloc(sizeof(XmlElement));
  token = getToken();
  
  if (token->type == TOKEN_STRING_TYPE){
    content = (StringToken*)token;
    printf("%s", content->str); // print
    contentElement = createXmlElement(content->str, XML_CONTENT);
		addList(xmlElement, contentElement, xmlList);
    return GET_CONTENT;
  }
  else if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if(strcmp(operator->symbol, "<") == 0)
      return GET_OPENANGLEBRACKET;
    else 
      throwError("missing bracket", ERR_NO_CLOSING_BRACKET);
  }
  else
    throwError("missing bracket", ERR_NO_CLOSING_BRACKET);
}

/*
 * Check whether the last token is ">" or not.
 * Else throw error..
 *
 */
void checkLastToken(){
  Token *token = malloc(sizeof(Token));
  OperatorToken* operator = malloc(sizeof(OperatorToken));
  token = getToken();
  
  if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if (strcmp(operator->symbol, ">") == 0){
      
    }
    else 
      throwError("missing bracket", ERR_NO_CLOSING_BRACKET);
  }
  else 
    throwError("missing bracket", ERR_NO_CLOSING_BRACKET);
}


int checkLoop(XmlList *xmlList,XmlElement *xmlElement, Token *token, int loop){
  ElementType getType;
  int selfClose = 0;
  int closeTag = 0;
  int end = 0;

  XmlElement *newXmlElement = malloc(sizeof(XmlElement));
  newXmlElement = createXmlElement(NULL, 0);
  
  if (loop == 0)
    getType = openAngleBracket(xmlList, xmlElement, newXmlElement, 0);
  else
    getType = xmlTag(xmlList, 0);
	
  while (end != 1){
    switch (getType){
      case GET_SLASH_CLOSE:
        closeTag = 1;
        getType = slash(xmlList, xmlElement, closeTag, selfClose);
        break;
      case GET_SLASH_SELFCLOSE:
        selfClose = 1;
        getType = slash(xmlList, xmlElement, closeTag, selfClose);
        break;
      case GET_TAG_OPEN:
        getType = xmlTag(xmlList, 0);
        break;
      case GET_TAG_CLOSE:
        getType = xmlTag(xmlList, 1);
        break;
      case GET_CLOSEANGLEBRACKET:
        getType = closeAngleBracket(xmlList, xmlElement);
        break;
      case GET_END:
        checkLastToken();
        end = 1;
        break;
      case GET_NEW_TAG:
        checkLoop(xmlList, newXmlElement, token, 1);
        getType = GET_CLOSEANGLEBRACKET;
        break;
      case GET_OPENANGLEBRACKET:
        getType = openAngleBracket(xmlList, xmlElement, newXmlElement, 1);
        break;
      case GET_CONTENT:
        getType = xmlContent(xmlList, xmlElement);
        break;
    }
    
  }
}

XmlElement *createXmlElement(char *data, XmlElementType type){
	XmlElement *xmlElement = malloc(sizeof(XmlElement));
	xmlElement->next = NULL;
	xmlElement->child = NULL;
	xmlElement->data = data;
	xmlElement->type = type;
	return xmlElement;
}

XmlList *createXmlList(){
	XmlList *xmlList = malloc(sizeof(XmlList));
	xmlList->head = NULL;
	xmlList->tail = NULL;
	xmlList->length = 0;
	return xmlList;
}

void addList(XmlElement *xmlElement, XmlElement *newXmlElement, XmlList *xmlList){
  XmlElement *tempElement = malloc(sizeof(XmlElement));
	if(xmlList->head == NULL){ 
		xmlList->head = xmlElement;
		xmlList->tail = xmlElement;
	}
	
	else{
		xmlList->tail = xmlElement;
    
    if(xmlElement->child == NULL)
      xmlElement->child = newXmlElement;
    else{
      while(xmlList->tail->child->next != NULL){
        xmlList->tail->child = xmlList->tail->child->next;
      }
      xmlList->tail->child->next = newXmlElement;
      xmlList->tail = newXmlElement;
    }
      
    

	}
	xmlList->length++;
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
