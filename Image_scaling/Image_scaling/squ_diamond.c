void x2squ_dia(unsigned char *pImg, unsigned char *poImg, int rowsize, int colsize)
{

	int i, j;



	for (j = 0; j < colsize; j++) {
		for (i = 0; i < rowsize; i++) {
			//if ((i * 2 + (j * 2 * rowsize)) > 1024 * 511)
			//pause = 25;
			*(poImg + i * 2 + (j * 2 * rowsize) * 2) = *(pImg + i + j*rowsize);
		}
	}//2x img scaling


	colsize = 2 * colsize;
	rowsize = 2 * rowsize;

	for (i = 1; i < colsize - 2; i = i + 2) {
		for (j = 1; j < rowsize - 2; j = j + 2) {

			*(poImg + (i*rowsize) + j) = (*(poImg + ((i + 1)*rowsize) + j - 1) + *(poImg + ((i + 1)*rowsize) + j + 1) + *(poImg + ((i - 1)*rowsize) + j - 1) + *(poImg + ((i - 1)*rowsize) + j + 1)) >>2;


		}
	}
	

	for (i = 1; i < colsize - 2; i = i + 2) {
		for (j = 2; j < rowsize - 3; j = j + 2) {

			*(poImg + (i*rowsize) + j) = (*(poImg + ((i + 1)*rowsize) + j) + *(poImg + ((i)*rowsize) + j + 1) + *(poImg + ((i)*rowsize) + j - 1) + *(poImg + ((i - 1)*rowsize) + j)) >>2;


		}
	}

	for (i = 2; i < colsize - 3; i = i + 2) {
		for (j = 1; j < rowsize - 2; j = j + 2) {

			*(poImg + (i*rowsize) + j) = (*(poImg + ((i + 1)*rowsize) + j) + *(poImg + ((i)*rowsize) + j + 1) + *(poImg + ((i)*rowsize) + j - 1) + *(poImg + ((i - 1)*rowsize) + j)) >>2;


		}
	}
	
	return 0;

}