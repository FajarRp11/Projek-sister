int flame_sensor_pin = 4;       // initializing pin 4 as the sensor output pin
int buzzer_pin = 7;             // initializing pin 7 as the buzzer pin
int led_pin = 2;                // initializing pin 2 as the led pin

unsigned long previousMillis = 0; // store the last time the LED was updated
const long interval = 200;        // interval at which to blink (milliseconds)
bool ledState = LOW;              // LED state

void setup()
{
  pinMode(led_pin, OUTPUT);             // declaring led pin as output pin
  pinMode(flame_sensor_pin, INPUT);     // declaring sensor pin as input pin for Arduino
  pinMode(buzzer_pin, OUTPUT);          // declaring buzzer pin as output pin
  Serial.begin(9600);                   // setting baud rate at 9600
}

void playMelody()
{
  // Play a simple melody: C4, E4, G4, C5
  tone(buzzer_pin, 262, 200);             // C4
  delay(200);
  tone(buzzer_pin, 330, 200);             // E4
  delay(200);
  tone(buzzer_pin, 392, 200);             // G4
  delay(200);
  tone(buzzer_pin, 523, 200);             // C5
  delay(200);
}

void loop()
{
  unsigned long currentMillis = millis();

  if (digitalRead(flame_sensor_pin) == LOW)  // if flame is detected
  {
    Serial.println("FLAME, FLAME, FLAME");

    // Blink the LED without blocking
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(led_pin, ledState);
    }

    playMelody();  // play the melody on the buzzer
  }
  else
  {
    digitalWrite(led_pin, LOW);              // turn off the LED
    noTone(buzzer_pin);                      // stop playing any tone
  }
}
