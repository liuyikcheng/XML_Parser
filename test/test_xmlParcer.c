#include "unity.h"
#include "xmlParcer.h"
#include "mock_Token.h"
#include <stdlib.h>
#include "CException.h"
#include "ErrorObject.h"
#include "stdio.h"
void setUp(void){}

void tearDown(void){}

/**
 *
 *Extract info from simple XML code:
 *
 *    <name>ABC</name>
 *
 */

// void test_getToken(void){
	// int i = 8;
	// OperatorToken *op[i];
	// StringToken *st[i];
	// IdentifierToken *id[i];
	// Token *token[i];
	// Tag tag;
	
	// while(i != 0){
		// op[i] = malloc(sizeof(OperatorToken));
		// st[i] = malloc(sizeof(StringToken));
		// id[i] = malloc(sizeof(IdentifierToken));
		// i--;
	// }
	
	// op[1]->symbol = "<";
	// op[1]->type = TOKEN_OPERATOR_TYPE;
	// getToken_ExpectAndReturn((Token*)op[1]);
	
	// id[2]->str = "name";
	// id[2]->type = TOKEN_IDENTIFIER_TYPE;
	// getToken_ExpectAndReturn((Token*)id[2]);
	
	// op[3]->symbol = ">";
	// op[3]->type = TOKEN_OPERATOR_TYPE;
	// getToken_ExpectAndReturn((Token*)op[3]);	
	
	// st[4]->str = "ABC";
	// st[4]->type = TOKEN_STRING_TYPE;
	// getToken_ExpectAndReturn((Token*)st[4]);	
	
	// op[5]->symbol = "<";
	// op[5]->type = TOKEN_OPERATOR_TYPE;
	// getToken_ExpectAndReturn((Token*)op[5]);	
	
	// op[6]->symbol = "/";
	// op[6]->type = TOKEN_OPERATOR_TYPE;
	// getToken_ExpectAndReturn((Token*)op[6]);	
	
	// id[7]->str = "name";
	// id[7]->type = TOKEN_IDENTIFIER_TYPE;
	// getToken_ExpectAndReturn((Token*)id[7]);	
	
	// op[8]->symbol = ">";
	// op[8]->type = TOKEN_OPERATOR_TYPE;
	// getToken_ExpectAndReturn((Token*)op[8]);

	
	// tag = xmlElement(8);
	// printf("\ntag parent is %s", tag.parent);
	// printf("\ntag child is %s", tag.child[0]);
	
// }

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
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *contentName = (Token*)createStringToken("ABC");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	Try{
  tag = checkToken(8);
	}Catch(err){
    printf("what%s", err->errorMsg);
  }
}

/**
 *
 * given:
 *		name>ABC</name>
 * 
 * should throw error
 *
 */
void test_error_should_return_ERR_NO_CLOSING_TAG(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *contentName = (Token*)createStringToken("ABC");
  
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	Try{
  tag = checkToken(8);
	}Catch(err){
    printf("\n Something is wrong \n");
  }
}

/**
 *
 * given:
 *		<name>ABC</name
 * 
 * should throw error
 *
 */
void test_error_should_return_ERR_NO_CLOSING_TAG1(void){
  CEXCEPTION_T err;
  Tag tag;
	Token *leftAngleBracket = (Token*)createOperatorToken("<");
	Token *rightAngleBracket = (Token*)createOperatorToken(">");
	Token *slash = (Token*)createOperatorToken("/");
  Token *idName = (Token*)createIdentifierToken("name");
  Token *contentName = (Token*)createStringToken("ABC");
  
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(idName);	
	getToken_ExpectAndReturn(rightAngleBracket);	
	getToken_ExpectAndReturn(contentName);	
	getToken_ExpectAndReturn(leftAngleBracket);	
	getToken_ExpectAndReturn(slash);	
	getToken_ExpectAndReturn(idName);	
	// getToken_ExpectAndReturn(rightAngleBracket);	
	Try{
  tag = checkToken(7);
	}Catch(err){
    printf("\n Something is wrong \n");
  }
}