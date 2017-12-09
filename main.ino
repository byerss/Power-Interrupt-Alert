/*
Power-Interrupt-Alert
2017 Stephen Byers
*/

boolean latched = false;
int counter = 0;
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 200;

void setup() {
  
Serial.begin(9600);
pinMode(7, INPUT_PULLUP);
pinMode(9, OUTPUT); //GREEN LED
pinMode(13, OUTPUT); //RED LED

  
}

void loop() {

unsigned long currentMillis = millis();


if (latched == true) {                //Check if ACK latched
  trap_is_clean();                    //If yes, skip main code -- LED steady green

}

else {
  
  if(digitalRead(7) == LOW){          //Button is Pressed
  digitalWrite(13, LOW);              //Turn off RED led
  counter = ++counter;                //Increment Counter for Fade-in ACK
    if(counter == 255){               //Counter Full - Do alternate Blink
      while(digitalRead(7) == LOW){   //Blink Green LED to indicate Latch while button continues to be pressed
        digitalWrite(9, LOW);
        delay(100);
        digitalWrite(9, HIGH);
        delay(100); 
      }
      latched = true;                 //Set Latch to True
      return 0;                       //Return to begining of Main Code
      }
      
  }

  if(digitalRead(7) == HIGH){         //Blink Red LED to Indicate Power Failure
    
     counter = 0;                     //Reset counter for ACK button if released before Latch

     //Standard "Blink without Delay" Example
     if (currentMillis - previousMillis >= interval) {
         previousMillis = currentMillis;   
     if (ledState == LOW) {
       ledState = HIGH;
     } else {
       ledState = LOW;
    }
    
    digitalWrite(13, ledState);       //Write LED state to blink
  }
 }
 
 analogWrite(9, counter);             //PWM Counter to Fade-in button press ACK


}
  
delay(10);                            //Give time for Fade-In

}

void trap_is_clean(){                 //Call Function to skip main code
  digitalWrite(9, HIGH);              //Green LED Steady ON
  digitalWrite(13, LOW);              //Red LED OFF
}
