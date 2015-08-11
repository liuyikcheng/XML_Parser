#include "unity.h"
#include <stdlib.h>
#include "xmlParcer.h"
#include "mock_Token.h"
#include "CException.h"
#include "ErrorObject.h"
#include "TokenCreate.h"
#include "stdio.h"
#include "linkedlist.h"


void setUp(void){}

void tearDown(void){}


/**
 *
 *                                                    
 *		<name>ABC DEF</name>        
 *                                       
 * Return:
 *            child            child
 *    name -----------> ABC ---------->(NULL)
 *     |                 | 
 *     | next            | next
 *    \|/               \|/
 *   (NULL)             DEF
 *                       |                               
 *                       | next
 *                      \|/
 *                     (NULL)
 *
 **/
void test_moking_getToken(void){
	ErrorObject* err;
  Tag tag;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);	

  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
 
  TEST_ASSERT_NOT_EQUAL(xmlList->head, NULL);
  TEST_ASSERT_NOT_EQUAL(xmlList->tail, NULL);
  TEST_ASSERT_EQUAL_STRING("name", xmlList->head->data);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->next);
  TEST_ASSERT_EQUAL_STRING("ABC", xmlList->head->child->data);
  TEST_ASSERT_EQUAL_STRING("DEF", xmlList->head->child->next->data);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->child->next->next);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->child->child);

}

/**
 *
 * given:
 * 
 *		<name></name>
 * 
 *
 */
 
void test_creating_list_element(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
		
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);	
	
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  
  TEST_ASSERT_EQUAL_STRING("name", xmlList->head->data);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->child);

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
 
void test_creating_list_element_with_data_as_root_and_name_as_child(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *end                = (Token*)createOperatorToken("$");
  
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
	getToken_ExpectAndReturn(end);	
	
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  
  TEST_ASSERT_EQUAL_STRING("data", xmlList->head->data);
  TEST_ASSERT_EQUAL_STRING("name", xmlList->head->child->data);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->child->child);
  

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

void test_creating_list_element_with_data_as_root_and_name_as_child_and_ABC_as_child_of_name(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *end                = (Token*)createOperatorToken("$");
  
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
	getToken_ExpectAndReturn(end);	
	
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  
  TEST_ASSERT_EQUAL_STRING("data", xmlList->head->data);
  TEST_ASSERT_EQUAL_STRING("name", xmlList->head->child->data);
  TEST_ASSERT_EQUAL_STRING("ABC", xmlList->head->child->child->data);
}


/**
 *
 * given:
 *  <data>
 *			<name>
 * 					<first>ABC</first>
 *    	</name>
 *  </data>
 *
 *
 */

void test_creating_list_element_with_child_inside_a_child(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
  Token *end           = (Token*)createOperatorToken("$");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idFirstName        = (Token*)createIdentifierToken("first");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *contentName        = (Token*)createStringToken("ABC");
	
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
	getToken_ExpectAndReturn(end);	

  xmlList = checkToken();
 
  TEST_ASSERT_EQUAL("data", xmlList->head->data);
  xmlList->head = xmlList->head->child;
  TEST_ASSERT_EQUAL("name", xmlList->head->data);
  xmlList->head = xmlList->head->child;
  TEST_ASSERT_EQUAL("first", xmlList->head->data);
  xmlList->head = xmlList->head->child;
  TEST_ASSERT_EQUAL("ABC", xmlList->head->data);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->child);
  
}

/**
 * 
 * given: 
 *  <data> 
 *    <class>A</class> 
 *		<name>ABC</name>                                       
 *    <age>18</age>
 *  </data>
 *
 *
 */

void test_creating_list_element_with_childs(void){
  CEXCEPTION_T err;
  
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *idClass            = (Token*)createIdentifierToken("class");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentClass        = (Token*)createStringToken("A");
  Token *contentAge         = (Token*)createIntegerToken(18);
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idClass);
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentClass);	
  getToken_ExpectAndReturn(leftAngleBracket);	
  getToken_ExpectAndReturn(slash);
	getToken_ExpectAndReturn(idClass);	
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
	getToken_ExpectAndReturn(end);
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  
  TEST_ASSERT_EQUAL("data", xmlList->head->data);
  xmlList->head = xmlList->head->child;
  TEST_ASSERT_EQUAL("class", xmlList->head->data);
  xmlList->head = xmlList->head->next;
  TEST_ASSERT_EQUAL("name", xmlList->head->data);
  xmlList->head = xmlList->head->next;
  TEST_ASSERT_EQUAL("age", xmlList->head->data);
}

 /**
 * 
 * given: 
 *  <data> 
 *    <class/> 
 *  </data>
 *
 *
 */

