#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
//Page 0
#define RFU00     0x00
#define     CommandReg 0x01
#define     ComIEnReg             0x02
#define     DivlEnReg             0x03
#define     ComIrqReg             0x04
#define     DivIrqReg             0x05
#define     ErrorReg              0x06
#define     Status1Reg            0x07
#define     Status2Reg            0x08
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F

//Page 1
#define RFU10      0x10
#define ModeReg 0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F

//Page 2
#define     RFU20                 0x20
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F

//RC522 Command
#define PCD_IDLE        0x00
#define PCD_AUTHENT     0x0E
#define PCD_RECEIVE     0x08
#define PCD_TRANSMIT    0x04
#define PCD_TRANSCEIVE  0x0C
#define PCD_RESETPHASE  0x0F    //soft reset
#define PCD_CALCRC       0x03

//Card Command
#define PICC_REQIDL           0x26
#define PICC_REQALL           0x52 
#define PICC_ANTICOLL1        0x93
#define PICC_ANTICOLL2        0x95 

#define RC522REST 3  //reset pin

#define 	MI_OK                 0
#define 	MI_NOTAGERR           (-1)
#define 	MI_ERR                (-2)

#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte
#define MAXRLEN  18

#define uchar unsigned char
unsigned char cmdReg[2] = {0x01,0x2C};

uchar readRc522Reg(uchar cmd){
    //printf("Read from rc522.");
    uchar cmds[2] = {0x00,0xFF};
    cmds[0] = ((cmd<<1)&0x7E)|0x80;
    //printf("Address:0x%02x.\r\n",cmds[0]);
    wiringPiSPIDataRW(0,cmds,2);
    return cmds[1];
}

void writeRc522Reg(uchar cmd,uchar value){
    //printf("Write to RC522.");
    uchar cmds[2]= {0x00,0x00};
    cmds[0] = (cmd<<1)&0x7E;
    cmds[1] = value;
    //printf("Address:0x%02x.\r\n",cmds[0]);
    wiringPiSPIDataRW(0,cmds,2);
}

void ClearBitMask(uchar reg,uchar mask){
    uchar tmp = 0x00;
    tmp = readRc522Reg(reg);
    writeRc522Reg(reg, tmp & ~mask);  // clear bit mask
}
void SetBitMask(uchar reg,uchar mask)
{
    uchar tmp = 0x00;
    tmp = readRc522Reg(reg);
    writeRc522Reg(reg,tmp | mask);  // set bit mask
}

void PcdAntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}

void PcdAntennaOn(void)
{
    uchar i;
    i = readRc522Reg(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}
char M500PcdConfigISOType(unsigned char type)
{
   if (type == 'A')                     //ISO14443_A
   { 
       ClearBitMask(Status2Reg,0x08);
       writeRc522Reg(ModeReg,0x3D);//3F
       writeRc522Reg(RxSelReg,0x86);//84
       writeRc522Reg(RFCfgReg,0x7F);   //4F
   	   writeRc522Reg(TReloadRegL,30);//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
	   writeRc522Reg(TReloadRegH,0);
       writeRc522Reg(TModeReg,0x8D);
	   writeRc522Reg(TPrescalerReg,0x3E);
	   delayMicroseconds(1000);
       PcdAntennaOn();
   }
   else{ return -1; }
   
   return MI_OK;
}

void InitRc522(){
   //Hardware Reset
   pinMode(RC522REST,OUTPUT);
   digitalWrite(RC522REST,HIGH);
   delayMicroseconds(10);
   digitalWrite(RC522REST,LOW);
   delayMicroseconds(10);
   digitalWrite(RC522REST,HIGH);
   delayMicroseconds(10);
   writeRc522Reg(CommandReg,PCD_RESETPHASE);
   delayMicroseconds(10);

   //
   writeRc522Reg(ModeReg,0x3D);
   writeRc522Reg(TReloadRegL,30);
   writeRc522Reg(TReloadRegH,0);
   writeRc522Reg(TModeReg,0x8D);
   writeRc522Reg(TPrescalerReg,0x3E);
   writeRc522Reg(TxAutoReg,0x40);

   //AntennaOff
   PcdAntennaOff();  
   //AntennaOn
   PcdAntennaOn();
   //Config ISO Type A
   M500PcdConfigISOType('A');

}

char PcdComMF522(unsigned char Command, 
                 unsigned char *pInData, 
                 unsigned char InLenByte,
                 unsigned char *pOutData, 
                 unsigned int *pOutLenBit)
{
    char status = MI_ERR;
    unsigned char irqEn   = 0x00;
    unsigned char waitFor = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned int i;
    switch (Command)
    {
        case PCD_AUTHENT:
			irqEn   = 0x12;
			waitFor = 0x10;
			break;
		case PCD_TRANSCEIVE:
			irqEn   = 0x77;
			waitFor = 0x30;
			break;
		default:
			break;
    }
   
    writeRc522Reg(ComIEnReg,irqEn|0x80);
    ClearBitMask(ComIrqReg,0x80);
    writeRc522Reg(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    
    for (i=0; i<InLenByte; i++)
    {   
		writeRc522Reg(FIFODataReg, pInData[i]);    
	}
    writeRc522Reg(CommandReg, Command);
   
    if (Command == PCD_TRANSCEIVE)
    {    
		SetBitMask(BitFramingReg,0x80);  
	}
    
    //i = 600;//根据时钟频率调整，操作M1卡最大等待时间25ms
	i = 250;
    do 
    {
        n = readRc522Reg(ComIrqReg);
        i--;
		delayMicroseconds(100);
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor));
    ClearBitMask(BitFramingReg,0x80);

    if (i!=0)
    {    
        if(!(readRc522Reg(ErrorReg)&0x1B))
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {   status = MI_NOTAGERR;   }
            if (Command == PCD_TRANSCEIVE)
            {
               	n = readRc522Reg(FIFOLevelReg);
              	lastBits = readRc522Reg(ControlReg) & 0x07;
                if (lastBits)
                {   
					*pOutLenBit = (n-1)*8 + lastBits;   
				}
                else
                {   
					*pOutLenBit = n*8;   
				}
                if (n == 0)
                {   
					n = 1;    
				}
                if (n > MAXRLEN)
                {   
					n = MAXRLEN;   
				}
                for (i=0; i<n; i++)
                {   
					pOutData[i] = readRc522Reg(FIFODataReg);    
				}
            }
        }
        else
        {   
			status = MI_ERR;   
		}
        
    }
   
    SetBitMask(ControlReg,0x80);           // stop timer now
    writeRc522Reg(CommandReg,PCD_IDLE); 
    return status;
}

