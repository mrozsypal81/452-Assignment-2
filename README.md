# 452-Assignment-2
A form of implementation of DES and AES

Members:

Jin Nguyen, jwin@csu.fullerton.edu
Michael Rozsypal, mrozsypal@csu.fullerton.edu

Language used:
C++

How to run:

first use the make file
then either

./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>
Each parameter is defined as follows:
• CIPHER NAME: The name of the cipher:
– DES: indicates the DES cipher
– AES: indicates the AES cipher
• KEY: the encryption key to use (must be 16 characters representing a 64-bit hexadecimal
number for DES and 128-bit number for AES)
• ENC/DEC: whether to encrypt or decrypt, respectively
• INPUT FILE: the file from which to read the input
• OUTPUT FILE: the file to which to write the output

examples
./cipher DES "0123456789abcdef" ENC in.txt out.txt

./cipher AES "00112233445566778899aabbccddeeff" ENC in.txt out.txt

Extra Credit implemented:
No

Special Features:
None
