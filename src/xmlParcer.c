#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "xmlParcer.h"
#include "Token.h"
#include "CException.h"
#include "ErrorObject.h"
#include "linkedlist.h"

#define TokenOpSymbol   ((OperatorToken*)token)->symbol
#define TokenIdStr      ((IdentifierToken*)token)->str
#define TokenStrStr     ((StringToken*)token)->str
#define TokenIntVal     ((IntegerToken*)token)->value
#define TokenFloatVal   ((FloatToken*)token)->value


/*
 * Function that start to received token.
 *
 */
XmlList *checkToken(){
  XmlList *xmlList        = malloc(sizeof(XmlList));
	Token *token            = malloc(sizeof(Token));
	XmlElement *xmlElement  = malloc(sizeof(XmlElement));
  
  xmlList = createXmlList();
  xmlElement = createXmlElement(NULL, XML_TAG); 

  addList(xmlElement, xmlElement, xmlList);
	xmlElement = checkLoop(xmlList, xmlElement, 0);
  
	// if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "<") == 0)){
		// printf("%s", TokenOpSymbol);//print
    // token = getToken();
    
    // if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "$") == 0)){
      // return xmlList;
    // }
    // else
      // throwError("\nExcess tokens!!", ERR_NO_OPEN_BRACKET);
	// }
	// else
		// throwError("\nExpecting '<' at start.",ERR_NO_OPEN_BRACKET);
 
	return xmlList;
}

XmlElement *checkLoop(XmlList *xmlList, XmlElement *xmlElement, int loop){
  ElementType getType;
  TagType tagType;
  bool end = 0;
  Token *token;
  
  XmlElement *newXmlElement = malloc(sizeof(XmlElement));
  newXmlElement = createXmlElement(NULL,XML_TAG);
  
  if (loop == 0){
    getType = WAIT_FOR_TOKEN;
  }
  else
    getType = RECEIVED_TAG_OPEN;
	
  while (end != 1){
    token = getToken();
    switch (getType){
      case WAIT_FOR_TOKEN:
        getType = startToken(token);
        break;
      case RECEIVED_SLASH_CLOSE:
        getType = slash(xmlList, xmlElement, CLOSE_TAG, token);
        break;
      case RECEIVED_SLASH_SELFCLOSE:
        getType = slash(xmlList, xmlElement, SELF_CLOSE_TAG, token);
        end = 1;
        break;
      case RECEIVED_TAG_OPEN:
        getType = xmlTag(xmlList, xmlElement, OPEN_TAG, token);
        break;
      case RECEIVED_TAG_CLOSE:
        getType = xmlTag(xmlList, xmlElement, CLOSE_TAG, token);
        end = 1;
        break;
      case RECEIVED_CLOSEANGLEBRACKET:
        getType = closeAngleBracket(xmlList, xmlElement, OPEN_TAG, token);
        break;
      case RECEIVED_END_CLOSEANGLEBRACKET:
        getType = closeAngleBracket(xmlList, xmlElement, CLOSE_TAG, token);
        break;
      case RECEIVED_END:
        break;
      case RECEIVED_NEW_TAG:
        // getType = xmlTag(xmlList, xmlElement, OPEN_TAG, token);
        // childElement = malloc(sizeof(XmlElement));
        // childElement = createXmlElement(newXmlElement->data,newXmlElement->type);
        // childElement = checkLoop(xmlList, childElement, 1);
        // addList(xmlElement, childElement, xmlList);
        // getType = RECEIVED_CLOSEANGLEBRACKET;
        break;
      case RECEIVED_OPENANGLEBRACKET:
        getType = openAngleBracket(xmlList, xmlElement, newXmlElement, CLOSE_TAG, token);
        break;
      case RECEIVED_START_OPENANGLEBRACKET:
        getType = openAngleBracket(xmlList, xmlElement, newXmlElement, OPEN_TAG, token);
        break;
      case RECEIVED_ATTRIBUTE:
        break;
    }
  }
  if (loop == 0){
    token = getToken();
    if (strcmp(TokenOpSymbol, "$") == 0){
    }
    else
      throwError("Expecting '$' symbol at end.", ERR_NO_OPEN_BRACKET);
  }
  
  return xmlElement;
}

ElementType startToken(Token *token){
  if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "<") == 0))
    return RECEIVED_START_OPENANGLEBRACKET;
  else
    throwError("Expecting '<' symbol at beginning.", ERR_NO_OPEN_BRACKET);
}

