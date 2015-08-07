#ifndef xmlParcer_H
#define xmlParcer_H
#include "Token.h"
#include "linkedlist.h"
#include <stdbool.h>
typedef enum{
  WAIT_FOR_TOKEN,
  RECEIVED_START_OPENANGLEBRACKET,
  RECEIVED_OPENANGLEBRACKET,
  RECEIVED_CLOSEANGLEBRACKET,
  RECEIVED_END_CLOSEANGLEBRACKET,
  RECEIVED_END,
  RECEIVED_TAG_OPEN,
  RECEIVED_TAG_CLOSE,
  RECEIVED_NEW_TAG,
  RECEIVED_SLASH_CLOSE,
  RECEIVED_SLASH_SELFCLOSE,
  RECEIVED_CONTENT,
  RECEIVED_ATTRIBUTE,
  RECEIVED_EQUAL_SIGN,

}ElementType;

typedef enum{
  OPEN_TAG,
  CLOSE_TAG,
  SELF_CLOSE_TAG,
}TagType;

XmlList *checkToken();
XmlElement *checkLoop(XmlList *xmlList, XmlElement *xmlElement, int loop);

ElementType startToken(Token *token);
ElementType xmlContent(XmlList *xmlList, XmlElement *xmlElement, Token *token);
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token);
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token);
ElementType equalSign(XmlList *xmlList, XmlElement *xmlElement, Token *token);
ElementType xmlTag(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token);
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement, TagType tagType, Token *token);
XmlAttribute *xmlAttribute(Token *token);
void checkLastToken();

void throwTokenError();

#endif // xmlParcer_H
