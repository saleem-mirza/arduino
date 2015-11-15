#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#define LED_PIN (13)
volatile int _wdt_flag = 1;
volatile unsigned int _timeDuration = 0;

ISR(WDT_vect)
{
  _wdt_flag = _wdt_flag == 0?1:0;
}

void Sleep(unsigned int seconds = 1)
{
  if(seconds < 1)
  {
    _timeDuration = 0;
    return;
  }
  else
  {
    _timeDuration = seconds;
  }
  
  sleep_enable();
  
  while(_timeDuration-- > 0)
  {
    sleep_mode();
  }
    
  sleep_disable();
  power_all_enable();
}

void setupWDT()
{
  // Maximum power saving mode
  //set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // Consumes little bit more power at cost of fast recovery
  set_sleep_mode(SLEEP_MODE_STANDBY);

  MCUSR &= ~(1<<WDRF);

  WDTCSR |= (1 << WDCE) | (1 << WDE);

  WDTCSR = 1 << WDP1 | 1<< WDP2;

  WDTCSR |= _BV(WDIE);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  delay(100);

  pinMode(LED_PIN, OUTPUT);

  setupWDT();
  Serial.println("Initialization completed.");
  delay(100);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);

  // Put MCU to deep sleep for n seconds, default is 1.
  Sleep(1);
}
