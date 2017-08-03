#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_PATH 2048
#define MAX_NODE_VALUE 1024
#define MAX_NODE_NAME 1024
#define MAX_ATTRIBUTE_VALUE 1024
#define MAX_ATTRIBUTE_NAME 1024
#define CHUNK 1024
#define FAILURE 0
#define SUCCESS 1

// main structure type for parsing and xml file
struct xml_node {
	char node_name[MAX_NODE_NAME];       // node name, this cannot be blank
	char value[MAX_NODE_VALUE];          // the value of the node.  Can be blank

	// pointers to other xml elements.  These will be null if not in use
	struct xml_node * previous_sibling_node;
	struct xml_node * next_sibling_node;
	struct xml_node * parent_node;
	struct xml_node * child_node;
};

// double linked list for xml attributes
struct xml_attribute {
	char attribute_name[MAX_ATTRIBUTE_NAME];
	char attribute_value[MAX_ATTRIBUTE_VALUE];

	struct xml_attribute * next_attribute;
	struct xml_attribute * previous_attribute;
};


/**
 * printUsageStatement()
 *
 * Prints out file name, options and usage.
 */
static void printUsageStatement();



