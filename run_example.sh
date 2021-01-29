#!/bin/sh

set -ex

./build.sh

[[ ! -d "./example" ]] && mkdir -p ./example
[[ -f "./example/encrypted.txt" ]] && rm ./example/encrypted.txt
[[ -f "./example/decrypted.txt" ]] && rm ./example/decrypted.txt

if [[ ! -f "./example/input.txt" ]]; then
  cat <<EOF > example/input.txt
Courtesy: Wikipedia.org
Link: http://en.wikipedia.org/wiki/Cryptography

========================================================================
Cryptography
From Wikipedia, the free encyclopedia
  
"Secret code" redirects here. For the Aya Kamiki album, see Secret Code.

German Lorenz cipher machine, used in World War II to encrypt very-high-level general staff messages
Cryptography (or cryptology; from Greek κρυπτός, kryptos, "hidden, secret"; 
and γράφειν, gráphin, "writing", or -λογία, -logia, "study", respectively)[1]
is the practice and study of hiding information. 

Modern cryptography intersects the disciplines of mathematics, computer science,
and electrical engineering. Applications of cryptography include ATM cards, 
computer passwords, and electronic commerce.
========================================================================
EOF
fi

./out/aqikcipher encode safeword example/input.txt example/encrypted.txt

./out/aqikcipher -v decode safeword example/encrypted.txt example/decrypted.txt

diff example/input.txt example/decrypted.txt
