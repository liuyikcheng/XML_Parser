/**
  ****************************************************************************** 
  * @author     Liu Yik Cheng
  * @programme  Microelectronics With Embedded Technology
  * @date       12-AUG-2015
  * @brief      XML parser
  *              This file provides checking according to XML file format
  *              after the received tokens and convert the string with XML 
  *              format to a linked list. The correct data will be extract 
  *              into a linked list while the wrong data will be throw     
  *              to error and display the error message. Token which contains
  *              with '$' symbol represent the end of the string.
  *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "xmlParcer.h"
#include "Token.h"
#include "CException.h"
#include "ErrorObject.h"
#include "linkedlist.h"




/*
 * @brief   The main function.
 * @param   None
 * @retval  xmlList    contains the list of the extracted XML data.
 */
XmlList *checkToken(){
  XmlList *xmlList        = malloc(sizeof(XmlList));
	XmlElement *xmlElement  = malloc(sizeof(XmlElement));
  
  xmlList = createXmlList();
  xmlElement = createXmlElement(NULL, XML_TAG); 

  addList(xmlElement, xmlElement, xmlList);
	xmlElement = checkLoop(xmlList, xmlElement, 0);
  
 
	return xmlList;
}

/*
 * @brief   The function that obtain the tokens from the getToken() function.
 * @param   xmlList       contains the list of the extracted XML data.
 *          xmlElement    contains the data as tag element from the identifier token.
 *          loop          0 means the first call of the function
 *                        1 means recursion of the function
 * @retval  xmlElement    The root element
 */
XmlElement *checkLoop(XmlList *xmlList, XmlElement *xmlElement, bool loop){
  ElementType getType;
  TagType tagType;
  bool end = 0; //determine when the loop should end 
  Token *token;
  
  XmlElement *newXmlElement = malloc(sizeof(XmlElement));
  newXmlElement = createXmlElement(NULL,XML_TAG);
  
  if (loop == 0){
    getType = WAIT_FOR_TOKEN;
  }
  else
    getType = RECEIVED_TAG_OPEN;
	
  while (end != 1){
    token = getToken();
    
    switch (getType){
      case WAIT_FOR_TOKEN:
        getType = startToken(token);
        break;
      case RECEIVED_SLASH_CLOSE:
        getType = slash(xmlList, xmlElement, CLOSE_TAG, token);
        break;
      case RECEIVED_SLASH_SELFCLOSE:
        getType = slash(xmlList, xmlElement, SELF_CLOSE_TAG, token);
        end = 1;
        break;
      case RECEIVED_TAG_OPEN:
        getType = xmlTag(xmlList, xmlElement, OPEN_TAG, token);
        break;
      case RECEIVED_TAG_CLOSE:
        getType = xmlTag(xmlList, xmlElement, CLOSE_TAG, token);
        end = 1;
        break;
      case RECEIVED_CLOSEANGLEBRACKET:
        getType = closeAngleBracket(xmlList, xmlElement, OPEN_TAG, token);
        break;
      case RECEIVED_END_CLOSEANGLEBRACKET:
        getType = closeAngleBracket(xmlList, xmlElement, CLOSE_TAG, token);
        break;
      case RECEIVED_OPENANGLEBRACKET:
        getType = openAngleBracket(xmlList, xmlElement, newXmlElement, CLOSE_TAG, token);
        break;
      case RECEIVED_START_OPENANGLEBRACKET:
        getType = openAngleBracket(xmlList, xmlElement, newXmlElement, OPEN_TAG, token);
        break;
      case RECEIVED_ATTRIBUTE:
        getType = xmlTag(xmlList, xmlElement, ATTRIBUTE_TAG, token);
        break;
      case RECEIVED_ATTRIBUTE_EQUAL_SIGN:
        getType = xmlTag(xmlList, xmlElement, ATTRIBUTE_EQUAL_SIGN, token);
        break;
    }
  }
  
  //Check the last token. Return error message if received any token other than "$"
  if (loop == 0){
    token = getToken();
    if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "$") == 0)){
    }
    else
      throwError("\nExpecting '$' symbol at end but received ", ERR_NO_OPEN_BRACKET, token);
  }
  
  return xmlElement;
}

