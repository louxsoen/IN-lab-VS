#include <stdio.h>
#include "seed.h"

int main() {
    u32 KL1 = 0xC119F584;
    u32 KR1 = 0x5AE033A0;
    u32 KL2 = 0x62947390;
    u32 KR2 = 0xA600AD14;
    u32 A, B, C, D, Z0, Z1, Z2, Z3, Y0, Y1, Y2, Y3;
    u32 TEMP;

    Z0 = (u8)(KL1);
    Z1 = (u8)(KL1 >>  8);
    Z2 = (u8)(KL1 >> 16);
    Z3 = (u8)(KL1 >> 24);

    Y0 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0xC0) ^ ((Z0 ^ Z1 ^ Z3) & 0x30) ^ ((Z0 ^ Z2 ^ Z3) & 0x0C) ^ ((Z1 ^ Z2 ^ Z3) & 0x03)];
    Y1 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x03) ^ ((Z0 ^ Z1 ^ Z3) & 0xC0) ^ ((Z0 ^ Z2 ^ Z3) & 0x30) ^ ((Z1 ^ Z2 ^ Z3) & 0x0C)];
    Y2 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0x0C) ^ ((Z0 ^ Z1 ^ Z3) & 0x03) ^ ((Z0 ^ Z2 ^ Z3) & 0xC0) ^ ((Z1 ^ Z2 ^ Z3) & 0x30)];
    Y3 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x30) ^ ((Z0 ^ Z1 ^ Z3) & 0x0C) ^ ((Z0 ^ Z2 ^ Z3) & 0x03) ^ ((Z1 ^ Z2 ^ Z3) & 0xC0)];
    
    KL1 = (Y3 << 24) ^ (Y2 << 16) ^ (Y1 << 8) ^ (u8)Y0;

    Z0 = (u8)(KR1);
    Z1 = (u8)(KR1 >>  8);
    Z2 = (u8)(KR1 >> 16);
    Z3 = (u8)(KR1 >> 24);

    Y0 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0xC0) ^ ((Z0 ^ Z1 ^ Z3) & 0x30) ^ ((Z0 ^ Z2 ^ Z3) & 0x0C) ^ ((Z1 ^ Z2 ^ Z3) & 0x03)];
    Y1 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x03) ^ ((Z0 ^ Z1 ^ Z3) & 0xC0) ^ ((Z0 ^ Z2 ^ Z3) & 0x30) ^ ((Z1 ^ Z2 ^ Z3) & 0x0C)];
    Y2 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0x0C) ^ ((Z0 ^ Z1 ^ Z3) & 0x03) ^ ((Z0 ^ Z2 ^ Z3) & 0xC0) ^ ((Z1 ^ Z2 ^ Z3) & 0x30)];
    Y3 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x30) ^ ((Z0 ^ Z1 ^ Z3) & 0x0C) ^ ((Z0 ^ Z2 ^ Z3) & 0x03) ^ ((Z1 ^ Z2 ^ Z3) & 0xC0)];
    
    KR1 = (Y3 << 24) ^ (Y2 << 16) ^ (Y1 << 8) ^ (u8)Y0;  
    KL1 += KC[0];
    KR1 -= KC[0];

// =================================================================== // 2 ROUND

    Z0 = (u8)(KL2);
    Z1 = (u8)(KL2 >>  8);
    Z2 = (u8)(KL2 >> 16);
    Z3 = (u8)(KL2 >> 24);

    Y0 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0xC0) ^ ((Z0 ^ Z1 ^ Z3) & 0x30) ^ ((Z0 ^ Z2 ^ Z3) & 0x0C) ^ ((Z1 ^ Z2 ^ Z3) & 0x03)];
    Y1 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x03) ^ ((Z0 ^ Z1 ^ Z3) & 0xC0) ^ ((Z0 ^ Z2 ^ Z3) & 0x30) ^ ((Z1 ^ Z2 ^ Z3) & 0x0C)];
    Y2 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0x0C) ^ ((Z0 ^ Z1 ^ Z3) & 0x03) ^ ((Z0 ^ Z2 ^ Z3) & 0xC0) ^ ((Z1 ^ Z2 ^ Z3) & 0x30)];
    Y3 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x30) ^ ((Z0 ^ Z1 ^ Z3) & 0x0C) ^ ((Z0 ^ Z2 ^ Z3) & 0x03) ^ ((Z1 ^ Z2 ^ Z3) & 0xC0)];
    
    KL2 = (Y3 << 24) ^ (Y2 << 16) ^ (Y1 << 8) ^ (u8)Y0; 

    Z0 = (u8)(KR2);
    Z1 = (u8)(KR2 >>  8);
    Z2 = (u8)(KR2 >> 16);
    Z3 = (u8)(KR2 >> 24);

    Y0 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0xC0) ^ ((Z0 ^ Z1 ^ Z3) & 0x30) ^ ((Z0 ^ Z2 ^ Z3) & 0x0C) ^ ((Z1 ^ Z2 ^ Z3) & 0x03)];
    Y1 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x03) ^ ((Z0 ^ Z1 ^ Z3) & 0xC0) ^ ((Z0 ^ Z2 ^ Z3) & 0x30) ^ ((Z1 ^ Z2 ^ Z3) & 0x0C)];
    Y2 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0x0C) ^ ((Z0 ^ Z1 ^ Z3) & 0x03) ^ ((Z0 ^ Z2 ^ Z3) & 0xC0) ^ ((Z1 ^ Z2 ^ Z3) & 0x30)];
    Y3 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x30) ^ ((Z0 ^ Z1 ^ Z3) & 0x0C) ^ ((Z0 ^ Z2 ^ Z3) & 0x03) ^ ((Z1 ^ Z2 ^ Z3) & 0xC0)];
    
    KR2 = (Y3 << 24) ^ (Y2 << 16) ^ (Y1 << 8) ^ (u8)Y0;  
    
    KL2 += KC[1];
    KR2 -= KC[1];

    printf("A + C : %08X, B + D : %08X\n", KL1, KR1);
    //printf("A BLOCK : %08X, C BLOCK : %08X\nB BLOCK : %08X, D BLOCK : %08X\n", KL1, KR1, KL2, KR2);
}

