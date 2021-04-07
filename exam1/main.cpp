#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

AnalogOut aout(PA_4);
//AnalogOut Rvin(D6);

DigitalIn But1(A2);
DigitalIn But2(A1);
DigitalIn But3(A0);
DigitalIn mypin(USER_BUTTON);

AnalogIn VIN(A3);


int main(){

    float rate = 0.25;
    float frequency;
    uint16_t sample = 0;
    float sample2[480];
    int flag = 0;

    aout = 1;

    while(1){

        if (But1 == 1){

            rate = rate * 2;
            if (rate > 1){
                  rate = 1;
            }
            uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%f\n", rate);
        }

        if (But2 == 1){

            uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%f\n", rate);
            break;

        }

        if (But3 == 1){
            
            
            rate = rate * 0.5;

            if (rate < 0.125) {
                  rate = 0.125;
            }

            uLCD.color(BLUE);  
            uLCD.background_color(WHITE);
            uLCD.textbackground_color(WHITE);
            uLCD.cls();
            // basic printf demo = 16 by 18 characters on screen
            uLCD.locate(1, 1);
            uLCD.text_width(4); //4X size text
            uLCD.text_height(4);
            uLCD.color(GREEN);
            uLCD.printf("\n%f\n", rate);

        }


    }

   

    
        

        /*uLCD.color(BLUE);  
        uLCD.background_color(WHITE);
        uLCD.textbackground_color(WHITE);
        uLCD.cls();
        // basic printf demo = 16 by 18 characters on screen
        uLCD.locate(1, 1);
        uLCD.text_width(4); //4X size text
        uLCD.text_height(4);
        uLCD.color(GREEN);
        uLCD.printf("\n%d\n", a); //Default Green on black text*/
        /*fr (int i=30; i>=0; --i) {
            uLCD.locate(1,2);
            uLCD.printf("%2d",i);
            ThisThread::sleep_for(500ms);
        }*/

    //}

    frequency = 4.166;
    printf("%f\r\n", frequency);

      int num;
      int peak;
      num = 80 * rate;
      peak = 240 - (2 * num);

    while(1){
            if (!mypin) break;
            for (int i = 0; i < num; i++) {

                  sample = (uint16_t)(59578 * i / num);
                  aout.write_u16(sample);
                  sample2[i] = VIN;
                  wait_us(940);
            }
            for (int i = 0; i < peak; i++){
                  sample = (uint16_t)(59578);
                  aout.write_u16(sample);
                  sample2[i + num] = VIN;
                  wait_us(940);
            }
            for (int i = 0; i < num; i++) {
                  sample = (uint16_t)(59578 * (num - i) / num);
                  aout.write_u16(sample);
                  sample2[i + num + peak] = VIN;
                  
                  wait_us(940);
            }
            
            for (int i = 0; i < num; i++) {

                  sample = (uint16_t)(59578 * i / num);
                  aout.write_u16(sample);
                  sample2[i + 2 * num + peak] = VIN;
                  wait_us(940);
            }
            for (int i = 0; i < peak; i++){
                  sample = (uint16_t)(59578);
                  aout.write_u16(sample);
                  sample2[i + 3 * num + peak] = VIN;
                  wait_us(940);
            }
            for (int i = 0; i < num; i++) {
                  sample = (uint16_t)(59578 * (num - i) / num);
                  aout.write_u16(sample);
                  sample2[i + 3 * num + 2 * peak] = VIN;
                  
                  wait_us(940);
            }
      }

      for (int i = 0; i < 480; i++) {
            printf("%f\r\n", sample2[i]);
      }
}