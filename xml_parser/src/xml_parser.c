#include "xml_parser.h"

void printUsageStatement(void)
{
	printf("xml parser\n\n");
	printf("Usage xml_parser --file <file path>\n\n");
	printf("--file    <file path>  path to xml file to parse\n");
	printf("--help -h              display this usage statement\n");
	printf("\n");
}


void createRootNode(struct xml_node ** root_node, struct xml_attribute * attributes)
{
	(*root_node)->parent_node           = NULL;
	(*root_node)->child_node            = NULL;
	(*root_node)->previous_sibling_node = NULL;
	(*root_node)->next_sibling_node     = NULL;
	(*root_node)->root_node             = NULL;
	(*root_node)->attributes            = attributes;

	return;
}


void createNextSiblingNode(struct xml_node ** new_node, struct xml_node ** current_node, struct xml_attribute * attributes)
{
	(*current_node)->next_sibling_node = *new_node;

	(*new_node)->child_node            = NULL;
	(*new_node)->next_sibling_node     = NULL;
	(*new_node)->parent_node           = (*current_node)->parent_node;
	(*new_node)->previous_sibling_node = (*current_node);
	(*new_node)->root_node             = (*current_node)->root_node;
	(*new_node)->attributes            = attributes;

	return;
}


void createChildNode(struct xml_node ** new_node, struct xml_node ** current_node, struct xml_attribute * attributes)
{
	(*current_node)->child_node = *new_node;

	(*new_node)->previous_sibling_node = NULL;
	(*new_node)->next_sibling_node     = NULL;
	(*new_node)->child_node            = NULL;
	(*new_node)->parent_node           = (*current_node);

	if ((*current_node)->root_node == NULL)
		(*new_node)->root_node = *current_node;
	else
		(*new_node)->root_node = (*current_node)->root_node;

	(*new_node)->attributes = attributes;

	return;
}


void parseFileLine(char * line, int line_length)
{
	int i;

	for (i = 0; i < line_length; i++)
	{
		switch (line[i])
		{
			case '<':
				break;

			case '>':
				break;


			case '=':
				break;
		}
	}
}


int main(int argc, char ** argv)
{
	int i, interactive;
	FILE * file;
	char buf[CHUNK];
	char file_path[MAX_FILE_PATH];
	size_t nread;
	struct xml_node root_node, current_node;

	// parse arguments 
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i] , "--file") == 0 || strcmp(argv[i], "-f") == 0)
		{
			i++;
			strncpy(file_path, argv[i], sizeof(file_path));
		}

		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
		{
			printUsageStatement();
			return SUCCESS;
		}

		if (strcmp(argv[i], "--interactive") == 0 || strcmp(argv[i], "-i") == 0)
		{
			interactive = TRUE;
		}
	}

	// read in file
	file = fopen(file_path, "r");
	if (!file)
	{
		printf("Error, could not find file\n");
		return FAILURE;
	}

	nread = fread(buf, 1, sizeof(buf), file);
	while (nread > 0)
	{
		nread = fread(buf, 1, sizeof(buf), file) > 0;


		// parse line figure out what's on it.  This could be
		// a label, value, end label, attributes.  Tons of stuff..
		parseFileLine(buf, CHUNK);

		//createRootNode(&root_node, NULL, NULL, NULL, NULL, NULL);
		current_node = root_node;
	}


	if (interactive)
	{
		interactive_shell();
	}


	fclose(file);

	return SUCCESS;
}
