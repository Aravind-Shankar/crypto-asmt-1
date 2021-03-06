/*
 *  File name:      savitr_test.c
 *  Author(s):      Team ApBash [Aravind S (EE14B012), Aditya Pradeep (EE14B068)]
 *  Synopsis:       File to test one-block encryption/decyption using savitr.h functions.
 *  Execution:      Compile with savitr.c, or "make test"
 *					Running the executable (encryption): savitr_test e <inputFile> <keyFile> <outputFile>
 *					Running the executable (decryption): savitr_test d <inputFile> <keyFile> <outputFile>
 *
 *					Files should adhere to certail file formats, described in the comments for
 *					the functions below.
 */

#include "savitr.h"
#include <stdlib.h>

/*
 *
 *	Reads one plaintext/ciphertext block from the file "fname" and stores the result in "text"
 *	(assumed to have enough capacity).
 *	Prints the input block to standard output as well, for diagnostic purposes.
 *
 *	File format required - one line with 16 space-separated bytes (i.e. 2-digit hex numbers)
 *
 */
void readText(const char *fname, u8 *text)
{
	FILE* f;
	unsigned int inputText;
	int i;

	if ((f = fopen(fname, "r")) == NULL)
	{
		printf("Cannot open input file\n");
		exit(-1);
	}
	printf("\nThe input text is: ");
	for (i = 0; i < 16; ++i)
	{
		fscanf(f, "%x", &inputText);
		printf("%02x ", inputText);
		text[i] = (u8) inputText;
	}
	printf("\n");
	fclose(f);
}

/*
 *
 *	Reads all round keys from the text file "fname" and stores them in "keys" (assumed large enough).
 *	Prints the keys in order to standard output, for diagnostic purposes.
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
	printf("\nThe round keys are:\n");
	for (i = index = 0; i < 10; ++i)
	{
		for (j = 0; j < 4; ++j, ++index)
		{
			fscanf(f, "%lx", &inputText);
			printf("%08lx ", inputText);
			keys[index] = inputText;
		}
		printf("\n");
	}
	fclose(f);
}

/*
 *
 *	Writes one block of ciphertext/plaintext to the file "fname".
 *	Output file format - one line with 16 space-separated bytes (i.e. 2-digit hex numbers)
 *
 */
void writeOutput(const char *fname, u8 *output)
{
	FILE* f;
	int i;

	if ((f = fopen(fname, "w")) == NULL)
	{
		printf("Cannot open output file\n");
		exit(-1);
	}
	printf("\nWriting to output file...\n");

	for (i = 0; i < 16; ++i)
		fprintf(f, "%02x ", output[i]);

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

// main(), straightforward one-block encryption/decryption using the given command-line args (as above)
int main(int argc, char const *argv[])
{
	u32 keys[40];
	u8 pt[16], ct[16];

	if (argc != 5)
		showUsageAndQuit(argc, argv);

	if (!strcmp(argv[1], "e"))
	{
		readText(argv[2], pt);
		readKeys(argv[3], keys);
		printf("\nEncrypting...\n");
		savitr_encrypt(pt, ct, keys);
		printf("\nDone encrypting.\n");
		writeOutput(argv[4], ct);
	}
	else if (!strcmp(argv[1], "d"))
	{
		readText(argv[2], ct);
		readKeys(argv[3], keys);
		printf("\nDecrypting...\n");
		savitr_decrypt(ct, pt, keys);
		printf("\nDone decrypting.\n");
		writeOutput(argv[4], pt);
	}
	else
		showUsageAndQuit(argc, argv);

	return 0;
}

