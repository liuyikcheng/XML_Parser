#ifndef xmlParcer_H
#define xmlParcer_H
#include "Token.h"
#include "linkedlist.h"
#include <stdbool.h>
typedef enum{
  GOT_OPENANGLEBRACKET,
  GOT_CLOSEANGLEBRACKET,
  GOT_END,
  GOT_TAG_OPEN,
  GOT_TAG_CLOSE,
  GOT_NEW_TAG,
  GOT_SLASH_CLOSE,
  GOT_SLASH_SELFCLOSE,
  GOT_CONTENT,
  GOT_ATTRIBUTE,

}ElementType;

typedef enum{
  CLOSE_TAG,
  SELF_CLOSE_TAG,
}TagType;

XmlList *checkToken();
XmlElement *checkLoop(XmlList *xmlList, XmlElement *xmlElement, Token *token, int loop);




ElementType xmlContent(XmlList *xmlList, XmlElement *xmlElement);
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, TagType tagType);
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement);
ElementType xmlTag(XmlList *xmlList, XmlElement *xmlElement, int closeTag);
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement, int endTag);
XmlAttribute *xmlAttribute(Token *token);
void checkLastToken();

#endif // xmlParcer_H
