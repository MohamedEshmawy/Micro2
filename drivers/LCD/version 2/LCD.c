#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "MY_HEADERS/delay.h"
#include "MY_HEADERS/LCD.H"



/*__________________________________________structure for putting custom hex__________________________________________________  */
typedef struct custom_char{
unsigned char cus_c [8];
}char_str;

char_str cus_chr [8]={
              {0x1f,0x11,0xa,0x4,0xa,0x11,0x4,0x4},	//hex value for putting at the first location of CGRAM and so on 
							{0x4,0xe,0x1f,0x0,0x11,0x15,0x5,0x4},
							{0x0,0xa,0x1f,0x1f,0xe,0x4,0x0,0x0},
							{0x4,0x6,0x5,0x5,0x4,0x4,0x1c,0x1c},
							{0x6,0x5,0x7,0x5,0x5,0x1d,0x1b,0x3},
							{0x12,0xc,0xc,0x12,0x9,0x6,0x6,0x9},
							{0x1f,0x1f,0xe,0x4,0xa,0x11,0x1f,0x0},
							{0x1f,0x11,0xa,0x4,0xe,0x1f,0x1f,0x0},		
};
/*__________________________________________function for enabling pulse ______________________________________________________  */
void enable(void){																			
					LCD_PORT->DATA|=(1<<EN);
				__ASM volatile ("MOV R2 ,#0xFF");		//Check this instruction delay, This should be about 1us
				LCD_PORT->DATA&=~(1<<EN);
}

/*________________________________________function for reading address count and busy flag____________________________________  */
uint8_t Bussy_read (uint8_t ret){
							uint8_t read_byte=0;	
							LCD_PORT->DEN&=~(0xF); 																		
							LCD_PORT->DIR&=~0xF; 	
							LCD_PORT->DEN|=(0xF);
							LCD_PORT->DATA&=~(1<<RS);
							LCD_PORT->DATA|=(1<<RW);
							enable();
							read_byte=(0x0F&LCD_PORT->DATA);
							read_byte=(read_byte<<4)&(0xF0);
							enable();
							read_byte|=(0x0F&LCD_PORT->DATA);
							if(ret==bsy_flg){
							read_byte&=(1<<7);
							read_byte=(read_byte>>7);		
							}
							return read_byte ;
}
/*__________________________________________this function writes the nibble to the LCD port for 4 bit mode_________________________  */
void LCD_bus_write(uint8_t data){
		  LCD_PORT->DEN&=~(0xF); 
			LCD_PORT->DIR|=0xF;       									//	Setting the LCD_PORT output
			LCD_PORT->DATA&=(0xF0);
			LCD_PORT->DEN|=(0xF);  											//	Enabling digital pins from 0 to 3
			LCD_PORT->DATA|=(0x0F&data);																
}
/*__________________________________________this function initializes the LCD in 4bit mode with courser options_____________________  */
 void LCD_ini(unsigned char mode){
				volatile uint32_t delay=0;								// 	Declaring  dummy bit for waiting after enabling clock  
				SYSCTL->RCGC2|=(1<<PORT_index);  					//	Clock for the LCD_PORT
				delay=SYSCTL->RCGC2;										  //	waiting after enabling the clock
				LCD_PORT->LOCK=0x4C4F434B;								//	writing the magic number to LOCK register	
				LCD_PORT->CR|=(1<<EN)|(1<<RW)|(1<<RS)|(0xF);//	Allowing changes for LCD_PORT   
				LCD_PORT->DIR|=(1<<EN)|(1<<RW)|(1<<RS);
				LCD_PORT->DEN|=(1<<EN)|(1<<RW)|(1<<RS);
	 
				delay_ms(20);
				LCD_PORT->DATA&=~((1<<RS)|(1<<RW));
				
				LCD_bus_write(0x03);
				enable();														//can't check bussy flag yet. so waiting 
				delay_ms(5);
				 
				LCD_bus_write(0x03);
		    enable();		
	      delay_ms(1);
				
				LCD_bus_write(0x03);
				enable();
				LCD_bus_write(1<<1);
				enable();
				
				LCD_command(1<<5);
				LCD_command(mode);
				LCD_command(clrscr);
				LCD_command(0x6);
 }
