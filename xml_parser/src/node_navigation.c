#include "node_naviagtion.h"

void getAttribute()
{


}


int getChildNode(struct xml_node * current_node, struct xml_node ** child_node)
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



int getNextSiblingNode(struct xml_node * current_node, struct xml_node ** sibling_node)
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


int getPreviousSiblingNode(struct xml_node * current_node, struct xml_node ** sibling_node)
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




int getParentNode(struct xml_node * current_node, struct xml_node ** parent_node)
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
