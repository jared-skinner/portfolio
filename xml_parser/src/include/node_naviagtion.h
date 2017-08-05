#ifndef __NODE_NAVIGATION__
#define __NODE_NAVIGATION__


#include "xml_util.h"

void getAttribute();



/**
 * getChildNode()
 *
 * for a given node, get first child node.
 *
 * @param [in]  current_node  - The node we want to find the child of
 *
 * @param [out] child_node    - The child node
 *
 * @return
 *
 *     SUCCESS - We successfully found a child node
 *
 *     FAILURE - We failed to find a child node
 */
int getChildNode(struct xml_node * current_node, struct xml_node ** child_node);



/**
 *
 * getNextSiblingNode()
 *
 * for a given node, get next sibling node.
 *
 * @param [in]  current_node  - The node we want to find the child of
 *
 * @param [out] sibling_node  - The next sibling node
 *
 *
 * @return
 *
 *     SUCCESS - We successfully found the next sibling node
 *
 *     FAILURE - We failed to find the next sibling node
 */
int getNextSiblingNode(struct xml_node * current_node, struct xml_node ** sibling_node);



/**
 * getPreviousSiblingNode()
 *
 * for a given node, get child node.
 *
 * @param [in]  current_node  - The node we want to find the previous sibling of
 *
 * @param [out] child_node    - The previous sibling node
 *
 *
 * @return
 *
 *     SUCCESS - We successfully found the previous sibling node
 *
 *     FAILURE - We failed to find the next sibling node
 */
int getPreviousSiblingNode(struct xml_node * current_node, struct xml_node ** sibling_node);



/**
 * getParentNode()
 *
 * for a given node, get child node.
 *
 * @param [in]  current_node  - The node we want to find the parent of
 *
 * @param [out] child_node    - The parent node
 *
 *
 * @return
 *
 *     SUCCESS - We successfully found the parent node
 *
 *     FAILURE - We failed to find the parent node
 */
int getParentNode(struct xml_node * current_node, struct xml_node ** parent_node);

#endif
