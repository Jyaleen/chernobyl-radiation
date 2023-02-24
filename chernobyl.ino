#include <Servo.h>    // use a set of functions to control the servo

int potPosition;      // keep track of the potentiometer's last value
int dataIndex;        // keep track of the index of the data item we're showing
int servoPosition;    // keep track of where the servo is

Servo myservo;        // make a servo helper object
int SERVO_PIN = 13;    // the phyiscal pin we'll attach the servo to

int data[] = {1,10,10,10,1,2,4,5,10,10,0}; // an array of made up data

double aggregatedData[] = {9.852796,6.855303,7.234724,10.773426,9.701829,11.363028,13.39248,9.623236,11.371501,11.314882,9.728632,11.199826,11.710206,9.504857,12.336706,17.476913,27.59828,16.020846,5.449925,2.127477,0.957039,2.171908,2.415295,1.682476,2.035357,2.739566,10.985739,10.192993,4.047097,1.74779,1.477822,0.970949,1.0445,0.910622,1.030643,1.25812,1.016698,0.904859,0.906648,0.848654,1.157445,0.88981,0.376864,0.05797,0.04926,0.041158,0.038884,0.03247,0.016764,0.015121,0.014517,0.016948};

// return the number of items in the array
int data_array_length() {
  // number of buyes in the array / number of bytes in the first item
  return sizeof(data) / sizeof(data[0]);
}

// figure out the biggest value in the array
int max_data_value() {
  // start by comparing to first item in array
  int maxVal = data[0];
  // now check each item in the array
  for (int i = 0; i < data_array_length(); i++) {
    // remember it if it it bigger than the current biggest value
    maxVal = max(data[i], maxVal);
  }
  // return the biggest value
  return maxVal;
}

// this is run once, when the board is reset
void setup() {
  myservo.attach(SERVO_PIN);  // attach the servo so we can send it commeands
}

// this is run over and over again forever
void loop() {
  // first read the potiometer via the analog pin 0 - returns a value between 0 and 1023 based on the voltage
  potPosition = analogRead(A0);

  // translate the potiometer to a data index (between 0 and the length of the data array)
  dataIndex = map(potPosition, 0, 1023, 0, data_array_length());

  // translate the data at the selected index into an array position
  servoPosition = map(data[dataIndex], 0, max_data_value(), 20, 160);

  // move the potiometer to the new position
  myservo.write(servoPosition);
}