void test_selfclosing_tag(void){
  CEXCEPTION_T err;
  
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *idClass            = (Token*)createIdentifierToken("class");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentAge         = (Token*)createIntegerToken(18);
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idClass);	
  getToken_ExpectAndReturn(slash);
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);
  
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  
  TEST_ASSERT_EQUAL_STRING("data", xmlList->head->data);
  xmlList->head = xmlList->head->child;
  TEST_ASSERT_EQUAL_STRING("class", xmlList->head->data);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->next);
 
}

/**
 * 
 * given: 
 *  <data> 
 *    <class/> 
 *		<name>ABC</name>                                       
 *    <age>18</age>
 *  </data>
 *
 *
 */

void test_selfclosing_tag_with_other_tags(void){
  CEXCEPTION_T err;
  
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *idClass            = (Token*)createIdentifierToken("class");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentAge         = (Token*)createIntegerToken(18);
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idClass);	
  getToken_ExpectAndReturn(slash);
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
	getToken_ExpectAndReturn(end);
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  
  TEST_ASSERT_EQUAL("data", xmlList->head->data);
  xmlList->head = xmlList->head->child;
  TEST_ASSERT_EQUAL("class", xmlList->head->data);
  xmlList->head = xmlList->head->next;
  TEST_ASSERT_EQUAL("name", xmlList->head->data);
  xmlList->head = xmlList->head->next;
  TEST_ASSERT_EQUAL("age", xmlList->head->data);
}

/**
 *
 * given:
 *  <data>
 *    <class/>
 *		<name>
 *			<first>ABC</first>
 *		</name>
 *    <age>18</age>
 *  </data>
 *
 *
 */

void test_random_elements(void){
  CEXCEPTION_T err;
  
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idFirst            = (Token*)createIdentifierToken("first");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *idClass            = (Token*)createIdentifierToken("class");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentAge         = (Token*)createIntegerToken(18);
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idClass);	
  getToken_ExpectAndReturn(slash);
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idFirst);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idFirst);	
	getToken_ExpectAndReturn(rightAngleBracket);	
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
	getToken_ExpectAndReturn(end);
	
  xmlList = checkToken();
  
	TEST_ASSERT_EQUAL("data", xmlList->head->data);
  xmlList->head = xmlList->head->child;
  TEST_ASSERT_EQUAL("class", xmlList->head->data);
  xmlList->head = xmlList->head->next;
  TEST_ASSERT_EQUAL("name", xmlList->head->data);
  xmlList->head = xmlList->head->next;
  TEST_ASSERT_EQUAL("age", xmlList->head->data);
  TEST_ASSERT_EQUAL(NULL, xmlList->head->next);
}

/**
 *
 * given:
 *  <data>
 *  //<class/>
 *		<name grade="A" gender="male">
 *			<first>ABC</first>
 *      <last>DEF</last>
 *		</name>
 *    <age>18</age>
 *  </data>
 *
 *
 */

void test_display6(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
	Token *equal              = (Token*)createOperatorToken("=");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idFirst            = (Token*)createIdentifierToken("first");
  Token *idLast            = (Token*)createIdentifierToken("last");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *idClass            = (Token*)createIdentifierToken("class");
  Token *idGrade            = (Token*)createIdentifierToken("grade");
  Token *idGender           = (Token*)createIdentifierToken("gender");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentLast        = (Token*)createStringToken("DEF");
  Token *contentGrade       = (Token*)createStringToken("\"A\"");
  Token *contentGender      = (Token*)createStringToken("\"male\"");
  Token *contentAge         = (Token*)createStringToken("18");
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idClass);	
  getToken_ExpectAndReturn(slash);
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(idGrade);	
	getToken_ExpectAndReturn(equal);
	getToken_ExpectAndReturn(contentGrade);
	getToken_ExpectAndReturn(idGender);
	getToken_ExpectAndReturn(equal);
	getToken_ExpectAndReturn(contentGender);
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idFirst);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idFirst);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idLast);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentLast);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idLast);	
	getToken_ExpectAndReturn(rightAngleBracket);	
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
	getToken_ExpectAndReturn(end);	
  

  xmlList = checkToken();

}

/**
 *
 *                                                    
 *		<name gender = "male"> ABC </name>        
 *                                       
 */
