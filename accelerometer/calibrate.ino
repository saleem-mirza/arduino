#include <Wire.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;

void setup()
{
  Serial.begin(9600);

  // Try to initialise and warn if we couldn't detect the chip
  while (!Serial) {}
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
}

volatile int count = 0;

void loop()
{

  Serial.println("Press any key to continue...");
  while (!Serial.available()) {} // wait for a character
  
  for(count = 0;count < 25;count ++)
  {
    lsm.read();
    float x =lsm.accelData.x;
    Serial.print("X: "); Serial.print(x); Serial.print(" ");
  
    float y = lsm.accelData.y;
    Serial.print("Y: "); Serial.print(y); Serial.print(" ");
  
    float z = lsm.accelData.z;
    Serial.print("Z: "); Serial.print(z); Serial.print(" ");
  
    Serial.println("");
    delay(50);
  }

  while (Serial.available())
  {
    Serial.read();  // clear the input buffer
  }
  Serial.println("Change side...");
}
