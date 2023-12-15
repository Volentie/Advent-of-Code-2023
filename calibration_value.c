#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getFileSize(char *path, FILE **file, long *file_size)
{
	*file = fopen(path, "r");
	if (*file == NULL)
	{
		perror("Error opening file");
		return -1;
	}
	// Getting file size
	fseek(*file, 0, SEEK_END);
	*file_size = ftell(*file);
	// Reset file position indicator to the beginning again
	rewind(*file);
	return 0;
}

char* processFileContents(FILE **file, long file_size)
{
	char *buffer;

	buffer = malloc(file_size + 1);

	if (buffer == NULL)
	{
		perror("Error allocating memory");
		fclose(*file);
		return NULL; 
	}
	fread(buffer, 1, file_size, *file);
	buffer[file_size] = '\0';
	fclose(*file);
	return buffer;
}

int processInputsSum()
{
	long *file_size = malloc(sizeof(long));

	if (file_size == NULL)
	{
		perror("Error allocating memory");
		return -1;
	}

	FILE *file;

	if (getFileSize("input", &file, file_size) != 0) {
		free(file_size);
		return -1;
	};

	printf("file size: %ld\n", *file_size);

	char *strBuf = processFileContents(&file, *file_size);
	if (strBuf == NULL) {
		free(file_size);
		return -1;
	}
	
	int sum = 0;
	int i = 0;
	int fD = -1;
	int lD = -1;
	while (*(strBuf+i) != '\0') {
		if (isdigit(strBuf[i]) && fD == -1)  {
			fD = (strBuf[i] - '0') * 10;
		}
		if (isdigit(strBuf[i])) {
			lD = strBuf[i] - '0';
		}
		if (strBuf[i] == '\n') {
			sum += fD + lD;
			printf("line: %i -> %i, %i, current sum: %i\n", i, fD, lD, sum);
			fD = -1;
			lD = -1;
		}
		i++;
	}

	free(strBuf);
	free(file_size);

	return 0;
}

int main(int argc, char *argv[])
{
	processInputsSum();
	return 0;
}
