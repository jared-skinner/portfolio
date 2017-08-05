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
	int i, err;
	char node_name[MAX_NODE_NAME];
	regex_t start_tag;
	regex_t end_tag;
	regex_t full_tag;
	// TODO: 5 is the max number of groups to match.  Get rid of the magic
	// number!
	regmatch_t groupArray[5];

	// compile regular expressions
	// TODO: we really only need to compile these once, find a more efficent way
	// of doing this
	if(regcomp(&start_tag, "^\\s*<(\\w*)>\\s*$", REG_EXTENDED) != 0)
	{
		printf("Failed to compile regex");
		return FAILURE;
	}

	if(regcomp(&end_tag, "^\\s*<\\/\\w*>\\s*$", REG_EXTENDED) != 0)
	{
		printf("Failed to compile regex");
		return FAILURE;
	}

	if(regcomp(&full_tag, "^\\s*<(\\w*)>(.*)<\\/\\w*>\\s*$", REG_EXTENDED) != 0)
	{
		printf("Failed to compile regex");
		return FAILURE;
	}




	// match line
	if (regexec(&full_tag, line, 1, groupArray, 0) == 0)
	{
		for (i = 0; i < 5; i++)
		{
			if (groupArray[i].rm_so == (size_t)-1)
				break; // No more groups

			char sourceCopy[strlen(line) + 1];
			strcpy(sourceCopy, line);
			sourceCopy[groupArray[i].rm_eo] = 0;
			printf("Group %u: [%2u-%2u]: %s\n", i, groupArray[i].rm_so, groupArray[i].rm_eo, sourceCopy + groupArray[i].rm_so);
		}

		printf("Found full tag!\n");
		printf("%s\n\n\n", line);
		return SUCCESS;
	}


	if (regexec(&start_tag, line, 0, NULL, 0) == 0)
	{
		printf("Found start tag!\n");
		printf("%s\n\n\n", line);
		return SUCCESS;
	}

	if (regexec(&end_tag, line, 0, NULL, 0) == 0)
	{
		printf("Found end tag!\n");
		printf("%s\n\n\n", line);
		return SUCCESS;
	}






	return SUCCESS;
}


int main(int argc, char ** argv)
{
	int i;
	FILE * file;
	char * line;
	char file_path[MAX_FILE_PATH];
	size_t bytes_read, len;
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

	while (getline(&line, &len, file) != -1)
	{
		// parse line figure out what's on it.  This could be
		// a label, value, end label, attributes.  Tons of stuff..

		parseFileLine(line, CHUNK);

		//createRootNode(&root_node);
	}


	fclose(file);

	return SUCCESS;
}
