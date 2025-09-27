#define F_CPU 3333333UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void main(void){
    uint32_t result = 0;
    
   // PORTB.DIRSET = PIN0_bm;
    
    /* Disable digital input buffer */
    PORTA.PIN6CTRL &= ~PORT_ISC_gm;
    PORTA.PIN6CTRL |= PORT_ISC_INPUT_DISABLE_gc;
    
    /* Disable pull-up resistor */
    PORTA.PIN6CTRL &= ~PORT_PULLUPEN_bm;
    
    
    
    ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc; //INPUT PIN SELECTION
     //VOLTAGE REFF
    
    ADC0.CTRLC |= ADC_REFSEL_VDDREF_gc//VDD VOLTAGE 
               | ADC_PRESC_DIV4_gc; //prescaler as /4
    
    ADC0.CTRLA |= ADC_RESSEL_10BIT_gc //10BIT RESOLUTION
               | ADC_ENABLE_bm;
    //.........................................//
        lcd_init();
        lcd_clear();
   //..........................................//
    // demo variables
   
    
    while(1){
        ADC0.COMMAND = ADC_STCONV_bm;
         while(!(ADC0.INTFLAGS & ADC_RESRDY_bm)){;}
       
         ADC0.INTFLAGS = ADC_RESRDY_bm;
         result = ADC0.RES;
         //_delay_ms(100);
              
     //.....................//         
          
         lcd_gotoxy(0,0);
         lcd_print("result:");
         lcd_print_uint(result);
        _delay_ms(10);
          lcd_clear();
     //......................//   
          
}
}   
