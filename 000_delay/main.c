#include <stc89.h> 

void delay_ms(unsigned int t){
    unsigned char x;
    while(t--)
        for(x=0;x<120;x--);
}
int main(){
    while(1){
        P2 = ~P2;
        delay_ms(150);
    }
    return 0;
}
