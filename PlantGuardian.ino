/**
 * Plant Guardian - Moisture Tracker
 * Created by Jonathan Lundström for Conrad.se
 * Website: http://jonathanlundstrom.me
 * Last edited: 2017-07-04
 */

bool debug = false;                   // Turn this on to enable debug output in serial console.
int timeout = 1000;                  // Time to sleep before each serial output is sent.

int plantOneInput = A0;               // Change this to represent port that sensor #1 is connected to.
int plantTwoInput = A1;               // Change this to represent port that sensor #2 is connected to.

int maximumPlantOne = 880;            // Change this number to the maximum value that the sensor gives while in a glass of water (enable debug)
int maximumPlantTwo = 870;            // Change this number to the maximum value that the sensor gives while in a glass of water (enable debug)

float moisturePlantOne = 0;
float moisturePlantTwo = 0;

/**
 * Setup Arduino application.
 */
void setup() {
  Serial.begin(9600);
  pinMode(plantOneInput, INPUT);
  pinMode(plantTwoInput, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Map moisture value against max value and return percentage.
 */
String moistureAsPercentage(float value, int maximum) {
  int mappedValue = map(value, 0, maximum, 0, 100);
  if (mappedValue > 100) { mappedValue = 100; }
  return String(mappedValue);
}

/**
 * The almighty loop...
 */
void loop() {
  moisturePlantOne = analogRead(plantOneInput);
  moisturePlantTwo = analogRead(plantTwoInput);

  if (debug) {
    Serial.println("Sensor #1: " + String(moisturePlantOne));
    Serial.println("Sensor #2: " + String(moisturePlantTwo));
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("{\"sensorOne\":\"" + moistureAsPercentage(moisturePlantOne, maximumPlantOne) + "\", \"sensorTwo\":\"" + moistureAsPercentage(moisturePlantTwo, maximumPlantTwo) + "\"}");
    digitalWrite(LED_BUILTIN, LOW); 
  }
  
  delay(timeout);
}
