#!/bin/sh
rm example/encrypted.txt
rm example/decrypted.txt
rm example/input.txt
cat example/original.txt > example/input.txt
./acipher encode example/input.txt example/encrypted.txt
./acipher decode example/encrypted.txt example/decrypted.txt
diff example/input.txt example/decrypted.txt
