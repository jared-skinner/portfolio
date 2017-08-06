#include "node_naviagtion.h"


int getChildNode(xml_node * current_node, xml_node ** child_node)
{
	if (current_node->child_node)
	{
		*child_node = current_node->child_node;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}


int getNextSiblingNode(xml_node * current_node, xml_node ** sibling_node)
{
	if (current_node->child_node)
	{
		*sibling_node = current_node->next_sibling_node;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}


int getPreviousSiblingNode(xml_node * current_node, xml_node ** sibling_node)
{
	if (current_node->child_node)
	{
		*sibling_node = current_node->previous_sibling_node;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}


int getParentNode(xml_node * current_node, xml_node ** parent_node)
{
	if (current_node->child_node)
	{
		*parent_node = current_node->parent_node;
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}


int  getRootNode(xml_node * current_node, xml_node ** root_node)
{
	if (current_node->root_node)
	{
		*root_node = current_node->root_node;
		return SUCCESS;
	}
	else
	{
		// the only node which should not have root node assigned is the root
		// node itself.  In this case return FAILURE, to indicate as much.
		*root_node = current_node;
		return FAILURE;
	}
}
