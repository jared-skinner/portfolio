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
	int ready_for_command = TRUE;
	xml_node * current_node;

	while (TRUE)
	{
		if (ready_for_command == TRUE)
		{
			printf("\n");
			printf("> ");
			character = getchar();
			ready_for_command = FALSE;
		}

		// we only want to consume one character at a time.  If the user entered
		// more than one command, ignore all the rest.
		if (getchar() == '\n')
			ready_for_command = TRUE;
		else
			continue;

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
				getRootNode(current_node, &current_node);
				printf("root node!\n");
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
