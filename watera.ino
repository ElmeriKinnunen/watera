
int LED_GREEN = 12;
int LED_RED = 14;
int relay = 5;
int moisture_value = A0;
int moisture_percent = 0;

void setup()
{
  Serial.begin(9600); // set serial data rate (bps)
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(relay, OUTPUT); // relay for pump

  digitalWrite(relay, HIGH); // set pump off by default
}

void loop()
{
	//map value, airvalue, watervalue, percent min, percent max
	moisture_percent = map(analogRead(moisture_value), 723, 435, 0, 100);

	if (moisture_percent > 100) {
		moisture_percent = 100;
	}

	if (moisture_percent < 1) {
		moisture_percent = 0;
	}

	if (moisture_percent < -10 || moisture_percent > 110) {
		Serial.print("ERROR: Moisture soil sensor value is incorrect!");
		Serial.print("Value: ");
		Serial.println(moisture_percent);
		digitalWrite(LED_RED, HIGH);
	}

	Serial.print("Moisture: ");
	Serial.print(moisture_percent);
	Serial.println("%");

	if (moisture_percent < 50 && moisture_percent > 0) {

		digitalWrite(LED_GREEN, HIGH);
		digitalWrite(relay, LOW);
		Serial.println("Relay ON");

		int timer = 0;

		while (timer != 10)
		{
			digitalWrite(LED_GREEN, LOW);
			delay(500);
			digitalWrite(LED_GREEN, HIGH);
			delay(500);

			timer++;
		}


		digitalWrite(LED_GREEN, LOW);
		digitalWrite(relay, HIGH);
		Serial.println("Relay OFF");

	}

	delay(5000);
}
