/*
 * This code lets one share data between the arduino and a java application.
 * 
 * Author: Kristian Kvam
 */

char data; //variable to store incoming data from JAVA 

int btn = 12; // Button
int red = 8; // Red light
int green = 9; // Green light
int blue = 10; // Blue Light

int btnState = 0;
int breaker = 0;

int good = 2;
int medium = 3;
int bad = 4;
int small = 5;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(btn, INPUT);
  pinMode(good, OUTPUT);
  pinMode(medium, OUTPUT);
  pinMode(bad, OUTPUT);
  pinMode(small, OUTPUT);
  Serial.begin(345600);
  Serial.setTimeout(50);
}

void loop() {

  btnState = digitalRead(btn);
  
  if(Serial.available()>0){ //if data has been written to the Serial stream
    data=Serial.read();

    lightSource(data);
    qualitySignal(data);

  }
       // Writes "ok" to the Java application if the button is pressed.
       if(btnState == HIGH && breaker == 0){
         Serial.write("ok");
         breaker = 1;
        }

        // Resets the button state.
        if(btnState == LOW){
         breaker = 0;  
        }

}
/*
 * Sets an output high for 200ms if the input data maches any of the cases.
 * This method is used to visualize the data recieved from the Java application.
 */
void qualitySignal(int input){
    switch (input) {
    case '4':
      digitalWrite(good,HIGH);
      delay(200);
      digitalWrite(good, LOW);
      break;
    case '5':
      digitalWrite(medium,HIGH);
      delay(200);
      digitalWrite(medium, LOW);
      break;
    case '6':
      digitalWrite(bad,HIGH);
      delay(200);
      digitalWrite(bad, LOW);
      break;
    case '7':
      digitalWrite(small,HIGH);
      delay(200);
      digitalWrite(small, LOW);
      break;
    default:
      // do nothing
      break;
  }
}
/*
 * Turns on the red, green, or blue light for 500 ms depending on the input data.
 * This method is used to turn on the lights when data recieved from the Java application 
 * matches any of the cases.
 */
void lightSource(int input){
      switch (input) {
    case '1':
      digitalWrite(red,HIGH);
      delay(500);
      digitalWrite(red, LOW);
      break;
    case '2':
      digitalWrite(green,HIGH);
      delay(500);
      digitalWrite(green, LOW);
      break;
    case '3':
      digitalWrite(blue,HIGH);
      delay(500);
      digitalWrite(blue, LOW);
      break;
    default:
      // do nothing
      break;
  }
}


