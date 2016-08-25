#include<msp430f5529.h>

#define FRAME 990

#define N 20

int h[N]={249, 328, 555, 908, 1348, 1829,2299, 2705, 3003,3161, 3161,

3003, 2705, 2299, 1829, 1348, 908, 555,328, 249 };

void ADC12();

void lowpass( int nIn[], int nOut[],int nLen, int h[]);

void main( )

{

	int i=0,j;

	WDTCTL = WDTPW | WDTHOLD;

	P3SEL |= BIT3+BIT4;

	UCA0CTL1 |= UCSWRST;

	UCA0CTL0|=UCMODE_0;

	UCA0CTL1 |= UCSSEL_2;

	UCA0BR0 = 104;

	UCA0BR1 = 0;

	UCA0MCTL = UCBRS0;

	UCA0CTL1 &= ~UCSWRST;

	ADC12();

}

void ADC12()

{

	int output[FRAME];

	int input[FRAME];

	int i,j,k;

	P6SEL |= 0x01;

	ADC12CTL0 &= ~ADC12ENC;

	ADC12CTL0 = ADC12SHT0_9+ ADC12ON+ADC12MSC;

	ADC12CTL1 =ADC12SHP+ADC12CONSEQ_2+ADC12DIV_7+ADC12SSEL_3;

	ADC12CTL2|=ADC12RES_1;

	ADC12MCTL0|=ADC12SREF_0+ADC12INCH_0;

	ADC12CTL0 |= ADC12ENC;

while(true)

{

	ADC12CTL0|=ADC12SC;

	for(i=0;i<FRAME;i++)

	{

		while( (ADC12IFG & ADC12BUSY)==0);

		input[i]=(ADC12MEM0>>1);

	}

	lowpass(input,output,N,h);

	for(j=0;j<FRAME;j++)

	{

		while (!(UCA0IFG & UCTXIFG));

		UCA0TXBUF=(output[j]>>3);

		for(k=0;k<=250;k++);

	}

	

}

void lowpass ( int nIn[], int nOut[], int nLen, int h[])//數位濾波程式

{

	long buff[FRAME+20];//儲存濾波數值陣列

	int icount,j;

	long sum;//總和

	for(icount=0;icount<FRAME;icount++)//儲存現在的待濾波數值

	{

		buff[icount+nLen-1]=nIn[icount];

	}

for(icount=0;icount<FRAME;icount++)//濾波處理

	{

		sum=0;//總和歸零

		for(j=0;j<nLen;j++)

	}

	sum+=( h[j]*buff[icount-1+nLen-j]);//濾波運算

}

nOut[icount]=sum>>15;//取最高位為輸出結果

}

for(icount=0;icount<nLen-1;icount++) //更新濾波數值暫存器

{

buff[nLen-icount-2]=nIn[FRAME-icount-1];

}

}