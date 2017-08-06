#ifndef __XML_PARSER__
#define __XML_PARSER__

#include "xml_util.h"
#include "interactive_shell.h"

/**
 * printUsageStatement()
 *
 * Prints out file name, options and usage.
 */
static void printUsageStatement();


/**
 * createRootNode()
 *
 * create the root xml node
 *
 *
 * @param [out] root_node   new root node
 *
 * @param [in]  attributes  an array of xml attributes
 */
void createRootNode(struct xml_node ** root_node, struct xml_attribute * attributes);


/**
 * createNextSiblingNode()
 *
 *
 */
void createNextSiblingNode(struct xml_node ** new_node, struct xml_node ** current_node, struct xml_attribute * attributes);


/**
 * createChildNode()
 *
 *
 */
void createChildNode(struct xml_node ** new_node, struct xml_node ** current_node, struct xml_attribute * attributes);


/**
 * parseFileLine()
 *
 *
 */
void parseFileLine(char * line, int line_length);


#endif
