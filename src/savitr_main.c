#include "savitr.h"
#include <stdlib.h>

u32 getNumBlocks(const char *fname)
{
	FILE* f;
	u32 numBlocks;

	if ((f = fopen(fname, "rb")) == NULL)
	{
		printf("Cannot open input file\n");
		exit(-1);
	}

	fseek(f, 0L, SEEK_END);
	numBlocks = (u32)ftell(f);
	numBlocks = (numBlocks / 16) + (u32)(numBlocks % 16 != 0);
	fclose(f);
	return numBlocks;
}

/*
 *
 *	File format required - any text file
 *
 */
u32 readText(const char *fname, u8 *text)
{
	FILE* f;
	u32 i, bytesRead;

	if ((f = fopen(fname, "rb")) == NULL)
	{
		printf("Cannot open input file\n");
		exit(-1);
	}
	// printf("\nThe input text is: ");
	for (bytesRead = i = 0; !feof(f) ; i += 16)
	{
		bytesRead += fread(text + i, sizeof(u8), 16, f);
	}
	// printf("\n");
	fclose(f);
	return bytesRead;
}

/*
 *
 *	File format required - 10 lines, each with 4 space-separated 8-digit hex numbers
 *
 */
void readKeys(const char *fname, u32 *keys)
{
	FILE* f;
	u32 inputText;
	int i, j, index;

	if ((f = fopen(fname, "r")) == NULL)
	{
		printf("Cannot open key file\n");
		exit(-1);
	}
	// printf("\nThe round keys are:\n");
	for (i = index = 0; i < 10; ++i)
	{
		for (j = 0; j < 4; ++j, ++index)
		{
			fscanf(f, "%lx", &inputText);
			// printf("%08lx ", inputText);
			keys[index] = inputText;
		}
		// printf("\n");
	}
	fclose(f);
}

/*
 *
 *	Output file format - text
 *
 */
void writeOutput(const char *fname, u8 *output, u32 numBlocks)
{
	FILE* f;
	u32 i;
	u32 len = 16 * numBlocks;

	if ((f = fopen(fname, "w")) == NULL)
	{
		printf("Cannot open output file\n");
		exit(-1);
	}
	printf("\nWriting to output file %s...\n", fname);

	for (i = 0; i < len; ++i)
		fprintf(f, "%c", (unsigned char)output[i]);

	printf("Done writing output.\n");
	fclose(f);
}

void showUsageAndQuit(int argc, const char *argv[])
{
	printf("Usage (encryption): %s e <inputFile> <keyFile> <outputFile>\n", argv[0]);
	printf("Usage (decryption): %s d <inputFile> <keyFile> <outputFile>\n", argv[0]);
	exit(1);
}

int main(int argc, char const *argv[])
{
	u32 keys[40];
	u8 *pt, *ct;
	u32 numBlocks, bytesRead;

	if (argc != 5)
		showUsageAndQuit(argc, argv);

	if (!strcmp(argv[1], "e"))
	{
		numBlocks = getNumBlocks(argv[2]);
		pt = (u8*) malloc(sizeof(u8) * 16 * numBlocks);
		ct = (u8*) malloc(sizeof(u8) * 16 * numBlocks);

		bytesRead = readText(argv[2], pt);
		readKeys(argv[3], keys);

		printf("\nEncrypting...\n");
		savitr_ecb_encrypt(pt, ct, keys, bytesRead);
		printf("\nDone encrypting.\n");

		writeOutput(argv[4], ct, numBlocks);

		free(pt); free(ct);
	}
	else if (!strcmp(argv[1], "d"))
	{
		numBlocks = getNumBlocks(argv[2]);
		ct = (u8*) malloc(sizeof(u8) * 16 * numBlocks);
		pt = (u8*) malloc(sizeof(u8) * 16 * numBlocks);

		bytesRead = readText(argv[2], ct);
		readKeys(argv[3], keys);

		printf("\nDecrypting...\n");
		savitr_ecb_decrypt(ct, pt, keys, bytesRead);
		printf("\nDone decrypting.\n");

		writeOutput(argv[4], pt, numBlocks);

		free(pt); free(ct);
	}
	else
		showUsageAndQuit(argc, argv);

	return 0;
}

