SAVITR - Readme

1.	Extract all the included .c and .h files, along with the Makefile, into one single directory.

2.	cd into that directory and run "make" ["nmake" on Windows] with the appropriate make target.
	Targets include:
		a)	"main"		-	for "savitr", the program that does full encryption/decryption of any given text file.
							This is the default make target so you can just run "make" instead.
		b)	"timer"		-	for "savitr_timer", which also encrypts/decrypts a full file, but just outputs the 						time taken (in clock cycles) for the encryption/decryption.
		c)	"test"		-	for "savitr_test", the program that just tests one-block encryption/decryption.
		d)	"clean"		-	deletes all executables. [doesn't work on Windows; see "cleanWIN"]
		e)	"cleanWIN"	-	same as "clean", but only for Windows.

3.	"./savitr [e|d] inputFile keyFile outputFile" runs the main program, which reads keys from "keyFile" and input text from "inputFile", and writes the output to "outputFile". If "e" was the second argument, the input is encrypted; if "d" was the second argument, the input is decrypted. Note that, for decryption, the input file is assumed to have a size which is a multiple of the block size (16 bytes) - violation of this may cause unexpected behaviour. [Drop the "./" for running on Windows.]

4.	"./savitr_timer [e|d] inputFile keyFile outputFile" and "./savitr_test [e|d] inputFile keyFile outputFile" run the timer and one-block test programs respectively. All instructions for "savitr" apply here as well. "savitr_test", however, requires input files of a specific format. Please refer to "savitr_test.c" for more details.