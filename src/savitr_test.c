#include "savitr.h"
#include <process.h>

void readText(const char *fname, u8 *text)
{

}

void readKeys(const char *fname, u32 *keys)
{

}

void writeOutput(u8 *output)
{

}

void showUsageAndQuit(int argc, const char *argv[])
{
	printf("Usage (encryption): %s e <inputFile> <keyFile>\n", argv[0]);
	printf("Usage (decryption): %s d <inputFile> <keyFile>\n", argv[0]);
	exit(1);
}

int main(int argc, char const *argv[])
{
	u32 keys[40];
	u8 pt[16], ct[16];

	if (argc != 4)
		showUsageAndQuit(argc, argv);

	if (!strcmp(argv[1], "e"))
	{
		readText(argv[2], pt);
		readKeys(argv[3], keys);
		savitr_encrypt(pt, ct, keys);
		writeOutput(ct);
	}
	else if (!strcmp(argv[1], "d"))
	{
		readText(argv[2], ct);
		readKeys(argv[3], keys);
		savitr_decrypt(ct, pt, keys);
		writeOutput(pt);
	}
	else
		showUsageAndQuit(argc, argv);

	return 0;
}

