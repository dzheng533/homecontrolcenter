#include "lcd1602.h"
#define PINBASE    100
#define DEVICEADDR 0x27

#define EN 2
#define RS 0
#define RW 1
#define BGLIGHT 3
#define LCDDB4 4
#define LCDDB5 5
#define LCDDB6 6
#define LCDDB7 7

#ifndef TRUE
#define  TRUE  (1==1)
#define  FALSE (1==2)
#endif
//cmd
#define LCD_CLEAR    0x01
#define LCD_HOME     0x02
#define LCD_ENTRY    0x04
#define LCD_CTRL     0x08
#define LCD_CDSHIFT  0x10
#define LCD_FUNC     0x20
#define LCD_CGRAM    0x40
#define LCD_DGRAM    0x80

// Bite in the entry register
#define LCD_ENTRY_SH  0x01
#define LCD_ENTRY_ID  0x02

// Bits in the control register
#define LCD_BLINK_CTRL    0x01
#define LCD_CURSOR_CTRL   0x02
#define LCD_DISPLAY_CTRL  0x04
// Bits in the function register
#define LCD_FUNC_F    0x01
#define LCD_FUNC_N    0x08
#define LCD_FUNC_DL   0x10

#define LCD_CDSHIFT_RL 0x04

static int lcdControl;
static const int rowOff[4] = {0x00,0x40,0x14,0x54};
static int cx,cy;

void writeData(unsigned char data){
   digitalWrite(PINBASE+LCDDB7,(data&0x08)?1:0);
   digitalWrite(PINBASE+LCDDB6,(data&0x04)?1:0);
   digitalWrite(PINBASE+LCDDB5,(data&0x02)?1:0);
   digitalWrite(PINBASE+LCDDB4,(data&0x01)?1:0);

   digitalWrite(PINBASE+EN,1);
   delayMicroseconds(50);
   digitalWrite(PINBASE+EN,0);
   delayMicroseconds(50);
}
void LCDCmdData(unsigned char data){
   unsigned char myData = data;
   unsigned char d4;
   //Write heigh 4 bits
   d4 = (myData >> 4) & 0x0F;
   writeData(d4);
   //Write low 4 bits
   d4 = myData & 0x0F;
   writeData(d4);
}
void LCDCmd(unsigned char cmd){
  digitalWrite(PINBASE+RS,0);
  digitalWrite(PINBASE+RW,0);
  digitalWrite(PINBASE+EN,0);
  LCDCmdData(cmd);
  delay(2);
}
void LCD4Cmd(unsigned char cmd){
   unsigned char tmpCmd = cmd;
   digitalWrite(PINBASE+RS,0);
   digitalWrite(PINBASE+RW,0);
   digitalWrite(PINBASE+EN,0);
   writeData(tmpCmd); 
}

void CLR(){
   LCDCmd(LCD_CLEAR);
   LCDCmd(LCD_HOME);
   delay(5);
}
void HOME(){
   LCDCmd(LCD_HOME);
   delay(5);
}
void DISPLAY(int state){
  if(state){
     lcdControl |= LCD_DISPLAY_CTRL;
  }else{
     lcdControl &= ~LCD_DISPLAY_CTRL;
  }
  LCDCmd(LCD_CTRL| lcdControl);
}

void CURSOR(int state){
  if(state){
     lcdControl |= LCD_CURSOR_CTRL;
  }else{
     lcdControl &= ~LCD_CURSOR_CTRL;
  }

  LCDCmd(LCD_CTRL| lcdControl);

}
void CURSOR_BLINK(int state){

   if(state){
     lcdControl |= LCD_BLINK_CTRL;
   }else{
     lcdControl &= ~LCD_BLINK_CTRL;
   }

  LCDCmd(LCD_CTRL| lcdControl);
}
void putChar(unsigned char data){
  digitalWrite(PINBASE+RS,HIGH);
  LCDCmdData(data);

}
void InitLCD(){
  unsigned char func;
  pcf8574Setup(PINBASE,DEVICEADDR);
  digitalWrite(PINBASE+BGLIGHT,LOW);  pinMode(PINBASE+BGLIGHT,OUTPUT);
  digitalWrite(PINBASE+LCDDB4,LOW);  pinMode(PINBASE+LCDDB4,OUTPUT);
  digitalWrite(PINBASE+LCDDB5,LOW);  pinMode(PINBASE+LCDDB5,OUTPUT);
  digitalWrite(PINBASE+LCDDB6,LOW);  pinMode(PINBASE+LCDDB6,OUTPUT);
  digitalWrite(PINBASE+LCDDB7,LOW);  pinMode(PINBASE+LCDDB7,OUTPUT);
  digitalWrite(PINBASE+EN,LOW);  pinMode(PINBASE+EN,OUTPUT);
  digitalWrite(PINBASE+RW,LOW);  pinMode(PINBASE+RW,OUTPUT);
  digitalWrite(PINBASE+RS,LOW);  pinMode(PINBASE+RS,OUTPUT);
  LightSwitch(ON);
  delay(35); //ms
  cx=cy=0;

  //set 4 bit mode
  func = LCD_FUNC | LCD_FUNC_DL;
  LCD4Cmd(func>>4);  delay(35);  //set 8 bit mode 3 times
  LCD4Cmd(func>>4);  delay(35);
  LCD4Cmd(func>>4);  delay(35);
  func = LCD_FUNC;
  LCD4Cmd(func>>4);  delay(35); // the 4th set 4 bit mode
  DISPLAY(TRUE);
  CURSOR(FALSE);
  CURSOR_BLINK(FALSE);
  CLR();
  Position(1,1);
  putChar('A');
  WriteLCDString("Hello!");
}
void LightSwitch(int flag){
  digitalWrite(PINBASE+BGLIGHT,flag);
}
void WriteLCDString(char *str){
  while(*str >0){
   putChar(*str);
   str++;
  }
}
void Position(int x,int y){
   if(x>16 ||x<0)
     return;
   if(y>2 || y<0)
     return;
   LCDCmd(x+(LCD_DGRAM|rowOff[y]));
  cx = x;
  cy = y;
}