/*
 * @brief   Check the content of the first token. 
 *          Return error message if received wrong token
 * @param   token         contains the data from getToken().
 * @retval  ElementType   determine the next path after received the correct token.
 */
ElementType startToken(Token *token){
  if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "<") == 0))
    return RECEIVED_START_OPENANGLEBRACKET;
  else
    throwError("\nExpecting '<' symbol at beginning but received ", ERR_NO_OPEN_BRACKET, token);
}


/*
 * @brief   Check the next token after received "<" symbol.
 *          Return error message if received wrong token
 * @param   xmlList       contains the list of the extracted XML data.
 *          xmlElement    contains the data as tag element from the identifier token.
 *          newXmlElement contains the data which different with xmlElement from the identifier token.
 *          tagtype       determine the current received tag type.
 *          token         contains the data from getToken().
 * @retval  ElementType   determine the next path after received the correct token.
 */
ElementType openAngleBracket(XmlList *xmlList, XmlElement *xmlElement, XmlElement *newXmlElement,\
                              TagType tagType, Token *token){
  XmlElement *childElement = malloc(sizeof(XmlElement));
  
  if ((token->type == TOKEN_OPERATOR_TYPE)&&(strcmp(TokenOpSymbol, "/") == 0)&&(tagType == CLOSE_TAG)){
    return RECEIVED_SLASH_CLOSE;
  }
  else if (token->type == TOKEN_IDENTIFIER_TYPE){
    if (tagType == OPEN_TAG) {
      xmlElement->data = TokenIdStr;
      return RECEIVED_TAG_OPEN;
    }
    else {
      if (xmlElement->data == NULL){
        throwError("\nExpecting an open tag but received ", ERR_NO_TAG, token);
      }
      //recusion if receive a new tag
      else if (strcmp(xmlElement->data, TokenIdStr) != 0){
        childElement = createXmlElement(TokenIdStr,XML_TAG);
        childElement = checkLoop(xmlList, childElement, 1);
        addList(xmlElement, childElement, xmlList);
        return RECEIVED_CLOSEANGLEBRACKET;
			}
      else
        throwError("\nMissing '/' or wrong tag name but received ", ERR_NO_TAG, token);
    }
  }
  else 
    throwError("Expecting a tag or '/' after the '<' symbol but received ", ERR_WRONG_TAG, token);
}

/*
 * @brief   Check the next token after received a tag.
 *          Return error message if received wrong token
 * @param   xmlList       contains the list of the extracted XML data.
 *          xmlElement    contains the data as tag element from the identifier token.
 *          tagtype       determine the current received tag type.
 *          token         contains the data from getToken().
 * @retval  ElementType   determine the next path after received the correct token.
 */
ElementType xmlTag(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token){
  XmlAttribute *attributeElement; 
  IdentifierToken *attributeId;
  
  if (tagType == ATTRIBUTE_TAG){
    if((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, "=") == 0)){
      return RECEIVED_ATTRIBUTE_EQUAL_SIGN;
    }
    else
      throwError("\nExpecting a '=' symbol after attribute tag but received ", ERR_NO_CLOSING_BRACKET, token);
  }
  else if (tagType == ATTRIBUTE_EQUAL_SIGN){
    if (token->type == TOKEN_STRING_TYPE){
      addListAttributeContent(xmlElement, TokenStrStr);
      return RECEIVED_TAG_OPEN;
    }
    else
      throwError("\nExpecting content after attribute tag but received ", ERR_NO_CLOSING_BRACKET, token);
  }
  else if (tagType == OPEN_TAG){
    if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, "/") == 0)){
      return RECEIVED_SLASH_SELFCLOSE;
    }
    else if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, ">") == 0))
      return RECEIVED_CLOSEANGLEBRACKET;
    else if (token->type == TOKEN_IDENTIFIER_TYPE){
      attributeElement = malloc(sizeof(XmlAttribute));
      attributeElement = createXmlAttribute(TokenIdStr, XML_ATTRIBUTE);
      addListAttribute(xmlElement, attributeElement, xmlList);
      return RECEIVED_ATTRIBUTE;
    }
    else 
      throwError("\nExpecting a '/' or '>' after the tag but received ", ERR_NO_CLOSING_BRACKET, token);
  }
  else if (tagType == CLOSE_TAG){
    if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, ">") == 0)){
      return ;
    }
    else
      throwError(("\nExpecting a '>' after the close tag but received "), ERR_NO_CLOSING_BRACKET, token);
  }
  else
    throwError("\nExpecting a '>' or '/' after the tag but received ", ERR_NO_CLOSING_BRACKET, token);
}
 
