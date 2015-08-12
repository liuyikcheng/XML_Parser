#include "unity.h"
#include "linkedlist.h"
#include "ErrorObject.h"
#include <stdio.h>
#include <malloc.h>

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 *
 *     head------->NULL
 *
 *     tail------->NULL
 *
 *
 **/
void test_createXmlList_function_should__not_return_NULL_but_with_two_pointers_pointing_to_NULL(void)
{
	XmlList *xmlList = malloc(sizeof(XmlList));
	xmlList = createXmlList();

  TEST_ASSERT_NOT_NULL(xmlList);
  TEST_ASSERT_EQUAL(NULL, xmlList->head);
  TEST_ASSERT_EQUAL(NULL, xmlList->tail);
  TEST_ASSERT_EQUAL(0, xmlList->length);
}

/**
 *
 *     |-----------| attribute
 *     |    abc    |-------->NULL
 *     |  XML_TAG  | child
 *     |-----------|-------->NULL
 *          |
 *          |next
 *         \|/
 *         NULL
 *
 **/
void test_createXmlElement_function(void){
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  xmlElement = createXmlElement("abc",XML_TAG);

  TEST_ASSERT_NOT_NULL(xmlElement);
  TEST_ASSERT_EQUAL(NULL, xmlElement->next);
  TEST_ASSERT_EQUAL(NULL, xmlElement->attribute);
  TEST_ASSERT_EQUAL(XML_TAG, xmlElement->type);
  TEST_ASSERT_EQUAL("abc", xmlElement->data);
}

/**
 *
 *     |-----------|
 *     |    abc    |
 *     |  XML_TAG  |
 *     |   NULL    |
 *     |-----------|
 *          |
 *          |next
 *         \|/
 *         NULL
 *
 **/
void test_createXmlAttribute_function(void){
  XmlAttribute *xmlAttribute = malloc(sizeof(XmlAttribute));
  xmlAttribute = createXmlAttribute("test", XML_ATTRIBUTE);

  TEST_ASSERT_NOT_NULL(xmlAttribute);
  TEST_ASSERT_EQUAL(NULL, xmlAttribute->next);
  TEST_ASSERT_EQUAL(NULL, xmlAttribute->attributeContent);
  TEST_ASSERT_EQUAL(XML_ATTRIBUTE, xmlAttribute->type);
  TEST_ASSERT_EQUAL("test", xmlAttribute->attributeTag);

}

/**
 *
 *
 *
 *     head-------> |-----------|    attribute
 *                  |    abc    |-------->NULL
 *                  |  XML_TAG  |    child
 *     tail-------> |-----------|-------->NULL
 *                         |
 *                         |next
 *                        \|/
 *                        NULL
 *
 **/
void test_addList_add_element_into_empty_list(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));

	xmlList = createXmlList();
  xmlElement = createXmlElement("abc",XML_TAG);

  addList(xmlElement, xmlElement, xmlList);

  TEST_ASSERT_NOT_NULL(xmlList->head);
  TEST_ASSERT_NOT_NULL(xmlList->tail);
  TEST_ASSERT_EQUAL("abc", xmlList->head->data);
  TEST_ASSERT_EQUAL("abc", xmlList->tail->data);
  TEST_ASSERT_EQUAL(1, xmlList->length);
}

/**
 *
 *                                                             tail
 *                                                             \|/ 
 *     head-------> |-----------|    attribute            |-----------|    attribute
 *                  |    root    |-------->NULL           |    child  |-------->NULL
 *                  |  XML_TAG  |    child                |  XML_TAG  |    child
 *                  |-----------|------------------------>|-----------|-------->NULL
 *                         |                                   |
 *                         |next                               |next
 *                        \|/                                 \|/
 *                       NULL                                 NULL
 *
 **/