/* 
 * Check the next token contains "/" or a tag after received "<" symbol.
 *    
 * Else throw error.  
 *
 * 
 *  
 */
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement, TagType tagType, Token *token){
  XmlElement *childElement = malloc(sizeof(XmlElement));
  
  if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "/") == 0)&&(tagType == CLOSE_TAG)){
    return RECEIVED_SLASH_CLOSE;
  }
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    if (tagType == OPEN_TAG) {
      xmlElement->data = TokenIdStr;
      return RECEIVED_TAG_OPEN;
    }
    else {
      if(strcmp(xmlElement->data, TokenIdStr) != 0){
        childElement = createXmlElement(TokenIdStr,XML_TAG);
        childElement = checkLoop(xmlList, childElement, 1);
        addList(xmlElement, childElement, xmlList);
        return RECEIVED_CLOSEANGLEBRACKET;
			}
      else
        throwError("\nMissing '/' or wrong tag name.", ERR_NO_TAG);
    }
  }
  else 
    throwError("Expecting a tag or '/' after the '<' symbol. ", ERR_WRONG_TAG);
}

/* 
 * Check the next token contains ">" or "/" after received a tag.
 *    
 * Else throw error.  
 *  
 */
ElementType xmlTag(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token){
  XmlAttribute *attributeElement; 
  
  if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, "/") == 0)){
    return RECEIVED_SLASH_SELFCLOSE;
  }
  else if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, ">") == 0)){
      if(tagType == CLOSE_TAG){
        return RECEIVED_END;
      }
      else{
        return RECEIVED_CLOSEANGLEBRACKET;
      }
  }
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    return RECEIVED_ATTRIBUTE;
  }
  else
    throwError("\nExpecting a '>' or '/' after the tag.", ERR_NO_CLOSING_BRACKET);
}

/* 
 * Check the next token contains string content or "<" after received ">" symbol.
 * Else throw error.  
 *  
 */
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token){
  char num[] = " ";// = " ";
  char *content;// = " "; 
	XmlElement *contentElement = malloc(sizeof(XmlElement));

  if(tagType == OPEN_TAG){
    if (token->type == TOKEN_STRING_TYPE){
      contentElement = createXmlElement(TokenStrStr, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      return RECEIVED_CLOSEANGLEBRACKET;
    }
    else if (token->type == TOKEN_INTEGER_TYPE){
      sprintf(num, "%d", TokenIntVal);
      contentElement = createXmlElement(num, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      return RECEIVED_CLOSEANGLEBRACKET;
    }
    else if(token->type == TOKEN_FLOAT_TYPE){
      sprintf(num, "%f", TokenFloatVal);
      contentElement = createXmlElement(num, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      return RECEIVED_CLOSEANGLEBRACKET;
    }
    else if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, "<") == 0)){
       // printf("%s", TokenOpSymbol); //printf
      return RECEIVED_OPENANGLEBRACKET;
    }
    else {
      printf("%s", TokenOpSymbol); //printf
      throwError("Expecting contents after '>' symbol. ", ERR_TOKEN_TYPE);
    }
  }
  else{
      return RECEIVED_END;
  }
  
}

/* 
 * Check the next token contains ">" or a tag after received "/" symbol.
 * Else throw error.  
 *  
 */
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token){
  
  if ((tagType == SELF_CLOSE_TAG) && (token->type == TOKEN_OPERATOR_TYPE) && (strcmp(">", TokenOpSymbol) == 0)){
    return RECEIVED_END_CLOSEANGLEBRACKET;
  }
  else if (tagType == CLOSE_TAG) {
    if ((token->type == TOKEN_IDENTIFIER_TYPE) && (strcmp(xmlElement->data, TokenIdStr) == 0)){
      // printf("%s", TokenIdStr);
      return RECEIVED_TAG_CLOSE;
    }
    else
      throwError("\nClosing tag are not same with open tag", ERR_WRONG_TAG);
  }
  else  
    throwError("\nExpecting '>' after '/' symbol.", ERR_WRONG_TAG);
  
}


// XmlAttribute *xmlAttribute(Token *token){
  // XmlAttribute *attribute = malloc(sizeof(XmlAttribute));
  
  
  // if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, "=") == 0)){
    // operator = (OperatorToken*)token;
  // }
  // else
    // throwError("Missing a '='", ERR_NO_CLOSING_BRACKET);
  
  // token = getToken();
  
  // if (token->type == TOKEN_STRING_TYPE){
    // content = (StringToken*)token;
  // }
  // else
    // throwError("Missing a '='", ERR_NO_CLOSING_BRACKET);
  
  // token = add2Tokens(id->str, operator->symbol, content->str);
  
  // attribute = createXmlAttribute(token);
  
  // return attribute;
// }

/*
 * Check whether the last token is "$" or not.
 * Else throw error..
 *
 */
void checkLastToken(Token *token){
  if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "$") == 0)){
  }
  else 
    throwError("Expecting a '>'", ERR_NO_CLOSING_BRACKET);
}

void throwTokenError(){
  
  do{
    Token *token = malloc(sizeof(Token));
    token = getToken();
    
    if (token->type == TOKEN_OPERATOR_TYPE){
      if(strcmp(TokenOpSymbol, "$") == 0){
        free(token);
        return;
      }
    }
  free(token);
  }while(1);
  
}
