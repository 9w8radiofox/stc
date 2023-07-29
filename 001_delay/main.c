#include <stc89.h> 

/**
 * @brief Set the up timer0
 *        Fastest possible Timer0 count is   35.75 us
 *        Slower  possible Timer0 count is  296.25 us
 */
void setup_delay_timer(void){
    TMOD  = 0x2;
    TCON  = 0;
    TF0   = 0;
    TL0   = TH0   = 0xFF;
    TR0   = 0;
}

/**
 * @brief delay routine
 * 
 * @param t 
 *          x =  0, get  25.000 us
 *          x =  1, get  35.813 us
 *          x =  2, get  49.875 us
 *          x =  5, get  92.250 us
 *          x =  6, get 106.375 us
 * 
 *          t =  0, get   28.25  us
 *          t =  1, get  110.668 us 
 *          t =  2, get  192.188 us
 *          t =  3, get  275.625 us
 *          t =  4, get  358.125 us
 *          t =  5, get  440.563 us
 *          t =  6, get  523.000 us
 *          t =  7, get  605.500 us
 *          t = 10, get  852.938 us
 *          t = 12, get 1017.813 us
 *  */
void delay(unsigned int t){
    int x;
    TR0 = 1;
    for(;t>0;t--)
        for(x=0;x<5;x++){
            while (!TF0);
            TF0 = 0;
        };
    TR0 = 0;
}

/* main program */
void main(void){
    setup_delay_timer();   
    while (1){
        delay(12);
        P2 = ~P2;
    };
}
