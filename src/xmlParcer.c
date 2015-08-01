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
	OperatorToken* operator = malloc(sizeof(OperatorToken));
	XmlElement *xmlElement  = malloc(sizeof(XmlElement));
  
  xmlList = createXmlList();
  xmlElement = createXmlElement(NULL, 0); 
	
	token = getToken();     // check the first token whether it is "<" or not
	if(token->type == TOKEN_OPERATOR_TYPE){
		operator = (OperatorToken*)token;
		printf("%s", operator->symbol);//print
		if(strcmp(operator->symbol, "<") == -1){ // Check whether the first token is "<"  
			Throw(ERR_NO_OPEN_BRACKET);
		}
	}
	else
		throwError("Missing left angle bracket.",ERR_NO_OPEN_BRACKET);
  
  xmlList = createXmlList();
	xmlElement = checkLoop(xmlList, xmlElement, token, 0);
	return xmlList;
}

XmlElement *checkLoop(XmlList *xmlList, XmlElement *xmlElement, Token *token, int loop){
  ElementType getType;
  TagType tagType;
  bool end = 0;

  XmlElement *childElement;
  XmlElement *newXmlElement;
  
  newXmlElement = malloc(sizeof(XmlElement));
  newXmlElement = createXmlElement(NULL,0);
  
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
        childElement = checkLoop(xmlList, childElement, token, 1);
        addList(xmlElement, childElement, xmlList);
        getType = GOT_CLOSEANGLEBRACKET;
        break;
      case GOT_OPENANGLEBRACKET:
        getType = openAngleBracket(xmlList, xmlElement, newXmlElement, 1);
        break;
      case GOT_CONTENT:
        getType = xmlContent(xmlList, xmlElement);
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
  OperatorToken* operator  = malloc(sizeof(OperatorToken));
  IdentifierToken* tag     = malloc(sizeof(IdentifierToken));
  Token *token             = malloc(sizeof(Token));
  XmlElement *childElement;
  token = getToken();
  
  if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    
    if (strcmp(operator->symbol, "/") == 0)
      return GOT_SLASH_CLOSE;
    else
      throwError("Expecting a '/' symbol.", ERR_NO_SLASH);
  }
  
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    tag = (IdentifierToken*)token;
    printf("%s", tag->str); // print
    
    if (endTag == 0) {
      xmlElement->data = tag->str;
      return GOT_TAG_OPEN;
    }
    else {
      
      if(strcmp(xmlElement->data, tag->str) != 0){
				childElement = malloc(sizeof(XmlElement));
        childElement = createXmlElement(tag->str,XML_TAG);
        newXmlElement->data = childElement->data;
        return GOT_NEW_TAG;
			}
      else
        throwError("Wrong tag name.", ERR_NO_TAG);
    }
  }
  else 
    throwError("Received wrong token", ERR_WRONG_TAG);
}

/* 
 * Check the next token contains ">" or "/" after received a tag.
 *    
 * Else throw error.  
 *  
 */
ElementType xmlTag(XmlList *xmlList, XmlElement *xmlElement, int closeTag){
  Token *token = malloc(sizeof(Token));
  OperatorToken *operator = malloc(sizeof(OperatorToken));
  IdentifierToken *tag    = malloc(sizeof(IdentifierToken));
  XmlAttribute *attributeElement; 
  
  do{
  token = getToken();
  
  if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    
    if (strcmp(operator->symbol, "/") == 0){
      return GOT_SLASH_SELFCLOSE;
    }
    else if (strcmp(operator->symbol, ">") == 0){
      
      if(closeTag == 1)
        return GOT_END;
      else
        return GOT_CLOSEANGLEBRACKET;
    }
    else 
      throwError("Expecting a '>'", ERR_NO_CLOSING_BRACKET);
  }
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    attributeElement = malloc(sizeof(XmlAttribute));
    attributeElement = xmlAttribute(token);
    addListAttribute(xmlElement, attributeElement, xmlList);
  }
  else
    throwError("Expecting a '>'", ERR_NO_CLOSING_BRACKET);
  }while(token->type == TOKEN_IDENTIFIER_TYPE); 
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
    return GOT_CONTENT;
  }
  else if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    
    if (strcmp(operator->symbol, "<") == 0){
      return GOT_OPENANGLEBRACKET;
    }
  }
  else 
    throwError("Received wrong token", ERR_TOKEN_TYPE);
}

/* 
 * Check the next token contains ">" or a tag after received "/" symbol.
 * Else throw error.  
 *  
 */
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, TagType tagType){
  Token *token = malloc(sizeof(Token));
  IdentifierToken *tag = malloc(sizeof(IdentifierToken));
  OperatorToken* operator = malloc(sizeof(OperatorToken));
  
  if (tagType == SELF_CLOSE_TAG){
    return GOT_END;
  }
  else if (tagType == CLOSE_TAG) {
    token = getToken();
    
    if(token->type == TOKEN_IDENTIFIER_TYPE){
      tag = (IdentifierToken*)token;
    }
    else 
      throwError("Expect Identifier token.", ERR_TOKEN_TYPE);
    
    tag = (IdentifierToken*)token;
    printf("%s", tag->str); // print
    
    if (strcmp(xmlElement->data, tag->str) == 0)
      return GOT_END;
    else
      throwError("Closing tag are not same with open tag", ERR_WRONG_TAG);
  }
  
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
		// addList(xmlElement, contentElement, xmlList);
    return GOT_CONTENT;
  }
  else if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if(strcmp(operator->symbol, "<") == 0)
      return GOT_OPENANGLEBRACKET;
    else 
      throwError("Expext a '<'", ERR_NO_OPEN_BRACKET);
  }
  else
    throwError("Recevied wrong token", ERR_NO_CLOSING_BRACKET);
}                        

XmlAttribute *xmlAttribute(Token *attr){
  Token *token = malloc(sizeof(Token));
  IdentifierToken *id = malloc(sizeof(IdentifierToken));
  StringToken *content = malloc(sizeof(StringToken));
  OperatorToken *operator = malloc(sizeof(OperatorToken));
  XmlAttribute *attribute = malloc(sizeof(XmlAttribute));
  
  id = (IdentifierToken*)attr;
  printf(" %s", id->str);
  
  token = getToken();
  
  if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    if (strcmp(operator->symbol, "=") == 0)
      printf("%s", operator->symbol); //print
    else
      throwError("Missing a '='", ERR_NO_CLOSING_BRACKET);
  }
  else
    throwError("Missing a '='", ERR_NO_CLOSING_BRACKET);
  
  token = getToken();
  
  if (token->type == TOKEN_STRING_TYPE){
    content = (StringToken*)token;
    printf("%s", content->str);
  }
  else
    throwError("Missing a '='", ERR_NO_CLOSING_BRACKET);
  
  token = add2Tokens(id->str, operator->symbol, content->str);
  
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
  OperatorToken* operator = malloc(sizeof(OperatorToken));
  token = getToken();
  
  if (token->type == TOKEN_OPERATOR_TYPE){
    operator = (OperatorToken*)token;
    printf("%s", operator->symbol); // print
    if (strcmp(operator->symbol, ">") == 0){
      
    }
    else 
      throwError("Expecting a '>'", ERR_NO_CLOSING_BRACKET);
  }
  else 
    throwError("Expecting a '>'", ERR_NO_CLOSING_BRACKET);
}
