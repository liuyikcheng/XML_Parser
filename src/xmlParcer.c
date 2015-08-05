#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "xmlParcer.h"
#include "Token.h"
#include "CException.h"
#include "ErrorObject.h"
#include "linkedlist.h"

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
	
	token = getToken();     // check the first token whether it is "<" or not

	if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(((OperatorToken*)token)->symbol, "<") == 0)){
		//printf("%s", ((OperatorToken*)token)->symbol);//print
		xmlElement = checkLoop(xmlList, xmlElement, 0);
    token = getToken();
    
    if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(((OperatorToken*)token)->symbol, "$") == 0)){
      // free(token);
      return xmlList;
    }
    else
      throwError("\nExcess tokens!!", ERR_NO_OPEN_BRACKET);
	}
	else
		throwError("\nExpecting '<' at start.",ERR_NO_OPEN_BRACKET);
 
	return xmlList;
}

XmlElement *checkLoop(XmlList *xmlList, XmlElement *xmlElement, int loop){
  ElementType getType;
  TagType tagType;
  bool end = 0;

  XmlElement *childElement;
  XmlElement *newXmlElement = malloc(sizeof(XmlElement));
  newXmlElement = createXmlElement(NULL,XML_TAG);
  
  if (loop == 0){
    getType = openAngleBracket(xmlList, xmlElement, newXmlElement, 0);
    addList(xmlElement, xmlElement, xmlList);
  }
  else
    getType = xmlTag(xmlList, xmlElement, 0);
	
  while (end != 1){
    switch (getType){
      case GOT_SLASH_CLOSE:
        tagType = CLOSE_TAG;
        getType = slash(xmlList, xmlElement, tagType);
        break;
      case GOT_SLASH_SELFCLOSE:
        tagType = SELF_CLOSE_TAG;
        getType = slash(xmlList, xmlElement, tagType);
        break;
      case GOT_TAG_OPEN:
        getType = xmlTag(xmlList, xmlElement, 0);
        break;
      case GOT_TAG_CLOSE:
        getType = xmlTag(xmlList, xmlElement, 1);
        break;
      case GOT_CLOSEANGLEBRACKET:
        getType = closeAngleBracket(xmlList, xmlElement);
        break;
      case GOT_END:
        checkLastToken();
        end = 1;
        break;
      case GOT_NEW_TAG:
        childElement = malloc(sizeof(XmlElement));
        childElement = createXmlElement(newXmlElement->data,newXmlElement->type);
        childElement = checkLoop(xmlList, childElement, 1);
        addList(xmlElement, childElement, xmlList);
        getType = GOT_CLOSEANGLEBRACKET;
        break;
      case GOT_OPENANGLEBRACKET:
        getType = openAngleBracket(xmlList, xmlElement, newXmlElement, 1);
        break;
    }
    
  }
  return xmlElement;
}

/* 
 * Check the next token contains "/" or a tag after received "<" symbol.
 *    
 * Else throw error.  
 *
 * 
 *  
 */
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement, int endTag){
  Token *token             = malloc(sizeof(Token));
  XmlElement *childElement;
 
  token = getToken();
  
  if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(((OperatorToken*)token)->symbol, "/") == 0)&&(endTag != 0)){
    return GOT_SLASH_CLOSE;
  }
  
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    // //printf("%s", ((IdentifierToken*)token)->str); // print
    
    if (endTag == 0) {
      xmlElement->data = ((IdentifierToken*)token)->str;
      // free(token);
      return GOT_TAG_OPEN;
    }
    else {
      if(strcmp(xmlElement->data, ((IdentifierToken*)token)->str) != 0){
        newXmlElement->data = ((IdentifierToken*)token)->str;
        // free(token);
        return GOT_NEW_TAG;
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
ElementType xmlTag(XmlList *xmlList, XmlElement *xmlElement, int closeTag){
  Token *token = malloc(sizeof(Token));
  XmlAttribute *attributeElement; 
  
  do{
  token = getToken();
  
  if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(((OperatorToken*)token)->symbol, "/") == 0)){
    return GOT_SLASH_SELFCLOSE;
    // //printf("%s", ((OperatorToken*)token)->symbol); // print
  }
  else if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(((OperatorToken*)token)->symbol, ">") == 0)){
      // //printf("%s", ((OperatorToken*)token)->symbol); // print
      if(closeTag == 1)
        return GOT_END;
      else
        return GOT_CLOSEANGLEBRACKET;
  }
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    attributeElement = malloc(sizeof(XmlAttribute));
    attributeElement = xmlAttribute(token);
    addListAttribute(xmlElement, attributeElement, xmlList);
  }
  else
    throwError("\nExpecting a '>' or '/' after the tag.", ERR_NO_CLOSING_BRACKET);
  }while(token->type == TOKEN_IDENTIFIER_TYPE); 
}

