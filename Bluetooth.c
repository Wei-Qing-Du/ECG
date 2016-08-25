#include<msp430f5529.h>

#define FRAME 990 //數值長度

#define N 20 //濾波器階數

inth[N]={

//濾波器的係數,截止頻率為38Hz

249, 328, 555, 908, 1348, 1829,2299, 2705, 3003,

3161, 3161, 3003, 2705, 2299, 1829, 1348, 908, 555,

328, 249

};

int output[FRAME];//數位濾波暫存陣列

for(j=0;j<FRAME;j++)//傳輸陣列迴圈

{

	while (!(UCA0IFG & UCTXIFG));//等待上個傳送完成

	UCA0TXBUF=(output[j]>>3);//移位使得值可以在1Byte內傳送

	for(k=0;k<=250;k++);//延遲250usec

}