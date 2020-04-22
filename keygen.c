#include <stdio.h>
#include <string.h>
#include "crypto/sha2.h"

int main()

{
    char sha2_hash[256];
    char req_num[19];
    char valid_serial[40];
    char formatted_serial[40];
    char _s[40];
    int _n;
    int iVar4;
    unsigned int uVar5;
    char cVar1;
    int xor_value;
    int extraout_r1;
    
    printf("Keygenerator for Biyak dictionary\n");
	while (strlen(req_num) < 1) {
		printf("Device ID Key (At least 1 character, no spaces): ");
		scanf("%s", req_num);
	}


    memset(sha2_hash,0,0x100);
	memset(_s,0,0x40);
	memset(valid_serial,0,0x40);
	memset(formatted_serial,0,0x40);
	xor_value = 8;
	_n = strlen(req_num);  
	memcpy(_s, req_num, _n);
	iVar4 = sha2(sha2_hash, 0x100, _s, 0x40);
	if (iVar4 == 0) {
		iVar4 = 0;
		do {
			while( 1 ) {
				//__aeabi_idivmod((int)(char)(sha2_hash[iVar4] ^ (byte)xor_value),10);
				extraout_r1 = (int)(char)(sha2_hash[iVar4] ^ xor_value) % 10; 
				uVar5 = extraout_r1 >> 0x1f;
				uVar5 = (extraout_r1 + uVar5) ^ uVar5;
				cVar1 = (char)uVar5;
				if ((int)uVar5 < 10) break;
				//*(char *)((int)&local_40 + iVar4) = cVar1 + '7';
				valid_serial[iVar4] = cVar1 + '7';
				iVar4 = iVar4 + 1;
				if (iVar4 == 0x10) goto LAB_00017dde;
			}
		// *(char *)((int)&local_40 + iVar4) = cVar1 + '0';
		valid_serial[iVar4] = cVar1 + '0';
		iVar4 = iVar4 + 1;
		} while (iVar4 != 0x10);
	LAB_00017dde:
	iVar4 = 0;
	for (int i=0; i<0x10; i++) {
		if ((i > 0) & (i % 4 == 0)) {
			formatted_serial[i+iVar4] = '-';
			iVar4++;
		}
		formatted_serial[i+iVar4] = valid_serial[i];
	}
	printf("%s\n", formatted_serial);
	return 0;
	}
}
