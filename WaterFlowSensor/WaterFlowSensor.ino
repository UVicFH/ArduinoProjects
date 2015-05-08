/**
* Author: Marc Laventure
* Date: May 8th 2015
* Description: Water Flow Sensor (FS400A G1) readings from digital IO to compute the Mass Flow Rate
* Sensor Reference Manual: http://ultisensor.com/post/G1-Hall-Effect-Flow-Sensor-USN-HS10TA-1-60Lmin.html
*
*/
#define WATER_FLOW_SENSOR_PIN 1
volatile uint32_t rotorFrequency;

/**
* The Interrupt Service Routine (ISR) for incrememnting the pulse to achieve frequency
*/
void rotorPulseInterrupt(void)
{
  rotorFrequency++;
}

void setup(void) 
{
  pinMode(WATER_FLOW_SENSOR_PIN, INPUT); // Set digital pin 2 as sensors input
  attachInterrupt(0, rotorPulseInterrupt, RISING); // Setup the interrupt for rising edge detection
  Serial.begin(9600); 
}

void loop(void) 
{
  float massFlowRate;
  rotorFrequency = 0;
  
  sei(); // Enable interrupts for retrieving data
  delay(1000); // Wait for 1 second (simplifies calculation)
  cli(); // Disable interrupts because we dont want any more after we retrieved our data
  
  /* Had to do research on this, but the reference manual for this sensor states the
    calculation formula is Frequency = 56*Q, where Q is the Mass Flow Rate
  */
  massFlowRate = rotorFrequency/56; // Gives us Flow Rate in Litres per minute
  Serial.print(massFlowRate);
  Serial.print(" Litres/minute");
}
