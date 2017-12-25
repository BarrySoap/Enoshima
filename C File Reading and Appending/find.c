#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *input;
	FILE *output;
	char buffer[50];
	int isearch = 0;
	int osearch = 0;
	int tmptmp = 10;
	int c = 0;
	
	do {
		for (int i = 0; i < argc; i++)
		{
			if (strcmp(argv[i], "-i") == 0)
			{
				isearch = 0;
				continue;
			} else {
				c++;
			}
		}
	} while (isearch == 1);
	
	do {
		for (int i = 0; i < argc; i++)
		{
			if (strcmp(argv[i], "-o") == 0)
			{
				osearch = 0;
				continue;
			} else {
				c++;
			}
		}
	} while (osearch == 1);
	
	if (c == 3 || c == 6)
	{
		printf("%s\n", argv[1]);
		printf("No input/output filename provided!\n");
		printf("Usable arguments: -i -o -c\n Example prompt: find hello -i input.txt -o output.txt -c\n");
		exit(0);
	}
	
	if (strcmp("-i", argv[2]) == 0)
	{
		FILE *pFile;
		char string[100]; 
		char *tmp = (char*)malloc(100 * sizeof(char));
		tmp[0] = 0;
		
		pFile = fopen (argv[3],"r");
		
		if (pFile != NULL) {
			while(fgets(string, 100, pFile) != NULL) 
			{
				if (argc == 7)
				{
					if (strcmp(argv[6], "-c") == 0)
					{
						for(int i = 0; string[i]; i++)
						{
							string[i] = tolower(string[i]);
						}
					}
				}
				strcpy(tmp, string);
				while (strstr(tmp, argv[1]))
				{
					if (strstr(string, argv[1])) 
					{
						tmptmp = 20;
						printf("%s found in file!\n", argv[1]);
					} else {
						printf("%s can't be found in file.\n", argv[1]);
					}
					printf("%s was found in ", argv[1]);
					printf("%s\n", string);
					tmp = strstr(tmp, argv[1]);
					tmp++;
				} 
			}	
		} else{
			exit(1);
		}
		fclose (pFile);
	}
		
	if (tmptmp == 10) 
	{
		printf("String can't be found within the given file!\n");
		exit(0);
	} 
		if (strcmp("-o", argv[4]) == 0)
		{
			output = fopen(argv[5], "w");
			if(!output)
			{
				printf("The output file is invalid!");
				exit(1);
			}
			fprintf(output, "%s", argv[1]);
			fclose(output);
			//free(tmp); // malloc for tmp cannot be freed
		} else {
			printf(" Invalid argument given.\n Usable arguments: -i -o -c\n Example prompt: find hello -i input.txt -o output.txt -c");
		}
	return 0;
}