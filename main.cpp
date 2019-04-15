
const uint8_t NUM_OF_SENSORS = 1;
const uint8_t SENSORS_PINS[] = {A0, A1, A2, A3, A4, A5, A6, A5};
const uint16_t DIFFERENCE_INDICATE_HAND = 30; // Need rethink about this... maybe add potentiometer.

int16_t arrSensorsThreshold[NUM_OF_SENSORS] = { 0 };
uint16_t curr_sensor_data[NUM_OF_SENSORS] = { 0 };


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Initialize sensors pins
  for (uint8_t i = 0; i < NUM_OF_SENSORS; ++i) {
    pinMode(SENSORS_PINS[i], INPUT);
  }


  delay(1500);
  calibrate();

  
}

void loop() {
  read_sensors_data();

  for (uint8_t index_sensor = 0; index_sensor < NUM_OF_SENSORS; ++index_sensor)
  {
    if(curr_sensor_data[index_sensor] < arrSensorsThreshold[index_sensor]){
      Serial.println("HAND ! Laser number " + (String)index_sensor + " was with value " + (String)curr_sensor_data[index_sensor]);
    }
    else
    {
      //Serial.println("NOT HAND ! Laser number " + (String)index_sensor + " was with value " + (String)curr_sensor_data[index_sensor]);
    }
  }

  delay(100);
}

void read_sensors_data() {
  for (uint8_t i = 0; i < NUM_OF_SENSORS; ++i) {
    curr_sensor_data[i] = analogRead(SENSORS_PINS[i]);
  }
}

void calibrate() {
  Serial.println("Start calibrate.");
  
  const uint16_t TIMES_TO_CHECK = 500;
  uint32_t sum_sensors_value[NUM_OF_SENSORS] = { 0 };

  for (uint16_t i = 0; i < TIMES_TO_CHECK; ++i)
  {
      read_sensors_data();
      for (uint8_t index_sensor = 0; index_sensor < NUM_OF_SENSORS; ++index_sensor)
      {
          sum_sensors_value[index_sensor] += curr_sensor_data[index_sensor];
      }

      delay(2);
  }
  
  for (uint8_t index_sensor = 0; index_sensor < NUM_OF_SENSORS; ++index_sensor)
  {
    arrSensorsThreshold[index_sensor] = (sum_sensors_value[index_sensor] / TIMES_TO_CHECK) - DIFFERENCE_INDICATE_HAND;
    Serial.println("Avg of Sensor number " + (String)index_sensor + " = " + (String)(sum_sensors_value[index_sensor] / TIMES_TO_CHECK));
    Serial.println("Difference indicate hand was " + (String)DIFFERENCE_INDICATE_HAND);
    Serial.println("Threshold of Sensor number " + (String)index_sensor + " = " + (String)arrSensorsThreshold[index_sensor]);
  }

  Serial.println("End calibrate.");
}

