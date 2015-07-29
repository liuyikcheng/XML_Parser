#include <stdlib.h>
#include <stdio.h>
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

void addListAttribute(XmlElement *xmlElement, XmlElement xmlAttribute, XmlList *xmlList){
  
}