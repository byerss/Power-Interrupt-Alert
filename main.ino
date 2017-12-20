/*
Power-Interrupt-Alert
2017 Stephen Byers
*/

boolean latched = false;
int counter = 0;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 200;

int button = 5;
int greenLED = 1;
int redLED = 0;
int blueLED = 4;



void setup() {
  
Serial.begin(9600);
pinMode(button, INPUT_PULLUP);
pinMode(greenLED, OUTPUT);    //GREEN LED
pinMode(redLED, OUTPUT);      //RED LED
pinMode(blueLED, OUTPUT);     //BLUE LED
pinMode(3, OUTPUT);           //GND for Button
digitalWrite(3, LOW);

  
}

void loop() {

unsigned long currentMillis = millis();


if (latched == true) {                //Check if ACK latched
  trap_is_clean();                    //If yes, skip main code -- LED steady green

}

else {
  
  if(digitalRead(button) == LOW){          //Button is Pressed
  digitalWrite(redLED, LOW);              //Turn off RED led
  counter = ++counter;                //Increment Counter for Fade-in ACK
    if(counter == 255){               //Counter Full - Do alternate Blink
      while(digitalRead(button) == LOW){   //Blink Green LED to indicate Latch while button continues to be pressed
        digitalWrite(greenLED, LOW);
        delay(75);
        digitalWrite(greenLED, HIGH);
        delay(75); 
      }
      latched = true;                 //Set Latch to True
      return;                       //Return to begining of Main Code
      }
      
  }

  if(digitalRead(button) == HIGH){         //Blink Red LED to Indicate Power Failure
    
     counter = 0;                     //Reset counter for ACK button if released before Latch

     //Standard "Blink without Delay" Example
     if (currentMillis - previousMillis >= interval) {
         previousMillis = currentMillis;   
     if (ledState == LOW) {
       ledState = HIGH;
     } else {
       ledState = LOW;
    }
    
    digitalWrite(redLED, ledState);       //Write LED state to blink
  }
 }
 
 analogWrite(greenLED, counter);             //PWM Counter to Fade-in button press ACK
 //analogWrite(redLED, counter);

}
  
delay(10);                            //Give time for Fade-In

}

void trap_is_clean(){                 //Call Function to skip main code
  digitalWrite(greenLED, HIGH);              //Green LED Steady ON
  digitalWrite(redLED, LOW);              //Red LED OFF
}