char PcdRequest(uchar req_code,uchar *pTagType)
{
	char status;  
	unsigned int unLen;
	unsigned char ucComMF522Buf[MAXRLEN]; 

	ClearBitMask(Status2Reg,0x08);
	writeRc522Reg(BitFramingReg,0x07);
	SetBitMask(TxControlReg,0x03);
 
	ucComMF522Buf[0] = req_code;

	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);
     printf("TransResult:%d,%d\r\n",status,unLen);
	if ((status == MI_OK) && (unLen == 0x10))
	{    
		*pTagType     = ucComMF522Buf[0];
		*(pTagType+1) = ucComMF522Buf[1];
	}
	else
	{   
		status = MI_ERR;   
	}
   
	return status;
}

char PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i,snr_check=0;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    

    ClearBitMask(Status2Reg,0x08);
    writeRc522Reg(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
 
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK)
	{
		for (i=0; i<4; i++)
		{   
			*(pSnr+i)  = ucComMF522Buf[i];
			snr_check ^= ucComMF522Buf[i];
		}
		if (snr_check != ucComMF522Buf[i])
   		{   
			status = MI_ERR;    
		}
    }
    
    SetBitMask(CollReg,0x80);
    return status;
}

int main(){
   uchar CardRevBuf[16] = { 0 };
   uchar result = 0;
   int i = 0;
   if( wiringPiSetup() < 0 ){
     return -1;
   }
   if( wiringPiSPISetup(0,10000000) < 0 ){
     return -2;
   }
   InitRc522();
   //Find Card
   printf("Finding Active Cards...\r\n");
   result = PcdRequest(PICC_REQIDL,&CardRevBuf[0]);
   if(result != MI_OK){
        printf("Finding All Cards...");
    	result = PcdRequest(PICC_REQALL,&CardRevBuf[0]);
	}
   printf("Result:%d.\r\n",result);
   printf("Buffer:");
   for(i=0;i<16;i++){
      printf("%02x,",CardRevBuf[i]);
   }
   printf("\r\n");
   
   printf("Read Card ID");
   result = PcdAnticoll(&CardRevBuf[2]);
   if(result != MI_OK){
      printf("Read ID Failed."); 
   }else{
      printf("Buffer:");
      for(i=0;i<16;i++){
        printf("%02x,",CardRevBuf[i]);
      }
      printf("\r\n");
   }
   //printf("Commang REG:");
   //printf("R:0x%02x; \r\n",readRc522Reg(ModeReg));
   //printf("BW:0x%02x; ",cmdReg[1]);
   //writeRc522Reg(CommandReg,0x20);
   //printf("Final:0x%02x,0x%02x",cmdReg[0],cmdReg[1]);
   printf("\n");
}