void test_addList_add_one_root_element_and_one_child_element_to_the_list(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement = malloc(sizeof(XmlElement));

  xmlList = createXmlList();
  xmlElement = createXmlElement("root",XML_TAG);
  childXmlElement = createXmlElement("child",XML_TAG);

  addList(xmlElement, xmlElement, xmlList);
  addList(xmlElement, childXmlElement, xmlList);

  TEST_ASSERT_NOT_NULL(xmlList->head);
  TEST_ASSERT_NOT_NULL(xmlList->tail);
  TEST_ASSERT_EQUAL("root", xmlList->head->data);
  TEST_ASSERT_EQUAL("child", xmlList->tail->data);
  TEST_ASSERT_EQUAL(2, xmlList->length);
}

/**
 *
 *          
 *     head-------> |-----------|    attribute            |-----------|    attribute
 *                  |    root    |-------->NULL           |    child  |-------->NULL
 *                  |  XML_TAG  |    child                |  XML_TAG  |    child
 *                  |-----------|------------------------>|-----------|-------->NULL
 *                         |                                   |
 *                         |next                               |next
 *                        \|/                                  |
 *                       NULL                                 \|/ 
 *                                          head-------> |-----------|    attribute
 *                                                       |    abc    |-------->NULL
 *                                                       |  XML_TAG  |    child
 *                                          tail-------> |-----------|-------->NULL
 *                                                         /|\  |
 *                                                 tail-----    |next
 *                                                             \|/
 *                                                            NULL
 **/
void test_addList_add_one_root_element_and_two_child_elements_to_the_list(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement2 = malloc(sizeof(XmlElement));

  xmlList = createXmlList();
  xmlElement = createXmlElement("root",XML_TAG);
  childXmlElement = createXmlElement("child1",XML_TAG);
  childXmlElement2 = createXmlElement("child2",XML_TAG);

  addList(xmlElement, xmlElement, xmlList);
  addList(xmlElement, childXmlElement, xmlList);
  addList(xmlElement, childXmlElement2, xmlList);

  TEST_ASSERT_NOT_NULL(xmlList->head);
  TEST_ASSERT_NOT_NULL(xmlList->tail);
  TEST_ASSERT_EQUAL("root", xmlList->head->data);
  TEST_ASSERT_EQUAL("child2", xmlList->tail->data);
  TEST_ASSERT_EQUAL(3, xmlList->length);
}

void test_addList_add_one_root_element_and_three_child_elements_to_the_list(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement2 = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement3 = malloc(sizeof(XmlElement));

  xmlList = createXmlList();
  xmlElement = createXmlElement("root", XML_TAG);
  childXmlElement = createXmlElement("child1", XML_TAG);
  childXmlElement2 = createXmlElement("child2", XML_TAG);
  childXmlElement3 = createXmlElement("child3", XML_TAG);

  addList(xmlElement, xmlElement, xmlList);
  addList(xmlElement, childXmlElement, xmlList);
  addList(xmlElement, childXmlElement2, xmlList);
  addList(xmlElement, childXmlElement3, xmlList);

  TEST_ASSERT_NOT_NULL(xmlList->head);
  TEST_ASSERT_NOT_NULL(xmlList->tail);
  TEST_ASSERT_EQUAL("root", xmlList->head->data);
  TEST_ASSERT_EQUAL("child3", xmlList->tail->data);
  TEST_ASSERT_EQUAL(4, xmlList->length);
}

void test_addListAttribute_function(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  XmlAttribute *xmlAttribute = malloc(sizeof(XmlAttribute));

  xmlList = createXmlList();
  xmlElement = createXmlElement("root", XML_TAG);
  xmlAttribute = createXmlAttribute("a", XML_ATTRIBUTE);

  addList(xmlElement, xmlElement, xmlList);
  addListAttribute(xmlElement, xmlAttribute, xmlList);

  TEST_ASSERT_NOT_NULL(xmlList->head);
  TEST_ASSERT_NOT_NULL(xmlList->tail);
  TEST_ASSERT_EQUAL("root", xmlList->head->data);
  TEST_ASSERT_EQUAL("root", xmlList->tail->data);
  TEST_ASSERT_EQUAL(XML_TAG, xmlList->tail->type);
  TEST_ASSERT_EQUAL("a", xmlList->tail->attribute->attributeTag);
  TEST_ASSERT_EQUAL(XML_ATTRIBUTE, xmlList->tail->attribute->type);
  TEST_ASSERT_EQUAL(NULL, xmlList->tail->attribute->attributeContent);
  TEST_ASSERT_EQUAL(2, xmlList->length);
}

