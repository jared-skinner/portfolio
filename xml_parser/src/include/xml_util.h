#ifndef __XML_UTIL__
#define __XML_UTIL__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define PROD_NAME                "xml_parser"
#define VERSION                  "0.0.1.0"
#define MAX_FILE_PATH            2048
#define MAX_NODE_VALUE           1024
#define MAX_NODE_NAME            1024
#define MAX_NUMBER_OF_ATTRIBUTES 100
#define MAX_ATTRIBUTE_VALUE      1024
#define MAX_ATTRIBUTE_NAME       1024
#define CHUNK                    1024
#define FAILURE                  0
#define SUCCESS                  1
#define TRUE                     1
#define FALSE                    0

// double linked list for xml attributes
struct xml_attribute_str {
	char attribute_name[MAX_ATTRIBUTE_NAME];
	char attribute_value[MAX_ATTRIBUTE_VALUE];
};
typedef struct xml_attribute_str xml_attribute;

// main structure type for parsing and xml file
struct xml_node_str {
	// node name, this cannot be blank
	char                  node_name[MAX_NODE_NAME];

	// the value of the node.  Can be blank
	char                  value[MAX_NODE_VALUE];

	// pointers to other xml elements.  These will be null if not in use
	struct xml_node_str * previous_sibling_node;
	struct xml_node_str * next_sibling_node;
	struct xml_node_str * parent_node;
	struct xml_node_str * root_node;

	// pointer to FIRST child node.  Once we have the first child node, we can
	// use the sibling nodes to iterate through the rest
	struct xml_node_str * child_node;

	xml_attribute       * attributes;
};
typedef struct xml_node_str xml_node;

#endif
