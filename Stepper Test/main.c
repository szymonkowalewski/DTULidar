

#include <main.h>


void main()
{
   

   setup_oscillator(OSC_8MHZ,2);



   while(TRUE)
   {
      
  }  
}



#include <main.h>

/*Declarations*/
#BYTE portc = 7      // Port used to control motor
BYTE const POSITIONS[4] = { 0b0101, 0b1001, 0b1010, 0b0110 };
unsigned int8 iCurrentPosition = 0; /* This variable keeps track of the current position */
unsigned int32 iDelay = 5000 // delay default 5ms

void main()
{
   /* Setup the oscillator */
   /* Set port c bits B3,B2,B1,B0 as output */
   setup_oscillator(OSC_8MHZ,2);
   set_tris_c(0xF0);
  
   /* Print the menu */
   printf("** Stepper motor controller ** \n");
   printf("Menu: \n");
   printf("w - Turns the motor a full revolution CCW \n");
   printf("d - Singel step CCW \n");
   printf("a - Singel step CW \n");
   printf("+ - increase delay by 0.1ms \n");
   printf("- - decrease delay by 0.1ms \n");
  
   while(TRUE)
   {
      switch(getc())
      {
           case 'w':   
               /* Turn a full revolution (200 steps) CCW */
               for(unsigned int8 i = 1; i<=200; i++)
               {
                  /* Select the next position */
                  portc = POSITIONS[((iCurrentPosition + i)&3)];
                  delay_us(iDelay);
               }
               /* Update the current position */
               iCurrentPosition = ((iCurrentPosition + 200)&3);
               printf("\nFull rotation complete CCW\n"); 
             break;
             
             case 'd':
                 /* Select next position */
                 iCurrentPosition = ((iCurrentPosition+1)&3);
                 
                 /* Set outputs to move the motor */
                 portc = POSITIONS[iCurrentPosition];
                 printf("\nSingle step positive direction CCW\n");
             break;
       
             case 'a':
                 /* Select previous position. 0->3 is special case */
                 if(iCurrentPosition == 0)
                 {
                     iCurrentPosition = 3;
                 }
                 else
                 {
                     iCurrentPosition = ((iCurrentPosition-1)&3);
                 }
                 
                 /* Set outputs to move the motor */
                 portc = POSITIONS[iCurrentPosition];
                 printf("\nSingle step negative direction CW\n");
             break;
             
             case '+':
                 /* Increase delay by 0.1ms */
                 iDelay = iDelay + 100;
                 printf("\nCurrent delay is: %lu ms\n", iDelay); 
             break;
             
             case '-':   
                 /* Decrease delay by 0.1ms */
                 iDelay = iDelay - 100;
                 printf("\nCurrent delay is: %lu ms\n", iDelay);
             break;
             }
        }
}
