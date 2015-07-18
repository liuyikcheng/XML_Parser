#ifndef xmlParcer_H
#define xmlParcer_H
#include "Token.h"
#include "linkedlist.h"

typedef enum{
  GET_OPENANGLEBRACKET,
  GET_CLOSEANGLEBRACKET,
  GET_END,
  GET_TAG_OPEN,
  GET_TAG_CLOSE,
  GET_NEW_TAG,
  GET_SLASH_CLOSE,
  GET_SLASH_SELFCLOSE,
  GET_CONTENT,

}ElementType;


XmlList *checkToken();
int checkLoop(XmlList *xmlList, XmlElement *xmlElement, Token *token, int loop);

OperatorToken *createOperatorToken(char* symbol);
StringToken *createStringToken(char* str);
IdentifierToken *createIdentifierToken(char* str);


ElementType xmlContent(XmlList *xmlList, XmlElement *xmlElement);
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, int closeTag, int selfClose);
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement);
ElementType xmlTag(XmlList *xmlList, int closeTag);
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement, int endTag);
#endif // xmlParcer_H
