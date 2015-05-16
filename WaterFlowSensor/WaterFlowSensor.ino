/**
* Author: Marc Laventure
* Date: May 8th 2015
* Description: Water Flow Sensor (FS400A G1) readings from digital IO to compute the Mass Flow Rate
*
*/
#define WATER_FLOW_SENSOR_PIN 2 
volatile uint32_t rotorFrequency;
int count = 1;

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
    calculation formula is Frequency = 4.8*Q(Units of Flow)*t(time in seconds)/.99910(Conversion factor of litres of water to kg), where Q is the Mass Flow Rate
  */
  massFlowRate = (float) ((rotorFrequency*.99910)/(60*4.8)); // Gives us Flow Rate in kg per second
  Serial.print(massFlowRate, 4);
  Serial.println(" kg/second");
  
  count++;
  if(count%60 == 0)
  {
    Serial.println("Done 60 second interval");
  }
}
