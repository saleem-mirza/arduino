#include <Wire.h>

void setup()
{
  Wire.begin();
  while (!Serial)
  {}
  Serial.begin(9600);
}

void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("\n\nScanning...\n");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("??");
    }
    else
    {
      Serial.print("..");
    }
    if(address%16==0)
    {
      Serial.println("");
    }
  }
  if (nDevices == 0)
  {
    Serial.println("");
    Serial.println("No I2C devices found\n");
    Serial.println("done\n");
  }
  delay(5000);           // wait 5 seconds for next scan
}

