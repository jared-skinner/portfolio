#include "xml_parser.h"

void printUsageStatement(void)
{
	printf("xml parser\n\n");
	printf("Usage xml_parser --file <file path>\n\n");
	printf("--file    <file path>  path to xml file to parse\n");
	printf("--help -h              display this usage statement\n");
	printf("\n");
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


int main(int argc, char ** argv)
{
	int i;
	FILE * file;
	char buf[CHUNK];
	char file_path[MAX_FILE_PATH];
	size_t nread;
	struct xml_node root_node;

	// parse arguments 
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i] , "--file") == 0)
		{
			i++;
			strncpy(file_path, argv[i], sizeof(file_path));
		}

		if (strcmp(argv[i], "--help") == 0)
		{
			printUsageStatement();
			return SUCCESS;
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


		// parse line figure out what's on it.  This could be anything from
		// just a label to label, value, end label, attributes.  Tons of stuff..
		createRootNode(&root_node);


		printf("%s\n", buf);
	}


	fclose(file);

	return SUCCESS;
}
