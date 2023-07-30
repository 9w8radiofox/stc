#include <stc89.h>

unsigned char array[4] = {0,0,0,0};

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

/**
 * @brief 
 * 
 * framerate = 750, frame rate is  19.12 Hz
 * framerate = 500, frame rate is  28.63 Hz
 * framerate = 250, frame rate is  56.94 Hz
 * framerate = 100, frame rate is 139.93 Hz
 * framerate =  50, frame rate is 272.17 Hz
 * 
 */
void main(void){
    int i, j;
    int framerate = 400;
    int digit = 8152;

    P3 = 0xFF;

    int_to_digit(digit);

    while(1){
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