/* Origin G_BOX
    Z3 = (S[0][(u8)(KL)] & m3) ^ (S[1][(u8)(KL >> 8)] & m0) ^ (S[0][(u8)(KL >> 16)] & m1) ^ (S[1][(u8)(KL >> 24)] & m2);
    Z2 = (S[0][(u8)(KL)] & m2) ^ (S[1][(u8)(KL >> 8)] & m3) ^ (S[0][(u8)(KL >> 16)] & m0) ^ (S[1][(u8)(KL >> 24)] & m1);
    Z1 = (S[0][(u8)(KL)] & m1) ^ (S[1][(u8)(KL >> 8)] & m2) ^ (S[0][(u8)(KL >> 16)] & m3) ^ (S[1][(u8)(KL >> 24)] & m0);
    Z0 = (S[0][(u8)(KL)] & m0) ^ (S[1][(u8)(KL >> 8)] & m1) ^ (S[0][(u8)(KL >> 16)] & m2) ^ (S[1][(u8)(KL >> 24)] & m3);

    Y0 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0xC0) ^ ((Z0 ^ Z1 ^ Z3) & 0x30) ^ ((Z0 ^ Z2 ^ Z3) & 0x0C) ^ ((Z1 ^ Z2 ^ Z3) & 0x03)];
    Y1 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x03) ^ ((Z0 ^ Z1 ^ Z3) & 0xC0) ^ ((Z0 ^ Z2 ^ Z3) & 0x30) ^ ((Z1 ^ Z2 ^ Z3) & 0x0C)];
    Y2 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0x0C) ^ ((Z0 ^ Z1 ^ Z3) & 0x03) ^ ((Z0 ^ Z2 ^ Z3) & 0xC0) ^ ((Z1 ^ Z2 ^ Z3) & 0x30)];
    Y3 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x30) ^ ((Z0 ^ Z1 ^ Z3) & 0x0C) ^ ((Z0 ^ Z2 ^ Z3) & 0x03) ^ ((Z1 ^ Z2 ^ Z3) & 0xC0)];
    
    KL = (Y3 << 24) ^ (Y2 << 16) ^ (Y1 << 8) ^ (u8)Y0;

    Z3 = (S[0][(u8)(KR)] & m3) ^ (S[1][(u8)(KR >> 8)] & m0) ^ (S[0][(u8)(KR >> 16)] & m1) ^ (S[1][(u8)(KR >> 24)] & m2);
    Z2 = (S[0][(u8)(KR)] & m2) ^ (S[1][(u8)(KR >> 8)] & m3) ^ (S[0][(u8)(KR >> 16)] & m0) ^ (S[1][(u8)(KR >> 24)] & m1);
    Z1 = (S[0][(u8)(KR)] & m1) ^ (S[1][(u8)(KR >> 8)] & m2) ^ (S[0][(u8)(KR >> 16)] & m3) ^ (S[1][(u8)(KR >> 24)] & m0);
    Z0 = (S[0][(u8)(KR)] & m0) ^ (S[1][(u8)(KR >> 8)] & m1) ^ (S[0][(u8)(KR >> 16)] & m2) ^ (S[1][(u8)(KR >> 24)] & m3);
   
    Y0 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0xC0) ^ ((Z0 ^ Z1 ^ Z3) & 0x30) ^ ((Z0 ^ Z2 ^ Z3) & 0x0C) ^ ((Z1 ^ Z2 ^ Z3) & 0x03)];
    Y1 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x03) ^ ((Z0 ^ Z1 ^ Z3) & 0xC0) ^ ((Z0 ^ Z2 ^ Z3) & 0x30) ^ ((Z1 ^ Z2 ^ Z3) & 0x0C)];
    Y2 = INVS[0][((Z0 ^ Z1 ^ Z2) & 0x0C) ^ ((Z0 ^ Z1 ^ Z3) & 0x03) ^ ((Z0 ^ Z2 ^ Z3) & 0xC0) ^ ((Z1 ^ Z2 ^ Z3) & 0x30)];
    Y3 = INVS[1][((Z0 ^ Z1 ^ Z2) & 0x30) ^ ((Z0 ^ Z1 ^ Z3) & 0x0C) ^ ((Z0 ^ Z2 ^ Z3) & 0x03) ^ ((Z1 ^ Z2 ^ Z3) & 0xC0)];
*/