/*__________________________________________read DR an internal operation (DDRAM or CGRAM to DR)_________________________  */ 
 uint8_t LCD_read_ram(void){
							uint8_t read_byte=0;																								
							while(Bussy_read(bsy_flg)!=0);
							LCD_PORT->DEN&=~(0xF); 
							LCD_PORT->DIR&=~0xF; 	
							LCD_PORT->DEN|=(0xF);
							LCD_PORT->DATA|=((1<<RS)|(1<<RW));
							enable();
							read_byte=(0x0F&LCD_PORT->DATA);
							read_byte=(read_byte<<4)&(0xF0);
							enable();
							read_byte|=(0x0F&LCD_PORT->DATA);
							return read_byte ;									
 }
 /*__________________________________________function for writing IR register _______________________________________________  */
void LCD_command(unsigned char com){
						while(Bussy_read(bsy_flg)!=0);
						LCD_PORT->DATA&=~((1<<RS)|(1<<RW));
						LCD_bus_write(com>>4);
						enable();
						LCD_bus_write(com);
						enable();
}
/*__________________________________________function for writing DR register __________________________________________________  */
void LCD_data(unsigned char com){
						while(Bussy_read(bsy_flg)!=0);
						LCD_PORT->DATA&=~(1<<RW);
						LCD_PORT->DATA|=(1<<RS);
						LCD_bus_write(com>>4);
						enable();
						LCD_bus_write(com);
						enable();
}
/*__________________________________________function for clearing LCD display __________________________________________________  */
void LCD_clrscr(void){
				LCD_command(1);
			  LCD_goto(0,0);
}
/*__________________________________________function for putting string on the disply____________________________________________  */
void LCD_puts(const char *s)
{
    register char c;
    while ( (c = *s++) ) {
        LCD_putc(c);
    }
}
/*_____________________________________function for putting custom character from CGRAM location _______________________________  */
void LCD_put_cus(unsigned char ord){
LCD_data(ord-1);
}

/*__________________________________________function for putting character on lcd_______________________________________________  */
void LCD_putc(unsigned char a){
		unsigned add=Bussy_read(add_count);
		if(a=='\n'){
			LCD_command(0xc0);
		}			
		else{
		LCD_data(a);	
		}
}
/*__________________________________________this function loads the CGRAM address with 8 characters from structure_____________  */
void LCD_buf_ini(void){
	unsigned add=Bussy_read(add_count);
	LCD_command(0x40);
	for(char i=0;i<8;++i){
		for(char j=0;j<8;++j){
	LCD_data(cus_chr[i].cus_c[j]);
	}		
}
LCD_command(add);
}
/*__________________________________________function for jumping to the random location of display______________________________  */
void LCD_goto(uint8_t clm,uint8_t row){
		if(row==0) LCD_command(0x80+clm);
		else 				LCD_command(0xC0+clm);
}
/*__________________________________________function for putting signed integer________________________________________________  */
void LCD_puti(long int print_val){
		uint16_t i=0,buff[20];
		if (print_val<0)
						{
							LCD_putc('-');
							print_val*=(-1);
						}
	
		int temp=print_val;
						for(i=0;print_val!=0;i++){
							buff[i]=temp%10;
							print_val=print_val/10;
							temp=print_val;
							}
							for(;i!=0;--i){
							LCD_putc(buff[i-1]+48);
							}	
}

/*__________________________________________function for putting signed float on lcd_______________________________________________  */
void LCD_putf(float print_val){
	char i;
	long int temp=print_val,temp1=0;
	int dec_plc=1;
		if (print_val<0)
			{
				LCD_putc('-');
				print_val*=(-1);
			}
		for (i=0;print_val!=temp;i++)
			{
				print_val*=10;
				temp=print_val;
				print_val*=10;
				print_val/=10;
	}
	for (;i>0;--i)
	{
		dec_plc*=10;
	}
	temp1=temp;
	LCD_puti(temp/dec_plc);
	LCD_putc('.');
	LCD_puti(temp%dec_plc);
}



