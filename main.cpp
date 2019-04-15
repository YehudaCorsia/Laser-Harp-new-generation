const uint8_t NUM_OF_SENSORS = 8;
const uint8_t SENSORS_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A5};
const uint16_t DIFFERENCE_INDICATE_HAND = 30; // Need rethink about this... maybe add potentiometer.

int16_t arrSensorsThreshold[NUM_OF_SENSORS] = { 0 };
uint16_t unCurrSensorData[NUM_OF_SENSORS] = { 0 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Initialize sensors pins
  for (uint8_t i = 0; i < NUM_OF_SENSORS; ++i) {
    pinMode(SENSORS_PINS[i], INPUT);
  }
  
  delay(1000);
  
  calibrate();
}

void loop() {
  read_sensors_data();

  for (uint8_t unIndexSensor = 0; unIndexSensor < NUM_OF_SENSORS; ++unIndexSensor)
  {
    if(unCurrSensorData[unIndexSensor] < arrSensorsThreshold[unIndexSensor]){
      Serial.println("HAND ! Laser number " + (String)unIndexSensor + " was with value " + (String)unCurrSensorData[unIndexSensor]);
    }
    else
    {
      //Serial.println("NOT HAND ! Laser number " + (String)unIndexSensor + " was with value " + (String)unCurrSensorData[unIndexSensor]);
    }
  }

  delay(100);
}

void read_sensors_data() {
  for (uint8_t i = 0; i < NUM_OF_SENSORS; ++i) {
    unCurrSensorData[i] = analogRead(SENSORS_PINS[i]);
  }
}

void calibrate() {
  Serial.println("Start calibrate.");
  
  const uint16_t TIMES_TO_CHECK = 500;
  uint32_t arrSumSensorsValue[NUM_OF_SENSORS] = { 0 };

  for (uint16_t i = 0; i < TIMES_TO_CHECK; ++i)
  {
      read_sensors_data();
      for (uint8_t unIndexSensor = 0; unIndexSensor < NUM_OF_SENSORS; ++unIndexSensor)
      {
          arrSumSensorsValue[unIndexSensor] += unCurrSensorData[unIndexSensor];
      }

      delay(2);
  }
  
  for (uint8_t unIndexSensor = 0; unIndexSensor < NUM_OF_SENSORS; ++unIndexSensor)
  {
    arrSensorsThreshold[unIndexSensor] = (arrSumSensorsValue[unIndexSensor] / TIMES_TO_CHECK) - DIFFERENCE_INDICATE_HAND;
    Serial.println("Avg of Sensor number " + (String)unIndexSensor + " = " + (String)(arrSumSensorsValue[unIndexSensor] / TIMES_TO_CHECK));
    Serial.println("Difference indicate hand was " + (String)DIFFERENCE_INDICATE_HAND);
    Serial.println("Threshold of Sensor number " + (String)unIndexSensor + " = " + (String)arrSensorsThreshold[unIndexSensor]);
  }

  Serial.println("End calibrate.");
}
