




sbit LCD_RS at RC0_bit;
sbit LCD_EN at RC1_bit;
sbit LCD_D4 at RC4_bit;         //Conexao Pic ->LCD
sbit LCD_D5 at RC5_bit;
sbit LCD_D6 at RC6_bit;
sbit LCD_D7 at RC7_bit;




sbit LCD_RS_Direction at TRISC0_bit;
sbit LCD_EN_Direction at TRISC1_bit;
sbit LCD_D4_Direction at TRISC4_bit;        //Conexao Pic ->LCD
sbit LCD_D5_Direction at TRISC5_bit;
sbit LCD_D6_Direction at TRISC6_bit;
sbit LCD_D7_Direction at TRISC7_bit;

char flag0=0;
unsigned tempo1,tempo2,resultado;
char txt[16];
char *text ="Modo de captura";

 void interrupt(){
        if(CCP1IF_bit==1) {

            if(flag0.B0==0){
                tempo1= (CCPR1H *256)+ CCPR1L;
                
                flag0.B0=1;
            
            }else{                                                   //Rotina de interrupcao para guardar o tempo de pulso nos TMR
                 tempo2= (CCPR1H *256)+ CCPR1L;
                 flag0.B0=0;
                 flag0.B1=1;
            
            }
            CCP1IE_bit=0;
            CCP1CON.B0= ~CCP1CON.B0;
            CCP1IE_bit=1;
            CCP1IF_bit=0;
        
        }
 
 
 
 }

void main() {
      TRISC=0x0C;
      T1CON=0x01;
      PORTC=0x0C;
      TRISA=0xFF;
      PORTA=0xFF;
      CCP1CON=0x05;
      CCP1IE_bit=1;
      GIE_bit=1;
      PEIE_bit=1;
      
      Lcd_Init();
      Lcd_Cmd(_LCD_CURSOR_OFF);
      Lcd_Cmd(_LCD_CLEAR);                               //Limpar o LCD e colocar uma mensagem padrao
      Lcd_Out(1,1,text);

      while(1){
      
              resultado=tempo2-tempo1;
              IntToStr(resultado,txt);                           //Exibir Resultado no Display
              Lcd_Out(2,1,txt);
              flag0.B1=0;
      }
      
      
}