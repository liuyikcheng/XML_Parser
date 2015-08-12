#ifndef xmlParcer_H
#define xmlParcer_H
#include <stdbool.h>
#include "Token.h"
#include "linkedlist.h"



/*
 * The list of content in different types of token
 */
#define TokenOpSymbol   ((OperatorToken*)token)->symbol
#define TokenIdStr      ((IdentifierToken*)token)->str
#define TokenStrStr     ((StringToken*)token)->str
#define TokenIntVal     ((IntegerToken*)token)->value
#define TokenFloatVal   ((FloatToken*)token)->value


/*
 * The state of the token receive process
 */
typedef enum{
  WAIT_FOR_TOKEN,
  RECEIVED_START_OPENANGLEBRACKET,
  RECEIVED_OPENANGLEBRACKET,
  RECEIVED_CLOSEANGLEBRACKET,
  RECEIVED_END_CLOSEANGLEBRACKET,
  RECEIVED_TAG_OPEN,
  RECEIVED_TAG_CLOSE,
  RECEIVED_NEW_TAG,
  RECEIVED_SLASH_CLOSE,
  RECEIVED_SLASH_SELFCLOSE,
  RECEIVED_CONTENT,
  RECEIVED_ATTRIBUTE,
  RECEIVED_EQUAL_SIGN,
  RECEIVED_ATTRIBUTE_EQUAL_SIGN

}ElementType;

/*
 * The type of the tag
 */
typedef enum{
  OPEN_TAG,
  CLOSE_TAG,
  SELF_CLOSE_TAG,
  ATTRIBUTE_TAG,
  ATTRIBUTE_EQUAL_SIGN
}TagType;

XmlList *checkToken();
XmlElement *checkLoop(XmlList *xmlList, XmlElement *xmlElement, bool loop);

ElementType startToken(Token *token);
ElementType xmlContent(XmlList *xmlList, XmlElement *xmlElement, Token *token);
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token);
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token);
ElementType equalSign(XmlList *xmlList, XmlElement *xmlElement, Token *token);
ElementType xmlTag(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token);
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement,\
                             TagType tagType, Token *token);

void throwTokenError();

#endif // xmlParcer_H
