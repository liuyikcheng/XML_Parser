#ifndef linkedlist_H
#define linkedlist_H
#include <Token.h>

typedef enum{
	XML_TAG,
	XML_CONTENT,
  XML_ATTRIBUTE,
}XmlElementType;

typedef struct XmlElement XmlElement;
typedef struct XmlAttribute XmlAttribute;

struct XmlElement{
  XmlElement *next;
  XmlElement *child;
  XmlAttribute *attribute;
  XmlElementType type;
  char *data;
};

typedef struct{
	struct XmlElement *head;
	struct XmlElement *tail ;
	int length;
}XmlList;

struct XmlAttribute{
  XmlAttribute *next;
  char* attributeTag;
  char* attributeContent;
  XmlElementType type;
};

XmlElement *createXmlElement(char *data, XmlElementType type);
XmlList *createXmlList();
XmlAttribute *createXmlAttribute(char *attributeTag, XmlElementType type);

void addList(XmlElement *xmlElement, XmlElement *newXmlElement, XmlList *xmlList);
void addListAttribute(XmlElement *xmlElement, XmlAttribute *xmlAttribute, XmlList *xmlList);
void addListAttributeContent(XmlElement *xmlElement, char *attributeContent);

XmlElement *strListFind(XmlList *list, void *data, int (*compare)(void *, void*));
int strCompare(void *first, void *second);


Token *add2Tokens(char *leftValue, char *operatorSymbol, char *rightValue);

#endif // linkedlist_H

