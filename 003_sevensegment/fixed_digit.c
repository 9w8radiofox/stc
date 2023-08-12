#include <stc89.h>

unsigned char array[4] = {0,0,0,0};

__code unsigned char SEG_CODE[]={
    0xC0, /*0 - 0*/
    0xF9, /*1 - 1*/
    0xA4, /*2 - 2*/
    0xB0, /*3 - 3*/
    0x99, /*4 - 4*/
    0x92, /*5 - 5*/
    0x82, /*6 - 6*/
    0xF8, /*7 - 7*/
    0x80, /*8 - 8*/
    0x90, /*9 - 9*/
    0x88, /*A - A*/
    0x83, /*b - B*/
    0xA7, /*c - C*/
    0xA1, /*d - D*/
    0x86, /*E - E*/
    0x8E, /*F - F*/
    0x7F, /*. - 0x10*/
    0xC6, /*C - 0x11*/
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
    int framerate = 450;
    int digit = 1968;

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
