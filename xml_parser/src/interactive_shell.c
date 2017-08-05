#include "interactive_shell.h"


void print_help()
{
	printf("      Options:\n\n");
	printf("h/? - Print this help message\n");
	printf("p   - quite interactive mode\n");
	printf("n   - get next sibling node and print name\n");
	printf("p   - get previous siblng node and print name\n");
	printf("c   - get child node and print name\n");
	printf("r   - get parent node and print name\n");
	printf("o   - get root node and print name\n");
}


void interactive_shell()
{
	char character;
	struct xml_node * current_node;

	while (TRUE)
	{
		printf("\n");
		printf("> ");
		character = getchar();
		getchar();

		switch (character)
		{
			case '\n':
				break;

			//quit
			case 'q':
				return;

			case 'h':
			case '?':
				print_help();
				break;

			case 'n':
				getNextSiblingNode(current_node, &current_node);
				printf("next_node!\n");
				break;

			case 'p':
				getPreviousSiblingNode(current_node, &current_node);
				printf("previous node!\n");
				break;

			case 'c':
				getChildNode(current_node, &current_node);
				printf("child node!\n");
				break;

			case 'r':
				getParentNode(current_node, &current_node);
				printf("parent node!\n");
				break;

			case 'o':
				// TODO: write this function!
				//getRootNode(current_node, &current_node);
				printf("parent node!\n");
				break;

			default:
				printf("Unknown Option!\n\n");
				print_help();
				break;
		}
		if (character == 'q')
			break;
	}
}