/* 
 * Check the next token contains string content or "<" after received ">" symbol.
 * Else throw error.  
 *  
 */
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement){
  char num[] = " ";// = " ";
  char *content;// = " "; 
  Token *token = malloc(sizeof(Token));
	XmlElement *contentElement;
  
  
	do{
    token = getToken();
    if (token->type == TOKEN_STRING_TYPE){
      contentElement = malloc(sizeof(XmlElement));
      contentElement = createXmlElement(((StringToken*)token)->str, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
    }
    else if (token->type == TOKEN_INTEGER_TYPE){
      sprintf(num, "%d", ((IntegerToken*)token)->value);
      contentElement = malloc(sizeof(XmlElement));
      contentElement = createXmlElement(num, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      
    }
    else if(token->type == TOKEN_FLOAT_TYPE){
      sprintf(num, "%f", ((FloatToken*)token)->value);
      contentElement = malloc(sizeof(XmlElement));
      contentElement = createXmlElement(num, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      
    }
    else if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(((OperatorToken*)token)->symbol, "<") == 0)){
      // //printf("%s", ((OperatorToken*)token)->symbol); // print
      return GOT_OPENANGLEBRACKET;
    }
    else 
      throwError("Expecting contents after '>' symbol. ", ERR_TOKEN_TYPE);
  }while(token->type ==  TOKEN_STRING_TYPE||TOKEN_INTEGER_TYPE||TOKEN_FLOAT_TYPE);
  
}

/* 
 * Check the next token contains ">" or a tag after received "/" symbol.
 * Else throw error.  
 *  
 */
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, TagType tagType){
  Token *token = malloc(sizeof(Token));
  
  if (tagType == SELF_CLOSE_TAG){
    return GOT_END;
  }
  else if (tagType == CLOSE_TAG) {
    token = getToken();
    if ((token->type == TOKEN_IDENTIFIER_TYPE) || (strcmp(xmlElement->data, ((IdentifierToken*)token)->str) == 0)){
       return GOT_END;
    }
    else
      throwError("\nClosing tag are not same with open tag", ERR_WRONG_TAG);
  }
  
}


XmlAttribute *xmlAttribute(Token *attr){
  Token *token = malloc(sizeof(Token));
  IdentifierToken *id = malloc(sizeof(IdentifierToken));
  StringToken *content = malloc(sizeof(StringToken));
  OperatorToken *operator = malloc(sizeof(OperatorToken));
  XmlAttribute *attribute = malloc(sizeof(XmlAttribute));
  
  id = (IdentifierToken*)attr;
  ////printf(" %s", id->str);
  
  token = getToken();
  
  if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(((OperatorToken*)token)->symbol, "=") == 0)){
    operator = (OperatorToken*)token;
  }
  else
    throwError("Missing a '='", ERR_NO_CLOSING_BRACKET);
  
  token = getToken();
  
  if (token->type == TOKEN_STRING_TYPE){
    content = (StringToken*)token;
    ////printf("%s", content->str);
  }
  else
    throwError("Missing a '='", ERR_NO_CLOSING_BRACKET);
  
  token = add2Tokens(id->str, operator->symbol, content->str);
  
  // printf("%s", (((OperatorToken*)token)->token[1]->type));
  attribute = createXmlAttribute(token);
  
  return attribute;
}

/*
 * Check whether the last token is ">" or not.
 * Else throw error..
 *
 */
void checkLastToken(){
  Token *token = malloc(sizeof(Token));
  
  token = getToken();
  
  if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(((OperatorToken*)token)->symbol, ">") == 0)){
  }
  else 
    throwError("Expecting a '>'", ERR_NO_CLOSING_BRACKET);
}

void throwTokenError(){
  
  do{
    Token *token = malloc(sizeof(Token));
    token = getToken();
    
    if (token->type == TOKEN_OPERATOR_TYPE){
      if(strcmp(((OperatorToken*)token)->symbol, "$") == 0){
        free(token);
        return;
      }
    }
  free(token);
  }while(1);
  
}
