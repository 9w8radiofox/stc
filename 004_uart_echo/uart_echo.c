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

void Uart_init(void);
void SendData(unsigned char dat);
void SendString(char *s);

void main(void){
    
    Uart_init();
    SendString("STC89-90xx\r\nUart Test !\r\n");
    while(1);

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
        P2 = SBUF;
        P2 = ~P2;
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


