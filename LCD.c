#include<16F887.h>
#DEVICE *=16 ADC=10 
#FUSES HS,NOWDT,NOPUT,NOLVP 
#USE DELAY(CLOCK=16M) 
#include<luutinh.h>
#include <LCD.h>

char temperature[] = " 00.0 C";
unsigned int16 temp;
void main(){
  setup_oscillator(OSC_8MHZ);                    // Set the internal oscillator to 8MHz
  setup_adc(ADC_CLOCK_INTERNAL);                 // ADC Module uses its internal oscillator
  setup_adc_ports(sAN0);                         // Configure AN0 pin as analog
  set_adc_channel(0);                            // Select channel 0 (AN0)
  lcd_init();                                    // Initialize LCD module
  lcd_putc('\f');                                // Clear LCD
  lcd_gotoxy(3, 1);                              // Go to column 3 row 1
  printf(lcd_putc, "Temperature:");
  while(TRUE){
    delay_ms(1000);
    temp = read_adc() * 0.489;                   // Read analog voltage and convert it to degree Celsius (0.489 = 500/1023)
    if (temp > 99)
      temperature[0]  = 1 + 48;                  // Put 1 (of hundred)
    else
      temperature[0]  = ' ';                     // Put space
    temperature[1]  = (temp / 10) % 10  + 48;
    temperature[2]  =  temp % 10  + 48;
    temperature[5] = 223;                        // Degree symbol
    lcd_gotoxy(5, 2);                            // Go to column 5 row 2
    printf(lcd_putc, temperature);               // Display LM35 temperature result
  }
}