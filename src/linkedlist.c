#include <stdlib.h>
#include <stdio.h>
#include <Token.h>
#include <TokenCreate.h>
#include "linkedlist.h"



XmlElement *createXmlElement(char *data, XmlElementType type){
	XmlElement *xmlElement = malloc(sizeof(XmlElement));
	xmlElement->next = NULL;
	xmlElement->child = NULL;
  xmlElement->attribute = NULL;
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

XmlAttribute *createXmlAttribute(char *attributeTag, XmlElementType type){
  XmlAttribute *attribute = malloc(sizeof(XmlAttribute));
  attribute->next = NULL;
  attribute->type = type;
  attribute->attributeTag = attributeTag;
  attribute->attributeContent = NULL;
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

// void addListAttribute(XmlElement *xmlElement, XmlElement *attributeElement, XmlList *xmlList){
   // XmlElement *tempElement = malloc(sizeof(XmlElement));
  
	// if(xmlList->head == NULL){ 
		// xmlList->head = xmlElement;
		// xmlList->tail = xmlElement;
	// }
	// else{
    // if(xmlElement->attribute == NULL){
      // xmlElement->attribute = attributeElement;
    // }
    // else{
      // tempElement = xmlElement->attribute;
      // if(tempElement->next != NULL){
        // tempElement = tempElement->next;
      // }
      // tempElement->next = attributeElement;
    // }
    // xmlList->tail = attributeElement;
  
	// }
	// xmlList->length++;
// }

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

void addListAttributeContent(XmlElement *xmlElement, char *attributeContent){
  XmlAttribute *tempElement = malloc(sizeof(XmlElement));
  tempElement = xmlElement->attribute;
  
  while(tempElement->attributeContent != NULL){
    tempElement = tempElement->next;
  }
  
  tempElement->attributeContent = attributeContent;
}

XmlElement *strListFind(XmlList *list, void *data, int (*compare)(void *, void*)){
  XmlElement *elem = malloc(sizeof(XmlElement));
  int result = 1;
  elem = list->head->child;
  
  while (result != 0){
    result = compare(data, elem->data);
    if(result != 0)
      elem = elem->next;
  }
  return elem;
}

int strCompare(void *first, void *second){
  if(strcmp(((char*)first), ((char*)second)) == 0)
    return 0;
  else
    return 1;
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