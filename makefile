all: keygen.c
	gcc keygen.c crypto/sha2.c -o keygen
