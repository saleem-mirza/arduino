#include <Wire.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;

void setup()
{
  Serial.begin(9600);

  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }

  while (!Serial) {}
  Serial.println("X\tY\tZ\tM");
}

void loop()
{
  lsm.read();
  delay(100);
  
  float x = 0.001003009 * (lsm.accelData.x + 51.6);  
  float y = 0.0009656984 * (lsm.accelData.y - 1.6);
  float z = 0.000964655 * (lsm.accelData.z + 95.36);
  float m = sqrt(x*x + y*y + z*z);

  Serial.print(x);Serial.print("\t");
  Serial.print(y);Serial.print("\t");
  Serial.print(z);Serial.print("\t");
  Serial.println(m);
}