void test_addListAttributeContent_function(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  XmlAttribute *xmlAttribute = malloc(sizeof(XmlAttribute));

  xmlList = createXmlList();
  xmlElement = createXmlElement("root", XML_TAG);
  xmlAttribute = createXmlAttribute("a", XML_ATTRIBUTE);

  addListAttribute(xmlElement, xmlAttribute, xmlList);
  addListAttributeContent(xmlElement, "13");
  addList(xmlElement, xmlElement, xmlList);

  TEST_ASSERT_EQUAL("root", xmlList->head->data);
  TEST_ASSERT_EQUAL("root", xmlList->tail->data);
  TEST_ASSERT_EQUAL(XML_TAG, xmlList->head->type);
  TEST_ASSERT_EQUAL("a", xmlList->head->attribute->attributeTag);
  TEST_ASSERT_EQUAL(XML_ATTRIBUTE, xmlList->head->attribute->type);
  TEST_ASSERT_EQUAL("13", xmlList->head->attribute->attributeContent);
}

void test_add_two_attribute_into_an_element(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  XmlAttribute *xmlAttribute = malloc(sizeof(XmlAttribute));
  XmlAttribute *xmlAttribute2 = malloc(sizeof(XmlAttribute));

  xmlList = createXmlList();
  xmlElement = createXmlElement("root", XML_TAG);
  xmlAttribute = createXmlAttribute("a", XML_ATTRIBUTE);
  xmlAttribute2 = createXmlAttribute("b", XML_ATTRIBUTE);

  addListAttribute(xmlElement, xmlAttribute, xmlList);
  addListAttributeContent(xmlElement, "13");
  addListAttribute(xmlElement, xmlAttribute2, xmlList);
  addListAttributeContent(xmlElement, "20");
  addList(xmlElement, xmlElement, xmlList);

  TEST_ASSERT_EQUAL("root", xmlList->head->data);
  TEST_ASSERT_EQUAL("root", xmlList->tail->data);
  TEST_ASSERT_EQUAL(XML_TAG, xmlList->head->type);
  TEST_ASSERT_EQUAL("a", xmlList->head->attribute->attributeTag);
  TEST_ASSERT_EQUAL("b", xmlList->head->attribute->next->attributeTag);
  TEST_ASSERT_EQUAL("13", xmlList->head->attribute->attributeContent);
  TEST_ASSERT_EQUAL("20", xmlList->head->attribute->next->attributeContent);
}

void test_strListFind_function(void){
  XmlList *xmlList = malloc(sizeof(XmlList));
  XmlElement *xmlElement = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement2 = malloc(sizeof(XmlElement));
  XmlElement *childXmlElement3 = malloc(sizeof(XmlElement));
  XmlElement *elem;

  xmlList = createXmlList();
  xmlElement = createXmlElement("root", XML_TAG);
  childXmlElement = createXmlElement("child1", XML_TAG);
  childXmlElement2 = createXmlElement("child2", XML_TAG);
  childXmlElement3 = createXmlElement("child3", XML_TAG);

  addList(xmlElement, xmlElement, xmlList);
  addList(xmlElement, childXmlElement, xmlList);
  addList(xmlElement, childXmlElement2, xmlList);
  addList(xmlElement, childXmlElement3, xmlList);

  elem = strListFind(xmlList, "child2", strCompare);

  TEST_ASSERT_NOT_NULL(elem);
  TEST_ASSERT_NOT_NULL(elem->data);
  TEST_ASSERT_EQUAL("child2", elem->data);

}