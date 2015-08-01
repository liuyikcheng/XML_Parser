#include <stdlib.h>
#include <stdio.h>
#include <Token.h>
#include <TokenCreate.h>
#include "linkedlist.h"


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

XmlAttribute *createXmlAttribute(Token *token){
  XmlAttribute *attribute = malloc(sizeof(XmlAttribute));
  attribute->next = NULL;
  attribute->token = token;
  return attribute;
}

void addList(XmlElement *xmlElement, XmlElement *newXmlElement, XmlList *xmlList){
  XmlElement *tempElement = malloc(sizeof(XmlElement));
  
	if(xmlList->head == NULL){ 
		xmlList->head = xmlElement;
		xmlList->tail = xmlElement;
	}
	else{
    if(xmlElement->child == NULL){
      xmlElement->child = newXmlElement;
    }
    else{
      tempElement = xmlElement->child;
      if(tempElement->next != NULL){
        tempElement = tempElement->next;
      }
      tempElement->next = newXmlElement;
    }
    xmlList->tail = newXmlElement;
  
	}
	xmlList->length++;
}

void addListAttribute(XmlElement *xmlElement, XmlAttribute *attributeElement, XmlList *xmlList){
  XmlAttribute *tempElement = malloc(sizeof(XmlElement));
  
  if(xmlList->head == NULL){ 
		xmlList->head = xmlElement;
		xmlList->tail = xmlElement;
	}
  
  else{
      if(xmlElement->attribute == NULL){
          xmlElement->attribute = attributeElement;
      }
      else{
      tempElement = xmlElement->attribute;
      if(tempElement->next != NULL){
        tempElement = tempElement->next;
      }
      tempElement->next = attributeElement;
    }
  
	}
	xmlList->length++;
}

Token *add2Tokens(char *leftValue, char *operatorSymbol, char *rightValue){
  OperatorToken *op = malloc(sizeof(OperatorToken)+(sizeof(Token)*2));
  IdentifierToken *lefttoken = malloc(sizeof(IdentifierToken));
  StringToken *righttoken = malloc(sizeof(StringToken));
  
  lefttoken = createIdentifierToken(leftValue);
  righttoken = createStringToken(rightValue);
  op = createOperatorToken(operatorSymbol);
  
  op->token[0] = (Token*)lefttoken;
  op->token[1] = (Token*)righttoken;
  
  return (Token*)op;
}