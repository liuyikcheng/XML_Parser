#include <stdlib.h>
#include <stdio.h>
#include <Token.h>
#include <TokenCreate.h>
#include "linkedlist.h"
#include "ErrorObject.h"

/*
 * @brief   To create a xml element from the data of the token.
 * @param   data        contains the data from the tokens.
 *          xmlList     contains the type data.
 * @retval  xmlElement  return the xml element.
 */
XmlElement *createXmlElement(char *data, XmlElementType type){
	XmlElement *xmlElement = malloc(sizeof(XmlElement));
	xmlElement->next = NULL;
	xmlElement->child = NULL;
  xmlElement->attribute = NULL;
	xmlElement->data = data;
	xmlElement->type = type;
	return xmlElement;
}

/*
 * @brief   To create a head and tail point to the linked list.
 * @param   None
 * @retval  xmlList    return the list.
 */
XmlList *createXmlList(){
	XmlList *xmlList = malloc(sizeof(XmlList));
	xmlList->head = NULL;
	xmlList->tail = NULL;
	xmlList->length = 0;
	return xmlList;
}

/*
 * @brief   To create an attribute element from the data of the token.
 * @param   attributeTag        contains the data from the tokens.
 *          type                contains the type data.
 * @retval  xmlElement  return the attribute element.
 */
XmlAttribute *createXmlAttribute(char *attributeTag, XmlElementType type){
  XmlAttribute *attribute = malloc(sizeof(XmlAttribute));
  attribute->next = NULL;
  attribute->type = type;
  attribute->attributeTag = attributeTag;
  attribute->attributeContent = NULL;
  return attribute;
}

/*
 * @brief   To add the parent element with the child element. 
 * @param   xmlElement            contains parent element.
 *          newXmlElement         contains child element.
 *          xmlList               contains the list element.
 * @retval  NULL
 */
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

/*
 * @brief   To add the element with the attribute element. 
 * @param   xmlElement            contains element.
 *          attributeElement      contains attribute element.
 *          xmlList               contains the list element.
 * @retval  NULL
 */
void addListAttribute(XmlElement *xmlElement, XmlAttribute *attributeElement, XmlList *xmlList){
  XmlAttribute *tempElement = malloc(sizeof(XmlElement));
 
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
  xmlList->length++;
}

/*
 * @brief   To add the attribute element with the attribute content. 
 * @param   xmlElement            contains element.
 *          attributeContent      contains attribute content.
 *          xmlList               contains the list element.
 * @retval  NULL
 */
void addListAttributeContent(XmlElement *xmlElement, char *attributeContent){
  XmlAttribute *tempElement = malloc(sizeof(XmlElement));
  tempElement = xmlElement->attribute;
  
  while(tempElement->attributeContent != NULL){
    tempElement = tempElement->next;
  }
  
  tempElement->attributeContent = attributeContent;
}

/*
 * @brief   To find the element which contain the same data as the input param data.
 *          Return error message if no elements are matching. 
 * @param   xmlList           contains the list element.
 *          data              contains the searching data.
 *          compare           contains the result after comparing two strings. 
 * @retval  xmlList->head     contains the element that match with the input param.
 */
XmlElement *strListFind(XmlList *xmlList, void *data, int (*compare)(void *, void*)){
  Token *token;
  int result = 1;
  xmlList->head = xmlList->head->child;
  
  do{
    result = compare(data, xmlList->head->data);
    if (result != 0)
      xmlList->head = xmlList->head->next;
    else
      break;
  }while (xmlList->head != NULL);
  
  if (result == 1)
    throwError("Error element not found!!!", ERR_NO_ELEMENT, token);
  else 
    return xmlList->head;
  
}

/*
 * @brief   Compare two strings 
 * @param   first       contains the data of the input.
 *          second      contains the data of the element. 
 * @retval  return 0    if the both variables contain the same data.
 *          return 1    if the both variables contain different data.
 */
int strCompare(void *first, void *second){
  if(strcmp(((char*)first), ((char*)second)) == 0)
    return 0;
  else
    return 1;
}