void test_create_attribute_element(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
	Token *equal              = (Token*)createOperatorToken("=");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idGender           = (Token*)createIdentifierToken("gender");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentGrade       = (Token*)createStringToken("\"A\"");
  Token *contentGender      = (Token*)createStringToken("\"male\"");
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();

	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(idGender);
	getToken_ExpectAndReturn(equal);
	getToken_ExpectAndReturn(contentGender);
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);		
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);	
  
  Try{
  xmlList = checkToken();
   }Catch(err){
    printf("%s", err->errorMsg);
  }
  TEST_ASSERT_EQUAL("gender", xmlList->head->attribute->attributeTag);
  TEST_ASSERT_EQUAL("\"male\"", xmlList->head->attribute->attributeContent);
}

/**
 *
 *                                                    
 *		<name gender = "male" grade = "A"> ABC </name>        
 *                                       
 */
void test_create_two_attribute_elements(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
	Token *equal              = (Token*)createOperatorToken("=");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idGender           = (Token*)createIdentifierToken("gender");
  Token *idGrade           = (Token*)createIdentifierToken("grade");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentGrade       = (Token*)createStringToken("\"A\"");
  Token *contentGender      = (Token*)createStringToken("\"male\"");
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();

	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(idGender);
	getToken_ExpectAndReturn(equal);
	getToken_ExpectAndReturn(contentGender);
  getToken_ExpectAndReturn(idGrade);
	getToken_ExpectAndReturn(equal);
	getToken_ExpectAndReturn(contentGrade);
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);		
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);	
  
  Try{
  xmlList = checkToken();
   }Catch(err){
    printf("%s", err->errorMsg);
  }
  TEST_ASSERT_EQUAL("gender", xmlList->head->attribute->attributeTag);
  TEST_ASSERT_EQUAL("\"male\"", xmlList->head->attribute->attributeContent);
  TEST_ASSERT_EQUAL("grade", xmlList->head->attribute->next->attributeTag);
  TEST_ASSERT_EQUAL("\"A\"", xmlList->head->attribute->next->attributeContent);
}

/**
 *  Throw:                                                   
 *		<name ABC DEF</name>        
 *                                       
 */
void test_error_missing_bracket(void){
	ErrorObject* err;
  Tag tag;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);	
  
	Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("\nExpecting a '/' or '>' after the tag.", err->errorMsg);
  }
}

/**
 *  Throw:                                                   
 *		name> ABC DEF</name>        
 *                                       
 */
void test_error_missing_bracket_at_start(void){
	ErrorObject* err;
  Tag tag;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(end);	
  
	Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("\nExpecting '<' symbol at beginning.", err->errorMsg);
  }
}

/**
 *  Throw:                                                   
 *		<name> ABC DEF</name        
 *                                       
 */
void test_error_missing_bra(void){
	ErrorObject* err;
  Tag tag;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(end);	
  
	Try{
  xmlList = checkToken();
	}Catch(err){
    TEST_ASSERT_EQUAL_STRING("\nExpecting a '>' after the close tag.", err->errorMsg);
  }
}

/**
 *  Throw:                                                   
 *		<name> ABC DEF</age>        
 *                                       
 */
void test_error_should_return_wrong_tag_message(void){
	ErrorObject* err;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);
  getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idAge);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);	
  
	Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("\nClosing tag are not same with open tag", err->errorMsg);
  }
}

/**
 *  Throw                                                   
 *		<name> ABC DEF</name        
 *                                       
 */
void test_error_missing_bracket_should_return_message_Expecing_a_right_angle_bracket_after_the_close_tag(void){
	ErrorObject* err;
  Tag tag;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(end);	
  
	Try{
  xmlList = checkToken();
	}Catch(err){
    TEST_ASSERT_EQUAL_STRING("\nExpecting a '>' after the close tag.", err->errorMsg);
  }
}

/**
 *  Throw:                                                   
 *		<name> ABC DEF</name> age        
 *                                       
 */
void test_error_should_return_wrong_tag_messa(void){
	ErrorObject* err;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);
  getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(idAge);	
	getToken_ExpectAndReturn(end);	
  
	Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("Expecting '$' symbol at end.", err->errorMsg);
  }
}

/**
 *  Error:                                                   
 *		<name>> ABC DEF </name>        
 *                                       
 */
void test_error_should_return_expecting_contents_after_right_angle_bracket(void){
  ErrorObject* err;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);
  getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);
  
  Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("\nExpecting contents after '>' symbol. ", err->errorMsg);
  }
}

/**
 *  Error:                                             
 *		<name> ABC DEF </name/>        
 *                                       
 */
void test_error_should_return_expecting_a_right_angle_bracket_after_close_tag(void){
  ErrorObject* err;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *end                = (Token*)createOperatorToken("$");
  
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);
  getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);
  
  Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("\nExpecting a '>' after the close tag.", err->errorMsg);
  }
}

/**
 *  Error:
 *		<name gender "male"> ABC DEF </name>        
 *                                       
 */