/*
 * @brief   Check the next token received ">" symbol.
 *          Return error message if received wrong token
 * @param   xmlList       contains the list of the extracted XML data.
 *          xmlElement    contains the data as tag element from the identifier token.
 *          tagtype       determine the current received tag type.
 *          token         contains the data from getToken().
 * @retval  ElementType   determine the next path after received the correct token.
 */
ElementType closeAngleBracket(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token){
  char *num = malloc(sizeof(char)*100);; 
	XmlElement *contentElement = malloc(sizeof(XmlElement));

  if(tagType == OPEN_TAG){
    if (token->type == TOKEN_STRING_TYPE){
      contentElement = createXmlElement(TokenStrStr, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      return RECEIVED_CLOSEANGLEBRACKET;
    }
    else if (token->type == TOKEN_INTEGER_TYPE){
      sprintf(num, "%d", TokenIntVal); //converting integer data type to string data type
      contentElement = createXmlElement(num, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      return RECEIVED_CLOSEANGLEBRACKET;
    }
    else if(token->type == TOKEN_FLOAT_TYPE){
      sprintf(num, "%.2f", TokenFloatVal); //converting float data type to string data type
      contentElement = createXmlElement(num, XML_CONTENT);
      addList(xmlElement, contentElement, xmlList);
      return RECEIVED_CLOSEANGLEBRACKET;
    }
    else if ((token->type == TOKEN_OPERATOR_TYPE) && (strcmp(TokenOpSymbol, "<") == 0)){
      return RECEIVED_OPENANGLEBRACKET;
    }
    else {
      throwError("\nExpecting contents after '>' symbol but received ", ERR_TOKEN_TYPE, token);
    }
  }
  else{
    return;
  }
  
}

/*
 * @brief   Check the next token received "/" symbol.
 *          Return error message if received wrong token
 * @param   xmlList       contains the list of the extracted XML data.
 *          xmlElement    contains the data as tag element from the identifier token.
 *          tagtype       determine the current received tag type.
 *          token         contains the data from getToken().
 * @retval  ElementType   determine the next path after received the correct token.
 */
ElementType slash(XmlList *xmlList, XmlElement *xmlElement, TagType tagType, Token *token){
  
  if ((tagType == SELF_CLOSE_TAG) && (token->type == TOKEN_OPERATOR_TYPE) && (strcmp(">", TokenOpSymbol) == 0)){
    return; //return nothing if it is a self closing tag
  }
  else if (tagType == CLOSE_TAG) {
    if ((token->type == TOKEN_IDENTIFIER_TYPE) && (strcmp(xmlElement->data, TokenIdStr) == 0)){
      return RECEIVED_TAG_CLOSE;
    }
    else
      throwError("\nClosing tag are not same with open tag but received ", ERR_WRONG_TAG, token);
  }
  else  
    throwError("\nExpecting '>' after '/' symbol but received ", ERR_WRONG_TAG, token);
  
}

/*
 * @brief   Throw the remaining Tokens after received any error.
 * @param   None
 * @retval  None
 */
void throwTokenError(){
  
  do{
    Token *token = malloc(sizeof(Token));
    token = getToken();
    
    if (token->type == TOKEN_OPERATOR_TYPE){
      if(strcmp(TokenOpSymbol, "$") == 0){
        free(token);
        return;
      }
    }
  free(token);
  }while(1);
  
}
