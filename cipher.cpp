#include <iostream>
#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <fstream>

using namespace std;

static void appendLineToFile(string filepath, unsigned char* output);
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

	ifstream infile;
	infile.open(inputFile);
	char singleChar;

	while(infile >> singleChar){
		userinput += singleChar;
		if(userinput.length() == 8 && cipherName == "DES"){
			AES_DES(userinput,cipherName,keyInput,functype,inputFile,outputFile);
			userinput = "";
		}
		if(userinput.length() == 16 && cipherName == "AES"){
			AES_DES(userinput,cipherName,keyInput,functype,inputFile,outputFile);
			userinput = "";
		}
	}

	// Padding for short blocks
	if(userinput.length() != 0 && cipherName == "DES"){
		int padlength = 8-userinput.length();
		while(padlength != 0){
			padlength--;
			userinput += 'X';
		}
		AES_DES(userinput,cipherName,keyInput,functype,inputFile,outputFile);
	}
	if(userinput.length() != 0 && cipherName == "AES"){
		int padlength = 16-userinput.length();
		while(padlength != 0){
			padlength--;
			userinput += 'X';
		}
		AES_DES(userinput,cipherName,keyInput,functype,inputFile,outputFile);
	}

	return 0;
}

void AES_DES (string userinput,string cipherName,string keyInput,string functype,string inputFile,string outputFile)
{
	//DES cipher
	if(cipherName == "DES")
	{
		

		/* Create an instance of the DES cipher */	
		CipherInterface* cipher = new DES(); 
			
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
		
		/* Perform encryption */
		if(functype == "ENC")
		{
			unsigned char* cipherText = {cipher->encrypt((unsigned char*)userinput.c_str())};
			appendLineToFile(inputFile, cipherText);
		}
		if(functype == "DEC")
		{
		/* Perform decryption */
		const unsigned char* userinputTemp = reinterpret_cast<const unsigned char*>(userinput.c_str());
		unsigned char* plaintext;
		plaintext = cipher->decrypt(userinputTemp);
		appendLineToFile(outputFile, plaintext);
		}
	
	}
	
	//AES cipher
	else if(cipherName == "AES")
	{
		// Create an instance of the AES cipher 	
		CipherInterface* cipher = new AES(); 

		/* Error checks */
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}

		if(functype == "ENC")
		{
		//set encryption key
		cout <<"Setting key." << endl;
		cipher->setKey((unsigned char*)keyInput.c_str());
		cout<<"Successfully set key." << endl;

		//perform encryption
		
		unsigned char* ciphertext = cipher->encrypt((unsigned char*)userinput.c_str());
		appendLineToFile(inputFile, ciphertext);
		}
		if(functype == "DEC")
		{
		//set decryption key
		cipher->setKey((unsigned char*)keyInput.c_str());

		//perform decryption
		const unsigned char* userinputTemp = reinterpret_cast<const unsigned char*>(userinput.c_str());
		unsigned char* plaintext;
		plaintext = cipher->decrypt(userinputTemp);
		appendLineToFile(outputFile, plaintext);
		}
	}
	else
	{
		cout << cipherName << " is not a valid type of cipher" << endl;
	}
}

static void appendLineToFile(string outputfile, unsigned char* output)
{
    ofstream file;
    file.open(outputfile, std::ios::out | std::ios::app);
    if (file.fail())
        throw std::ios_base::failure(strerror(errno));

    //make sure write fails with exception if something is wrong
    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    file << output;
}
