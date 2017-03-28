/*
 *  File name:      savitr_main.c
 *  Author(s):      Team ApBash [Aravind S (EE14B012), Aditya Pradeep (EE14B068)]
 *  Synopsis:       File to implement full ECB mode encryption/decyption using savitr.h functions.
 *  Execution:      Compile with savitr.c, or "make" (or "make main")
 *					Running the executable (encryption): savitr e <inputFile> <keyFile> <outputFile>
 *					Running the executable (decryption): savitr d <inputFile> <keyFile> <outputFile>
 *
 *					In/out files can be any files. Key file must adhere to a format, mentioned below in
 *					the comments for readKeys().
 */

#include "savitr.h"
#include <stdlib.h>

// Helper function to calculate the number of blocks to encrypt - to allocate the required memory for input text
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
 *	Reads input plaintext/ciphertext from file "fname" (to a max of "maxLen" chars)
 *	and stores the result in "text" (assumed large enough).
 *	Also returns the actual number of bytes read.
 *
 *	File format required - any text file
 *
 */
u32 readText(const char *fname, u8 *text, u32 maxLen)
{
	FILE* f;
	u32 bytesRead;

	if ((f = fopen(fname, "rb")) == NULL)
	{
		printf("Cannot open input file\n");
		exit(-1);
	}
	
	if (!feof(f))
		for (bytesRead = 0; bytesRead < maxLen; ++text, ++bytesRead)
		{
			(*text) = (u8)fgetc(f);
			if (feof(f)) break;		// checking at end of loop to ensure EOF is not read as well
		}
	
	fclose(f);
	return bytesRead;
}

/*
 *
 *	Reads all round keys from the text file "fname" and stores them in "keys" (assumed large enough).
 *	
 *	File format required - 10 lines, each with 4 space-separated 8-digit hex numbers.
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
	
	for (i = index = 0; i < 10; ++i)
	{
		for (j = 0; j < 4; ++j, ++index)
		{
			fscanf(f, "%lx", &inputText);
			keys[index] = inputText;
		}
	}
	fclose(f);
}

/*
 *
 *	Writes "len" output bytes stored in "output" to the file "fname".
 *	Output file format - normal text file.
 *
 */
void writeOutput(const char *fname, u8 *output, u32 len)
{
	FILE* f;
	u32 i;
	
	if ((f = fopen(fname, "wb")) == NULL)
	{
		printf("Cannot open output file\n");
		exit(-1);
	}
	printf("\nWriting to output file %s...\n", fname);

	for (i = 0; i < len; ++i)
		fputc(output[i], f);

	printf("Done writing output.\n");
	fclose(f);
}

// function to show correct usage and exit, if input command-line args were incorrect
void showUsageAndQuit(int argc, const char *argv[])
{
	printf("Usage (encryption): %s e <inputFile> <keyFile> <outputFile>\n", argv[0]);
	printf("Usage (decryption): %s d <inputFile> <keyFile> <outputFile>\n", argv[0]);
	exit(1);
}

// main(), straightforward full ECB encryption/decryption using the given command-line args (as above)
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

		bytesRead = readText(argv[2], pt, 16 * numBlocks);
		readKeys(argv[3], keys);

		printf("\nEncrypting...\n");
		savitr_ecb_encrypt(pt, ct, keys, bytesRead);
		printf("\nDone encrypting.\n");

		writeOutput(argv[4], ct, 16 * numBlocks);

		free(pt); free(ct);
	}
	else if (!strcmp(argv[1], "d"))
	{
		numBlocks = getNumBlocks(argv[2]);
		ct = (u8*) malloc(sizeof(u8) * 16 * numBlocks);
		pt = (u8*) malloc(sizeof(u8) * 16 * numBlocks);
		
		bytesRead = readText(argv[2], ct, 16 * numBlocks);
		readKeys(argv[3], keys);

		printf("\nDecrypting...\n");
		savitr_ecb_decrypt(ct, pt, keys, 16 * numBlocks);
		printf("\nDone decrypting.\n");

		writeOutput(argv[4], pt, 16 * numBlocks);

		free(ct); free(pt);
	}
	else
		showUsageAndQuit(argc, argv);

	return 0;
}

