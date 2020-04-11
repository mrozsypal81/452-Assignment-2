echo "Encrypting!"
echo "./cipher AES 00112233445566778899aabbccddeeff ENC small.txt small.enc"

./cipher AES 00112233445566778899aabbccddeeff ENC small.txt small.enc
echo 
echo

echo "Decrypting"
echo "./cipher AES 00112233445566778899aabbccddeeff DEC small.enc small.dec"
./cipher AES 00112233445566778899aabbccddeeff DEC small.enc small.dec
