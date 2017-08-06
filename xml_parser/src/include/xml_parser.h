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
 * printVersionStatement();
 *
 * Prints out version information
 */
void printVersionStatement();


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
void createRootNode(xml_node ** root_node, xml_attribute * attributes);


/**
 * createNextSiblingNode()
 *
 *
 */
void createNextSiblingNode(xml_node ** new_node, xml_node ** current_node, xml_attribute * attributes);


/**
 * createChildNode()
 *
 *
 */
void createChildNode(xml_node ** new_node, xml_node ** current_node, xml_attribute * attributes);


/**
 * parseFileLine()
 *
 *
 */
int parseFileLine(char * line, int line_length);

#endif
