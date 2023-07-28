#include <stc89.h> 

void delay_ms(unsigned int t){
    unsigned int x;
    while(t--)
        for(x=0;x<126;x++);
}

void delay(unsigned int t){
    /* 
        delay(1) produce 41.250us
        delay(2) produce 53.167us
        delay(3) produce 65.125us
    */
    while(t--);
}

int main(){
    while(1){
        /*  for bit toggle use !
                P2_0 = !P2_0;
            for byte toggle use ~
                P2 = ~P2; 
        */
        P2_7 = !P2_7;
        delay_ms(2);
    }
    return 0;
}
