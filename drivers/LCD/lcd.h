/*
 * 4_bit mood
 
 * Pin Connections:
 * PB3 [pin 5]  -> RS
 * PB2 [pin 6]  -> EN
 * PB4 [pin 23] -> D4
 * PB5 [pin 24] -> D5
 * PB6 [pin 25] -> D6
 * PB7 [pin 26] -> D7
 *
 *
 * 
 *
 */






#define En 0x04;
#define Rs 0x08;
//functions pt
void SystemInit();
void delay_milli(int n);
void delay_micro(int n);
void LCD_init(void);
void Uart_Init();
void Lcd_Write(unsigned char data,unsigned char command );
void Lcd_Cmd(unsigned char command);
void Lcd_Data(unsigned char data);
void send_string(char *s);
void send_int(int n);
void send_float(void);
void count(void);
void delay(int cnt);
void display(void);