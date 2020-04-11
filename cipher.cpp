#include <iostream>
#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <fstream>

using namespace std;



static void appendLineToFile(string filepath, string output);
void AES_DES (string userinput,string cipherName,string keyInput,string functype,string inputFile,string outputFile);

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
	
	string userinput;

	//cipher name
	string cipherName = argv[1];
	//key
	string keyInput = argv[2];
	//ENC or DEC
	string functype = argv[3];
	// input file
	string inputFile = argv[4];
	//output file
	string outputFile = argv[5];

	// Block size
	int blockSize = -1;
	
	//For handling if AES is for encrypt or decrypt
	// This sets the key to be encrypt ahead of time
	//if(cipherName == "AES" && functype == "ENC"){
	//	//string zerozero = "00";
	//	keyInput = "00" + keyInput;
	//}

	// The cipher interface
	CipherInterface* cipher = NULL;
	
	// We are doing DES
	if(cipherName == "DES")
	{
		// Set the block size to 64 bits
		blockSize = 8;
		
		cipher = new DES();

		/* Error checks */
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
		
		/* Set the encryption key
		* A valid key comprises 16 hexidecimal
		* characters. Below is one example.
		* Your program should take input from
		* command line.
		*/
		cipher->setKey((unsigned char*)keyInput.c_str());

	}
	// We are doing AES
	else 
	{
		blockSize = 16;
		cipher = new AES();
		
		// Set the flag for encryption
		if(functype == "ENC")
			keyInput = "0" + keyInput;
		// Set the flag for decryption
		else keyInput = "1" + keyInput;

		cipher->setKey((unsigned char*)keyInput.c_str());		
		fprintf(stderr, "Set the AES key!");
	}
	
	// Create a block
	unsigned char block[blockSize];
	
	int numWritten = -1;

	
	//ifstream infile;
	//infile.open(inputFile.c_str());
	
	
	
	char singleChar;

	// Open the file for reading
	FILE* inFilePtr = fopen(inputFile.c_str(), "rb");
	
	
	// Open the output file
	FILE* outFilePtr = fopen(outputFile.c_str(), "wb");
	
	// The number of bytes read
	int numBytesRead = -1;
	
	// The processed text
	unsigned char* processedText = NULL;



	



	/* Create an instance of the DES cipher */	
	// Sanity check!
	if(!inFilePtr)
	{
		perror("fopen() for input file");
		exit(-1);
	}
	

	// Sanity check!
	if(!outFilePtr)
	{
		perror("fopen for output file");
		exit(-1);
	}
	
	// Read the entire file
	while(!feof(inFilePtr))
	{
		
		// Read a block
		numBytesRead = fread(block, 1, blockSize, inFilePtr);
		
		// Process any bytes if you have read them
		if(numBytesRead != 0)
		{
			
			// Encrypt
			if(functype == "ENC")
			{
				// Padd the incomplete block
				for(int i = numBytesRead; i < blockSize; i++){
					block[i] = '0';	
				}
				
				processedText = cipher->encrypt((const unsigned char*)block);
				
					
			}
			// Do decrypt
			else if(functype == "DEC")
			{
		//		fprintf(stderr, "Decrypt!");
				processedText = cipher->decrypt((const unsigned char*)block);	
		//		fprintf(stderr, "Dome!");
			}
			// Wrong mode
			else
			{
				fprintf(stderr, "ERROR %s is an invalid mode!\n", functype.c_str());
				exit(-1);
			}			
			
			//fwrite
			numWritten = fwrite(processedText, 1, blockSize, outFilePtr); 

			// Make sure the write succeeded
			if(numWritten != blockSize)
			{
				fprintf(stderr, "Could not save the output!\n");
				exit(-1);
			}
		}
	}
		

	return 0;
}