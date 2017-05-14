#include <math.h>

void x2dev_dis(unsigned char *pImg, unsigned char *poImg, int rowsize, int colsize)
{

	int i = 0;

	int pause;
	int mean;
	double dev0;
	double dev1;
	double dev2;
	double dev3;

	i = 0;
	int j = 0;

	for (j = 0; j < colsize; j++) {
		for (i = 0; i < rowsize; i++) {
			//if ((i * 2 + (j * 2 * rowsize)) > 1024 * 511)
			//pause = 25;
			*(poImg + i * 2 + (j * 2 * rowsize) * 2) = *(pImg + i + j*rowsize);
		}
	}//2x img scaling


	int a = 1;
	
	//row-wise interpolation
	for (j = 0; j < colsize * 2; j=j+2) {
		for (i = 3; i < rowsize * 2 - 4; i = i + 2) {
			
			mean = (*(poImg + (j*rowsize * 2) + i - 1) + *(poImg + (j*rowsize * 2) + i + 1) + *(poImg + (j*rowsize * 2) + i - 3) + *(poImg + (j*rowsize * 2) + i + 3))/4;
			dev0 = abs(mean - (*(poImg + (j*rowsize * 2) + i - 3)));
			dev1 = abs(mean - (*(poImg + (j*rowsize * 2) + i - 1)));
			dev2 = abs(mean - (*(poImg + (j*rowsize * 2) + i + 1)));
			dev3 = abs(mean - (*(poImg + (j*rowsize * 2) + i + 3)));

			//*(poImg + (j*rowsize * 2) + i) = ((1/(dev0+1))*(1/4)**(poImg + (j*rowsize * 2) + i - 3)) + ((1 / (dev1 + 1))*(3 / 4)**(poImg + (j*rowsize * 2) + i - 1)) + ((1 / (dev2 + 1))*(3 / 4)**(poImg + (j*rowsize * 2) + i + 1)) + ((1 / (dev3 + 1))*(1 / 4)**(poImg + (j*rowsize * 2) + i + 3));
			//*(poImg + (j*rowsize * 2) + i) = ((1 / (dev0 + 1))*(1)**(poImg + (j*rowsize * 2) + i - 3)) + ((1 / (dev1 + 1))*(1)**(poImg + (j*rowsize * 2) + i - 1)) + ((1 / (dev2 + 1))*(1)**(poImg + (j*rowsize * 2) + i + 1)) + ((1 / (dev3 + 1))*(1)**(poImg + (j*rowsize * 2) + i + 3));
			//*(poImg + (j*rowsize * 2) + i) = (((0.125)**(poImg + (j*rowsize * 2) + i - 3)) / (dev0 + 1)) + (((0.375)**(poImg + (j*rowsize * 2) + i - 1)) / (dev1 + 1)) + (((0.375)**(poImg + (j*rowsize * 2) + i + 1)) / (dev2 + 1)) + (((0.125)**(poImg + (j*rowsize * 2) + i + 3)) / (dev3 + 1));
			*(poImg + (j*rowsize * 2) + i) = ((((1)**(poImg + (j*rowsize * 2) + i - 3)) / (dev0 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i - 1)) / (dev1 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i + 1)) / (dev2 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i + 3)) / (dev3 + 1)))/4;


			if (((((1)**(poImg + (j*rowsize * 2) + i - 3)) / (dev0 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i - 1)) / (dev1 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i + 1)) / (dev2 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i + 3)) / (dev3 + 1))) > 255)
				*(poImg + (j*rowsize * 2) + i) = 255;
			else if (((((1)**(poImg + (j*rowsize * 2) + i - 3)) / (dev0 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i - 1)) / (dev1 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i + 1)) / (dev2 + 1)) + (((1)**(poImg + (j*rowsize * 2) + i + 3)) / (dev3 + 1))) < 0)
				*(poImg + (j*rowsize * 2) + i) = 0;
			//else if (*(poImg + (j*rowsize * 2) + i) < 10)
			//a = 1;
			//else if()
		}
	}

	
	//column-wise interpolation
	for (j = 0; j < rowsize * 2; j++) {
		for (i = 3; i < colsize * 2 - 4; i = i = i + 2) {

			mean = (*(poImg + j + (i - 1)*rowsize * 2) + *(poImg + j + (i + 1)*rowsize * 2) + *(poImg + j + (i - 3)*rowsize * 2) + *(poImg + j + (i + 3)*rowsize * 2)) / 4;
			dev0 = abs(mean - (*(poImg + j + (i - 3)*rowsize * 2)));
			dev1 = abs(mean - (*(poImg + j + (i - 1)*rowsize * 2)));
			dev2 = abs(mean - (*(poImg + j + (i + 1)*rowsize * 2)));
			dev3 = abs(mean - (*(poImg + j + (i + 3)*rowsize * 2)));

			//*(poImg + (i*rowsize * 2) + j) = ((1/(dev0+1))*(*(poImg + ((i-3)*rowsize * 2) + j))*(1/8)) + ((1 / (dev1 + 1))*(*(poImg + ((i-1)*rowsize * 2) + j))*(3 / 8)) +((1 / (dev2 + 1))*(*(poImg + ((i+1)*rowsize * 2) + j))*(3 / 8)) + ((1 / (dev3 + 1))*(*(poImg + ((i+3)*rowsize * 2) + j))*(3 / 8));
			//*(poImg + (i*rowsize * 2) + j) = (((*(poImg + ((i - 3)*rowsize * 2) + j))*(0.125)) / (dev0 + 1)) + (((*(poImg + ((i - 1)*rowsize * 2) + j))*(0.375)) / (dev1 + 1)) + (((*(poImg + ((i + 1)*rowsize * 2) + j))*(0.375)) / (dev2 + 1)) + (((*(poImg + ((i + 3)*rowsize * 2) + j))*(0.125)) / (dev3 + 1));
			*(poImg + (i*rowsize * 2) + j) = ((((*(poImg + ((i - 3)*rowsize * 2) + j))*(1)) / (dev0 + 1)) + (((*(poImg + ((i - 1)*rowsize * 2) + j))*(1)) / (dev1 + 1)) + (((*(poImg + ((i + 1)*rowsize * 2) + j))*(1)) / (dev2 + 1)) + (((*(poImg + ((i + 3)*rowsize * 2) + j))*(1)) / (dev3 + 1)))/4;

			if (((((*(poImg + ((i - 3)*rowsize * 2) + j))*(1)) / (dev0 + 1)) + (((*(poImg + ((i - 1)*rowsize * 2) + j))*(1)) / (dev1 + 1)) + (((*(poImg + ((i + 1)*rowsize * 2) + j))*(1)) / (dev2 + 1)) + (((*(poImg + ((i + 3)*rowsize * 2) + j))*(1)) / (dev3 + 1))) > 255)
				*(poImg + (i*rowsize * 2) + j) = 255;
			else if (((((*(poImg + ((i - 3)*rowsize * 2) + j))*(1)) / (dev0 + 1)) + (((*(poImg + ((i - 1)*rowsize * 2) + j))*(1)) / (dev1 + 1)) + (((*(poImg + ((i + 1)*rowsize * 2) + j))*(1)) / (dev2 + 1)) + (((*(poImg + ((i + 3)*rowsize * 2) + j))*(1)) / (dev3 + 1))) < 0)
				*(poImg + (i*rowsize * 2) + j) = 0;
		}
	}
	
	
	return 0;






}