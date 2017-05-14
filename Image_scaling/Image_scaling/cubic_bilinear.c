#define vs 0.5
#define vs1 0.3
#define vs2 0.6


void x2adap_bic_bilin(unsigned char *pImg, unsigned char *poImg, int rowsize, int colsize)
{

	int i = 0;
	int j = 0;
	/*
	unsigned char vc0;
	unsigned char vc1;
	unsigned char vc2;
	unsigned char vc3;
	*/

	float vc0;
	float vc1;
	float vc2;
	float vc3;



	for (j = 0; j < colsize; j++) {
		for (i = 0; i < rowsize; i++) {
			//if ((i * 2 + (j * 2 * rowsize)) > 1024 * 511)
			//pause = 25;
			*(poImg + i * 2 + (j * 2 * rowsize) * 2) = *(pImg + i + j*rowsize);
		}
	}//2x img scaling

	vc0 = 4 - 8 * (1 + vs) + 5 * (1 + vs)*(1 + vs) - (1 + vs)*(1 + vs)*(1 + vs);
	vc1 = 1 - 2 * vs*vs + vs*vs*vs;
	vc2 = 1 - 2 * (1 - vs)*(1 - vs) + (1 - vs)*(1 - vs)*(1 - vs);
	vc3 = 4 - 8 * (2 - vs) + 5 * (2 - vs)*(2 - vs) - (2 - vs)*(2 - vs)*(2 - vs);


	//row-wise interpolation
	for (j = 0; j < colsize * 2; j++) {
		for (i = 3; i < rowsize * 2 - 4; i = i + 2) {
			*(poImg + (j*rowsize * 2) + i) = vc0**(poImg + (j*rowsize * 2) + i - 3) + vc1**(poImg + (j*rowsize * 2) + i - 1) + vc2**(poImg + (j*rowsize * 2) + i + 1) + vc3**(poImg + (j*rowsize * 2) + i + 3);
			if (((*(poImg + (j*rowsize * 2) + i - 1)) > (*(poImg + (j*rowsize * 2) + i)) && ((*(poImg + (j*rowsize * 2) + i + 1)) > (*(poImg + (j*rowsize * 2) + i)))) || ((*(poImg + (j*rowsize * 2) + i - 1)) < (*(poImg + (j*rowsize * 2) + i)) && ((*(poImg + (j*rowsize * 2) + i + 1)) < (*(poImg + (j*rowsize * 2) + i)))))
				*(poImg + (j*rowsize * 2) + i) = ((*(poImg + (j*rowsize * 2) + i + 1)) + *(poImg + (j*rowsize * 2) + i - 1)) / 2;
			
		}
	}

	
	//column-wise interpolation
	for (j = 0; j < rowsize * 2; j++) {
		for (i = 3; i < colsize * 2 - 4; i = i = i + 2) {
			*(poImg + (i*rowsize * 2) + j) = vc0**(poImg + j + (i - 3)*rowsize * 2) + vc1**(poImg + j + (i - 1)*rowsize * 2) + vc2**(poImg + j + (i + 1)*rowsize * 2) + vc3**(poImg + j + (i + 3)*rowsize * 2);
			if ((((*(poImg + j + (i - 1)*rowsize * 2))>(*(poImg + (i*rowsize * 2) + j)))&&((*(poImg + j + (i + 1)*rowsize * 2))>(*(poImg + (i*rowsize * 2) + j))))||(((*(poImg + j + (i - 1)*rowsize * 2))<(*(poImg + (i*rowsize * 2) + j)))&&((*(poImg + j + (i + 1)*rowsize * 2))<(*(poImg + (i*rowsize * 2) + j)))))
				*(poImg + (i*rowsize * 2) + j) =((*(poImg + j + (i - 1)*rowsize * 2))+(*(poImg + j + (i + 1)*rowsize * 2))) / 2;
			
		
		}
	}
	
















	return 0;

}