void test_error_should_return_Expecting_a_equal_symbol_after_attribute_tag(void){
  ErrorObject* err;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
	Token *equal              = (Token*)createOperatorToken("=");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idGender           = (Token*)createIdentifierToken("gender");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *contentGender      = (Token*)createStringToken("\"male\"");
  Token *end                = (Token*)createOperatorToken("$");
  
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);
	getToken_ExpectAndReturn(idGender);
	getToken_ExpectAndReturn(contentGender);
  getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);
  
  Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("\nExpecting a '=' symbol after attribute tag.", err->errorMsg);
  }
}

/**
 *  Error:
 *		<name = "male"> ABC DEF </name>     
 *                                       
 */
void test_error_should_return_Expecting_a_slash_or_right_angle_bracket_after_the_tag(void){
  ErrorObject* err;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
	Token *equal              = (Token*)createOperatorToken("=");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idGender           = (Token*)createIdentifierToken("gender");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *contentGender      = (Token*)createStringToken("\"male\"");
  Token *end                = (Token*)createOperatorToken("$");
  
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);
	getToken_ExpectAndReturn(equal);
	getToken_ExpectAndReturn(contentGender);
  getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);
  
  Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("\nExpecting a '/' or '>' after the tag.", err->errorMsg);
  }
}

/**
 *  Error:
 *		<18> ABC DEF </18>     
 *                                       
 */
void test_error_should_return_message_Expecting_a_tag_or_slash_after_the_right_angle_bracket_symbol(void){
  ErrorObject* err;
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
	Token *equal              = (Token*)createOperatorToken("=");
  Token *idName             = (Token*)createIntegerToken(18);
  Token *idGender           = (Token*)createIdentifierToken("gender");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentName1       = (Token*)createStringToken("DEF");
  Token *contentGender      = (Token*)createStringToken("\"male\"");
  Token *end                = (Token*)createOperatorToken("$");
  
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);
	getToken_ExpectAndReturn(equal);
	getToken_ExpectAndReturn(contentGender);
  getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(contentName1);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(end);
  
  Try{
  xmlList = checkToken();
	}Catch(err){
    throwTokenError();
    TEST_ASSERT_EQUAL_STRING("Expecting a tag or '/' after the '<' symbol. ", err->errorMsg);
  }
}


/**
 * 
 * given: 
 *  <data> 
 *    <class/> 
 *		<name>ABC</name>                                       
 *    <age>18</age>
 *  </data>
 *
 *
 */

void test_element_search_should_return_ABC(){
  CEXCEPTION_T err;
  
  XmlElement *elem = malloc(sizeof(XmlElement));
  
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *idClass            = (Token*)createIdentifierToken("class");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentAge         = (Token*)createIntegerToken(18);
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idClass);	
  getToken_ExpectAndReturn(slash);
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
	getToken_ExpectAndReturn(end);
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  elem = strListFind(xmlList, "name", strCompare);
  TEST_ASSERT_EQUAL_STRING(elem->child->data, "ABC");
  
}

/**
 * 
 * given: 
 *  <data> 
 *    <class/> 
 *		<name>ABC</name>                                       
 *    <age>18</age>
 *  </data>
 *
 *
 */

void test_element_search_should_return_18(){
  CEXCEPTION_T err;
  
  XmlElement *elem = malloc(sizeof(XmlElement));
  
	Token *leftAngleBracket   = (Token*)createOperatorToken("<");
	Token *rightAngleBracket  = (Token*)createOperatorToken(">");
	Token *slash              = (Token*)createOperatorToken("/");
  Token *idName             = (Token*)createIdentifierToken("name");
  Token *idAge              = (Token*)createIdentifierToken("age");
  Token *idData             = (Token*)createIdentifierToken("data");
  Token *idClass            = (Token*)createIdentifierToken("class");
  Token *contentName        = (Token*)createStringToken("ABC");
  Token *contentAge         = (Token*)createIntegerToken(18);
  Token *end                = (Token*)createOperatorToken("$");
  
	XmlList *xmlList = malloc(sizeof(XmlList));
	
	xmlList = createXmlList();
	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idData);	
	getToken_ExpectAndReturn(rightAngleBracket);	
  getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idClass);	
  getToken_ExpectAndReturn(slash);
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
	getToken_ExpectAndReturn(end);
  Try{
  xmlList = checkToken();
  }Catch(err){
    printf("%s", err->errorMsg);
  }
  elem = strListFind(xmlList, "age", strCompare);
  TEST_ASSERT_EQUAL_STRING("age", elem->data);
  TEST_ASSERT_EQUAL_STRING("18", elem->child->data);
  
}