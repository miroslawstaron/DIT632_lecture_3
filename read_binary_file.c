/*
* Creating, reading and writing a file
*/
#include <stdlib.h>		
#include <stdio.h>		// Note! this is the header file which allows us to work with files

#define MAX 20			// max number of characters to read

void demo_file_binary()
{
	FILE* pFileToCreate;	// file which we will create

	// location to my file
	// let's use the same file as before to check how the reading looks like
	char* strFilename = "myTestFile.txt";

	// open the file to read
	// Note! to read binary file we need to change the modifier - rb instead of just r
	pFileToCreate = fopen(strFilename, "rb");

	// a good practice when working with files is to check
	// that the file pointer is correct, i.e. the file was opened
	// in the way we wanted
	if (pFileToCreate != NULL)
	{
		// if the file was opened (see the flag)
		// we can do something with it
		// here I chose to read a string from the file

		char cValToRead = '0';	// value to read, initialized with 0 just to reserve some space

		fread(&cValToRead,				// where we store the value
			  sizeof(cValToRead),		// the size of the single element
			  1,						// how many elements we should read
			  pFileToCreate);			// where we should read them from (file)

		// and print the result on the console
		printf("%c \n", cValToRead);

		// now, version with the buffer
		char* pstrBuffer; 

		// reserve a place in memory for MAX characters
		pstrBuffer = malloc(MAX * sizeof(char));

		// now, let's make it fail safe wrt memory
		// and check if the memory was actually allocated
		if (pstrBuffer != NULL)
		{
			// read the number of elements to the buffer
			fread(pstrBuffer, 
				  sizeof(char), 
				  MAX-1, 
				  pFileToCreate); 

			// end of string in order to avoid printing random memory content
			pstrBuffer[MAX-1] = '\0';

			// let's print them and see what happens
			printf("%s \n", pstrBuffer);

			// don't forget to free the memory
			free(pstrBuffer);
		}
		else // the memory could not be allocated
		{
			printf("Error - memory could not be allocated!");
		}

		// and please remember to close the file
		// if we do not close the file, the data may be lost
		fclose(pFileToCreate);
	}
	else	// if the file was not opened, e.g. does not exists
	{
		printf("Error opening file %s.", strFilename);
	}	
}