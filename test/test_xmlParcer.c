#include "unity.h"
#include "xmlParcer.h"
#include "mock_Token.h"
#include <stdlib.h>
#include "CException.h"
#include "ErrorObject.h"
#include "stdio.h"
#include "linkedlist.h"
void setUp(void){}

void tearDown(void){}


/**
 *
 * Display simple XML code:
 *  
 *		<name>ABC</name>
 *
 */
void test_moking_getToken(void){
	ErrorObject* err;
  Tag tag;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *contentName = (Token*)createStringToken("ABC");
  Token *contentName1 = (Token*)createStringToken("DEF");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	// Try{
  checkToken(xmlList);
	// printf("%s", xmlList->head->data);
	// }Catch(err){
    // printf("what%s", err->errorMsg);
  // }
}

/**
 *
 * given:
 *  <data>
 *		<name></name>
 *  </data>
 *
 *
 */
 
void test_display(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *idData = (Token*)createIdentifierToken("data");
  Token *contentName = (Token*)createStringToken("ABC");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	
  checkToken(xmlList);
}

/**
 *
 * given:
 *  <data>
 *		<name>ABC</name>
 *  </data>
 *
 *
 */

void test_display1(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *idData = (Token*)createIdentifierToken("data");
  Token *contentName = (Token*)createStringToken("ABC");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	
  checkToken(xmlList);
}

/**
 *
 * given:
 *  <data>
 *		<name>ABC</name>
 *    <age>18</age>
 *  </data>
 *
 *
 */

void test_display2(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *idAge = (Token*)createIdentifierToken("age");
  Token *idData = (Token*)createIdentifierToken("data");
  Token *contentName = (Token*)createStringToken("ABC");
  Token *contentAge = (Token*)createStringToken("18");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idAge);	
  getToken_ExpectAndReturn(rightAngleBracket);
  getToken_ExpectAndReturn(contentAge);
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idAge);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	Try{
  checkToken(xmlList);
	}Catch(err){
		printf("lol");
	}
}

/**
 *
 * given:
 *  <data>
 *			<name>
 * 					<firstName>ABC</firstName>
 *    	</name>
 *  </data>
 *
 *
 */

void test_display3(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *idFirstName = (Token*)createIdentifierToken("first");
  Token *idData = (Token*)createIdentifierToken("data");
  Token *contentName = (Token*)createStringToken("ABC");
	
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idFirstName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idFirstName);	
	getToken_ExpectAndReturn(rightAngleBracket);
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	// Try{
  checkToken(xmlList);
  printf("%s", xmlList->head);
  // TEST_ASSERT_NOT_EQUAL(xmlList->head, NULL);
	// }Catch(err){
		// printf("lol");
	// }
}

/**
 *
 * given:
 *		<name>ABC</name
 * 
 * should throw error
 *
 */
// void test_error_should_return_ERR_NO_CLOSING_TAG1(void){
  // CEXCEPTION_T err;
  // Tag tag;
	// Token *leftAngleBracket = (Token*)createOperatorToken("<");
	// Token *rightAngleBracket = (Token*)createOperatorToken(">");
	// Token *slash = (Token*)createOperatorToken("/");
  // Token *idName = (Token*)createIdentifierToken("name");
  // Token *contentName = (Token*)createStringToken("ABC");
  
	// getToken_ExpectAndReturn(leftAngleBracket);	
	// getToken_ExpectAndReturn(idName);	
	// getToken_ExpectAndReturn(rightAngleBracket);	
	// getToken_ExpectAndReturn(contentName);	
	// getToken_ExpectAndReturn(leftAngleBracket);	
	// getToken_ExpectAndReturn(slash);	
	// getToken_ExpectAndReturn(idName);	
	// getToken_ExpectAndReturn(rightAngleBracket);	
	// Try{
  // tag = checkToken(7);
	// }Catch(err){
    // printf("\n Something is wrong \n");
  // }
// }