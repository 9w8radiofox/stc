#include <stc89.h>

#define FOSC 11059200L      
#define BAUD 9600           

/*Define UART parity mode*/
#define NONE_PARITY     0   
#define ODD_PARITY      1   
#define EVEN_PARITY     2   
#define MARK_PARITY     3   
#define SPACE_PARITY    4   

#define PARITYBIT NONE_PARITY

/*__sbit bit9 = P2^2;*/
__bit busy;

char number = -1;
unsigned char array[4] = {0};

__code unsigned char SEG_CODE[]={
    0xC0,
    0xF9,
    0xA4,
    0xB0,
    0x99,
    0x92,
    0x82,
    0xF8,
    0x80,
    0x90 
};

void int_to_digit(int n){
    array[3] = 0;
    while(n>=1000){
        array[3]++;
        n -= 1000;
    }

    array[2] = 0;
    while(n>=100){
        array[2]++;
        n -= 100;
    }

    array[1] = 0;
    while(n>=10){
        array[1]++;
        n -= 10;
    }

    array[0] = n;

}

void Uart_init(void);
void SendData(unsigned char dat);
void SendString(char *s);

void main(void){
    int i, j;
    int framerate = 400;
    
    Uart_init();
    SendString("\n*");
    while(1){
        if (number==-1){
            SendString("\nEnter an integer : ");
            number = 0;
        }

        for (i = 0; i <4; i++){
            switch(i){
                case 0 :
                    P3_7 = 0x01;
                    P3_4 = 0x00;
                    break;
                case 1 :
                    P3_4 = 0x01;
                    P3_5 = 0x00;
                    break;
                case 2 :
                    P3_5 = 0x01;
                    P3_6 = 0x00;
                    break;
                case 3 :
                    P3_6 = 0x01;
                    P3_7 = 0x00;
                    break; 
            }
            P2 = SEG_CODE[array[i]];
            for(j = framerate; j>0;j--){};
        }   
    }
}

void num2char(int num,unsigned char temp[3]){
    int i;
    i = 2;
    do{
        temp[i] = num%10+'0';
        num/=10;
        i = i -1;
    } while(i>=0);
}


void Uart_init(void){
#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;            
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;            
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;            
#endif

    TMOD = 0x20;            
    TH1 = TL1 = -(FOSC/12/32/BAUD); 
    TR1 = 1;               
    ES = 1;                
    EA = 1; 

}

/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() __interrupt (4)
{
    if (RI)
    {
        RI = 0;
        SendData(SBUF);
        if(SBUF==0xd){
            number=4;
            P2 = 0xA5;
        }
        else{
            array[number] = SBUF;
            if (number<4)
                number++;
        }
/*      P2 = SBUF;
        P2 = ~P2; */
    }
    if (TI)
    {
        TI = 0;           
        busy = 0;         
    }
}

/*----------------------------
Send a unsigned char data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(unsigned char dat)
{
    while (busy);          
    ACC = dat;             
    if (P)                 
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;            
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;            
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;            
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;            
#endif
    }
    busy = 1;
    SBUF = ACC;             
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString(char *s)
{
    while (*s)              
    {
        SendData(*s++);     
    }
}


