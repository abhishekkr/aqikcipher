
## a Qik Cipher

### Description:

a Quick Cipher is my attempt at creating a dumb One-Time-Pad that tries using a small shared password; good enough to mask, not to make it unhackable


### How-To Use:

* build it `mkdir out; gcc -o out/aqikcipher aQikCipher.c` or `./build.sh`

* Encrypt: `./out/aqikcipher encode password original.file encrypted.file`

* Decrypt: `./out/aqikcipher decode password decrypted.file decrypted.file`

* Can checkout example run at `./run_example.sh`

---
