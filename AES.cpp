#include<iostream>
#include<openssl/aes.h>
#include "AES.h"

using namespace std;
unsigned char twoCharToHexByte(const unsigned char* twoChars);
unsigned char charToHex(const char& character);
/**
 * Sets the key to use
 * @param key - the first byte of this represents whetherm
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	
	// TODO: AES implementation of openssl cares about whether
	// you are encrypting or decrypting when setting the key.
	// That is, when encrypting you use function AES_set_encrypt_key(...)
	// and when decrypting AES_set_decrypt_key(...).
	//
	// One way to solve this problem is to pass in a 17 byte key, where
	// the first byte is used to indicate whether we are encrypting or
	// decrypting. E.g., if the first byte is 0, then use AES_set_encrypt_key(...).
	// Otherwise, use AES_set_decrypt_key(...).  The rest of the bytes in the
	// array indicate the 16 bytes of the 128-bit AES key.
	//
	// Both functions return 0 on success and other values on faliure.
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h
	// and aes.cpp example provided with the assignment.
	
	/* The key index */
	int keyIndex = 0;
	
	/* The AES key index */
	int AESKeyIndex = 0;

	// The exit code
	bool retVal = true;


	// This is to account for the encryption 00 that is added before in cipher.cpp
	int s = strlen((char*)keyArray);
	//cout << "array length" << endl;
	//cout << s << endl;
	
	// Get the flag for encryption and decryption
	char type = keyArray[0];
	
	// Iterate the key starting from the first element skipping
	// two bytes at time
	for(int keyIndex = 1; keyIndex < 32; keyIndex += 2)
	{
		// Convert the two bytes into one byte
		this->AES_key[AESKeyIndex] = twoCharToHexByte(keyArray + keyIndex);
		
		++AESKeyIndex;
	}
	

	//cout << "This->AES_key" << endl;
	//cout << keyArray << endl;
	
	// Set the key for encryption
	if(type == '0')
	{	
		fprintf(stderr, "Setting encryption key!\n");
		//cout << "setting Encryption key" << endl;
		if(AES_set_encrypt_key(this->AES_key, 128, &this->enc_key)!=0)
		{
			cout << "Fail to set Encryption key";
			retVal = false;
		}
	}
	else
	{
		fprintf(stderr, "Setting decryption key!\n");
		//cout << "setting decryption key" << endl;
		
		if(AES_set_decrypt_key(this->AES_key, 128, &this->dec_key) != 0)
		{
			cout << "Fail to set Decryption key";
			retVal = false;
		}
	}
	
	return retVal;
	
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	
	//TODO: 1. Dynamically allocate a block to store the ciphertext.

		unsigned char* ciphertext = new unsigned char[16];
		memset(ciphertext,0,16);
		

	//	2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
		//cout <<"Begin encryption" << endl;
		AES_ecb_encrypt(plainText, ciphertext, &this->enc_key, AES_ENCRYPT);
		//cout <<"Successful encryption" << endl;
		

	// 	3. Return the pointer to the ciphertext
		
	return ciphertext;	
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	
	//TODO: 1. Dynamically allocate a block to store the plaintext.

		unsigned char* plaintext = new unsigned char[16];
		memset(plaintext,0,16);
		

	//	2. Use AES_ecb_encrypt(...) to decrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
		//cout <<"Begin decryption" << endl;
		AES_ecb_encrypt(cipherText, plaintext, &this->dec_key, AES_DECRYPT);
		//cout <<"Successful decryption" << endl;
	// 	3. Return the pointer to the plaintext
	//cout << "plaintext" << endl;
	//cout << plaintext << endl;
	return plaintext;
}


/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */	
	if(character >= '0' && character <= '9'){	
		/* Convert the character to hex */
		//cout << "convert the char to hex" << endl;
		return character - '0';
	}
	/* It the first digit a letter 'a' - 'f'? */
	else if(character >= 'a' && character <= 'f'){
		/* Conver the cgaracter to hex */
		//cout << "convert the cgaracter to hex" << endl;
		return (character - 97) + 10;
	}
			
	/* Invalid character */
	
	else {
		//cout << "invalid char" << endl;
		return 'z';
	}
}

/**
 * Converts two characters into a hex integers
 * and then inserts the integers into the higher
 * and lower bits of the byte
 * @param twoChars - two charcters representing the
 * the hexidecimal nibbles of the byte.
 * @param twoChars - the two characters
 * @return - the byte containing having the
 * valud of two characters e.g. string "ab"
 * becomes hexidecimal integer 0xab.
 */
unsigned char twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;
	
	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if((singleByte = charToHex(twoChars[0])) == 'z') 
	{
		/* Invalid digit */
		//cout << "invalid digit" << endl;
		return 'z';
	}
	
	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);
	
	/* Conver the second character */
	if((secondChar = charToHex(twoChars[1])) == 'z'){
		//cout << "convert second char" << endl;
		return 'z'; 
	}
	/* Insert the second value into the lower nibble */	
	singleByte |= secondChar;
	//cout << "returning the hex byte" << endl;
	return singleByte;
}
