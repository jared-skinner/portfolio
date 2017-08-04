#include "xml_parser.h"

void printUsageStatement()
{
	printf("%s, Version %s\n\n", PROD_NAME, VERSION);
	printf("Usage xml_parser [--file <file path> | -v | -h]\n\n");
	printf("--file    <file path>  path to xml file to parse\n");
	printf("--help -h              display this usage statement\n");
	printf("--version -v           display version information\n");
	printf("\n");
}


void printVersionStatement()
{
	printf("%s, Version %s\n\n", PROD_NAME, VERSION);
}



void createRootNode(struct xml_node * root_node)
{
	return;
}


void createChildNode()
{

}


void createSiblingNode()
{

}


void createAttribute()
{

}

int parseFileLine(char * line, int line_length)
{
	int i;
	int start_tag = 0;
	int end_tag = 0;
	char node_name[MAX_NODE_NAME];
	char * pattern = "<";

	for (i = 0; i < line_length; i++)
	{
		switch (line[i])
		{
			case '<':
				if (start_tag == 1)
					return FAILURE;

				start_tag = 1;

				break;

			case '>':
				break;

			case '/':
				break;

			case '=':
				break;
		}
	}

	return SUCCESS;
}


int main(int argc, char ** argv)
{
	int i;
	FILE * file;
	char buf[CHUNK];
	char file_path[MAX_FILE_PATH];
	size_t nread;
	struct xml_node root_node;
	int read_file_path = 0;

	// parse arguments 
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i] , "--file") == 0)
		{
			i++;
			// make sure a file path was provided!
			if (i >= argc)
			{
				printUsageStatement();
				return SUCCESS;
			}

			read_file_path = 1;
			strncpy(file_path, argv[i], sizeof(file_path));
		}
		else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
		{
			printUsageStatement();
			return SUCCESS;
		}
		else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
		{
			printVersionStatement();
			return SUCCESS;
		}
		else
		{
			// unknown argument, print usage and exit
			printUsageStatement();
			return SUCCESS;
		}
	}

	// no file argument was provided, print usage and exit
	if (!read_file_path)
	{
		printUsageStatement();
		return SUCCESS;
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

		createRootNode(&root_node);


		printf("%s\n", buf);
	}


	fclose(file);

	return SUCCESS;
}
