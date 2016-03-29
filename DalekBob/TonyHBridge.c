/* Test code for BangGood H bridge
 * Motor enable lines are to be tied high
 * Direction is controlled simply by digitally writing one side low, then PWM the other side
 * Swap sides to change direction
 */

int RPWM=5;
int LPWM=6;


void setup() 
{

   pinMode(RPWM,OUTPUT);
   pinMode(LPWM,OUTPUT);
}

#define	DEAD_ZONE_HIGH	550
#define DEAD_ZONE_LOW	460

void loop() {
 

  int iValue = analogRead(5);
   char rgcText[512];


  if(iValue > DEAD_ZONE_HIGH)	// Ensure there is a dead zone from 512 to 550 to avoid problems with a/d conversion fluctuations.
  {
    digitalWrite(LPWM,0);
    iValue -= DEAD_ZONE_HIGH;
    iValue /= 2;
    analogWrite(RPWM,iValue);

	sprintf(rgcText,"ValA=%d\n",iValue);
	Serial.write(rgcText);

  }
  else
  {
	   if(iValue < DEAD_ZONE_LOW)	// Ensure there is a dead zone from 460 to 512 to avoid problems with a/d conversion fluctuations.
	   {
			iValue = DEAD_ZONE_LOW-iValue;
			digitalWrite(RPWM,0);
			iValue /= 2;
			analogWrite(LPWM,iValue);
			sprintf(rgcText,"ValB=%d\n",iValue);
			Serial.write(rgcText);
	  }
  }

 

  if(iValue >= 460 && iValue <=550)
  {
    digitalWrite(RPWM,0);
    digitalWrite(LPWM,0);
  }



  



}
