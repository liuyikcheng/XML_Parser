#ifndef linkedlist_H
#define linkedlist_H

typedef enum{
	XML_TAG,
	XML_CONTENT,
  XML_ATTRIBUTE,
}XmlElementType;

typedef struct XmlElement XmlElement;
struct XmlElement{
  XmlElement *next;
  XmlElement *child;
  XmlElement *attribute;
  XmlElementType type;
  char *data;
};

typedef struct{
	struct XmlElement *head;
	struct XmlElement *tail ;
	int length;
	
}XmlList;

XmlElement *createXmlElement(char *data, XmlElementType type);
XmlList *createXmlList();
void addList(XmlElement *xmlElement, XmlElement *newXmlElement, XmlList *xmlList);
void addListAttribute(XmlElement *xmlElement, XmlElement xmlAttribute);

#endif // linkedlist_H

