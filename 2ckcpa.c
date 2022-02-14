#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <time.h>

#define DIR "C:\\Users\\부채널분석1\\Desktop\\Masking Trace\\"   
#define traceFN "trace.bin"  
#define AlignedTraceFN "trace.bin"
#define ptFN "plaintext.npy"
typedef unsigned char u8;

#define startpoint 0
#define endpoint 24000 

static u8 AES_Sbox[256] = {
   0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
   0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
   0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
   0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
   0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
   0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
   0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
   0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
   0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
   0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
   0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
   0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
   0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
   0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
   0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
   0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

#define TraceNum 2000
#define TraceLength 24000

void secondorderCPA() {
    float		**data		= NULL;
	u8			**PT 		= NULL;
	u8			iv, hw_iv; 
	u8			MK[16];	 
	double  	*Sx; 			// 전력
	double		Sy;	  			// 해밍웨이트
	double		*Sxx;
	double		Syy;
	double		*Sxy;
	double	 	*corr;	
	double		maxCorr; 
	double		a, b, c;
	int			key;
	int			maxkey;
	int			x, y;
	int			i, j, k;
	char		buf[256];
	double		cur, all;
	FILE		*rfp, * wfp;
//==============================================================//
//					Measured Power Allocation					//
//==============================================================//
	sprintf(buf, "%s%s", DIR, traceFN);
	rfp = fopen(buf, "rb"); 
	if (rfp == NULL) printf("%s 파일 읽기 오류", traceFN);

	data = (float**)calloc(TraceNum, sizeof(float*));
	for (i = 0 ; i < TraceNum; i++)	
		data[i] = (float*)calloc(TraceLength, sizeof(float));
	
	for (i = 0; i < TraceNum; i++)
		fread(data[i], sizeof(float), TraceLength, rfp);
	
	fclose(rfp);
//==============================================================//
//					   Plaintext Allocation				    	//
//==============================================================//
	sprintf(buf, "%s%s", DIR, ptFN);
	rfp = fopen(buf, "rb");
	if (rfp == NULL) printf("%s 파일 읽기 오류", ptFN);

	PT = (u8**)calloc(TraceNum, sizeof(u8*));
	for (i = 0; i < TraceNum; i++)
		PT[i] = (u8*)calloc(16, sizeof(u8));
	
	for (i = 0; i < TraceNum; i++)	fread(PT[i], sizeof(char), 16, rfp);

//==============================================================// 
//	          			create new trace		  		        //
//==============================================================//
    unsigned int m = 0;
    unsigned int Start_Msub = 19700;
    unsigned int End_Msub = 19900;
    unsigned int Start_MSbox = 5200;
    unsigned int End_MSbox = 5400;
    unsigned int len1 = (End_MSbox - Start_MSbox) * (End_Msub - Start_Msub);
    Cut1 = (double**)calloc(TraceNum, sizeof(double*));
    for (i = 0; i < TraceNum; i++) {
        Cut1[i] = (double*)calloc(len1, sizeof(double));
    }
    double* plus = (double*)calloc(TraceLength, sizeof(double));
    double* Mean = (double*)calloc(TraceLength, sizeof(double));
    for (int i = 0; i < TraceNum; i++) {
        for (int j = 0; j < TraceLength; j++) {
            plus[j] += data[i][j];
        }
    }

    for (int i = 0; i < TraceLength; i++) {
        Mean[i] = (double)(plus[i] / 5000);
    }

    for (i = 0; i < TraceNum; i++) {
        m = 0;
        for (j = Start_Msub; j < End_Msub; j++) {
            for (k = Start_MSbox; k < End_MSbox; k++) {
                Cut1[i][m + (k - Start_MSbox)] = (data[i][k] - Mean[k]) * (data[i][j] - Mean[j]);
            }
            m += End_MSbox - Start_MSbox;
        }
    }

    Sx = (double*)calloc(len1, sizeof(double));
    Sxx = (double*)calloc(len1, sizeof(double));
    Sxy = (double*)calloc(len1, sizeof(double));
    corrT = (double*)calloc(len1, sizeof(double));
    for (i = 0; i < len1; i++) {
        for (j = 0; j < TraceNum; j++) {
            Sx[i] += Cut1[j][i];
            Sxx[i] += Cut1[j][i] * Cut1[j][i];
        }
    }
    Sy = 0;
    Syy = 0;
    max = 0;
    memset(Sxy, 0, sizeof(double) * len1);
    for (key = 0; key < 256; key++) {
        Sy = 0;
        Syy = 0;
        memset(Sxy, 0, sizeof(double) * len1);
        for (j = 0; j < TraceNum; j++) {
            iv = AES_Sbox[PT[j][0] ^ key];
            hw_iv = 0;

            for (k = 0; k < 8; k++) {
                hw_iv += ((iv >> k) & 1);
            }

            Sy += hw_iv;
            Syy += hw_iv * hw_iv;

            for (k = 0 /*0*/; k < len1 /*TraceLength*/; k++) {
                Sxy[k] += hw_iv * Cut1[j][k];
            }
        }
        for (k = 0; k < len1; k++) {
            corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));

            if (fabs(corrT[k]) > max) {
                maxkey = key;
                max = fabs(corrT[k]);
            }
        }
        sprintf_s(buf, 256 * sizeof(char), "%scorrtrace3\\block_%02x.corrtrace", DIR, key);
        if ((err = fopen_s(&wfp, buf, "wb"))) {
            printf("File Open Error5!!\n");
        }
        fwrite(corrT, sizeof(double), len1, wfp);
        fclose(wfp);
        printf("Now key (0x%02x) , corr (%lf) : %02dth_block: maxkey(%02x), maxcorr(%lf)\n", key, corrT[0], i, maxkey, max);
    }
    free(Sx);
    free(Sxx);
    free(Sxy);
    free(corrT);
    free(data);
    free(PT);
}

int main() {
    secondorderCPA();
    //CPA();
}