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

	ifstream infile;
	infile.open(inputFile.c_str());
	char singleChar;

	while(infile >> noskipws >> singleChar){
		userinput += singleChar;
		cout << singleChar << endl;
		if(userinput.length() == 8 && cipherName == "DES"){
			AES_DES(userinput,cipherName,keyInput,functype,inputFile,outputFile);
			//cout << userinput << endl;
			userinput = "";
		}
		if(userinput.length() == 16 && cipherName == "AES"){
			AES_DES(userinput,cipherName,keyInput,functype,inputFile,outputFile);
			userinput = "";
			cout << userinput << endl;
		}
	}

	// Padding for short blocks
	if(userinput.length() != 0 && cipherName == "DES"){
		//cout << "Inside Pad if" << endl;
		//cout << userinput.length() << endl;
		int padlength = 8-userinput.length();
		while(padlength != 0){
			padlength--;
			userinput += '0';
		}
		//cout << userinput << endl;
		AES_DES(userinput,cipherName,keyInput,functype,inputFile,outputFile);
	}
	if(userinput.length() != 0 && cipherName == "AES"){
		cout << "Inside Pad if" << endl;
		cout << userinput.length() << endl;
		int padlength = 16-userinput.length();
		while(padlength != 0){
			padlength--;
			userinput += '0';
		}
		cout << userinput << endl;
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
			//cout << userinput << endl;
			unsigned char* cipherText = {cipher->encrypt((unsigned char*)userinput.c_str())};
			//cout << cipherText << endl;
			string encOutput = (reinterpret_cast<char*>(cipherText));
			appendLineToFile(outputFile, encOutput);
		}
		if(functype == "DEC")
		{
		/* Perform decryption */
		const unsigned char* userinputTemp = reinterpret_cast<const unsigned char*>(userinput.c_str());
		//cout << "user input " << endl;
		//cout << userinput << endl;
		unsigned char* plaintext;
		//cout << "plaintext " << endl;
		//cout << plaintext << endl;
		plaintext = cipher->decrypt(userinputTemp);
		string decOutput = (reinterpret_cast<char*>(plaintext));
		//cout << "decOutput " << endl;
		//cout << decOutput << endl;
		appendLineToFile(outputFile, decOutput);
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
		//cout <<"Setting key." << endl;
		cipher->setKey((unsigned char*)keyInput.c_str());
		//cout<<"Successfully set key." << endl;

		//perform encryption
		
		cout << "userinput inside AES ENC" << endl;
		cout << userinput << endl;
		unsigned char* ciphertext = cipher->encrypt((unsigned char*)userinput.c_str());
		string encOutput = (reinterpret_cast<char*>(ciphertext));
		appendLineToFile(outputFile, encOutput);
		}
		if(functype == "DEC")
		{
		//set decryption key
		cipher->setKey((unsigned char*)keyInput.c_str());

		//perform decryption
		const unsigned char* userinputTemp = reinterpret_cast<const unsigned char*>(userinput.c_str());
		unsigned char* plaintext;
		plaintext = cipher->decrypt(userinputTemp);
		cout << "plaintext in after DEC" << endl;
		cout << plaintext << endl;
		string decOutput = (reinterpret_cast<char*>(plaintext));
		appendLineToFile(outputFile, decOutput);
		}
	}
	else
	{
		cout << cipherName << " is not a valid type of cipher" << endl;
	}
	
}

static void appendLineToFile(string outputfile, string output)
{
    ofstream file;
    file.open(outputfile.c_str(), std::ios_base::app);
    //if (file.fail())
    //    throw std::ios_base::failure(strerror(errno));

    //make sure write fails with exception if something is wrong
    //file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

	cout << "output.length" << endl;
	cout << output.length() << endl;

		file << output;
		file.close();
	
}