//Instantiate variables
int sensorValue = 0;
int lightIntensity = 0;
int pinArray[16];
boolean diagnostics = false;
boolean calibrate = false;


  
void setup() {

  // Set MIDI baud rate:
  if (diagnostics == true) {
    Serial.begin(9600);
    }
  
  else {
    Serial.begin(31250);
    }

}

void loop() {

 //Print light intensity if diagnostics is enabled
 if (diagnostics == true) {
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println(" Diagnostic Mode Enabled");
  Serial.print(" Light Intensity: ");
  Serial.println(lightIntensity);
  }

  //Initial calibration
  if (calibrate == false) {

    //Get light intensity for each sensor
    for (int i = 0; i <= 15; i++) {

      int pin = 16 + i;
      sensorValue = analogRead(pin);
  
      //Find maximum light intensity
      if (sensorValue > lightIntensity) {
  
        lightIntensity = sensorValue;
          
        }  
      //Print intensity if diagnostics enabled
      if (diagnostics == true) {

        Serial.print(" Sensor ");
        Serial.print(i);
        Serial.print(" - ");
        Serial.println(sensorValue);
        
        }
          
      }
      
    //Add 100 to brightest light intensity to avoid accidental triggers
    lightIntensity = lightIntensity + 100;
    
    }

  //Calibration complete, set variable to not run calibration loop again
  calibrate = true;

  //If ambient light is too bright, output error code
  if (lightIntensity > 900) {

    //Output error code in console if diagnostics mode is enabled
    if (diagnostics == true) {

        Serial.println(" ERROR: AMBIENT LIGHT TOO BRIGHT ");
        delay(1000);

        }

    //Beep if diagnostics mode is not enabled
    else {

      Serial.write(0x90);
      Serial.write(56);
      Serial.write(0x40);
      
      delay(1000);
      
      Serial.write(0x90);
      Serial.write(56);
      Serial.write(0x00);

      Serial.write(0x90);
      Serial.write(60);
      Serial.write(0x40);
      
      delay(1000);
      
      Serial.write(0x90);
      Serial.write(60);
      Serial.write(0x00);

      delay(1000);

    }

  }

  //Continue to normal program if light intensity is in a workable range
  else {

    //Iterate through each sensor / note
    for (int i = 0; i <= 15; i++) {     
  
      int pin = 16 + i;  
      int note = 56 + i;
  
      sensorValue = analogRead(pin);

      //Trigger if sensor is receiving more light than ambient light
      if (sensorValue > lightIntensity) {

        //Print sensor value if diagnostics is enabled
        if (diagnostics == true) {

          Serial.print(" Sensor ");
          Serial.print(i);
          Serial.print(" - ");
          Serial.print(sensorValue);
          Serial.print(" - ON");
          Serial.println("");

          }

          //Play note if diagnostics is not enabled
          else {

        //Trigger if the pin isn't already on
        if (pinArray[i] != 1) {

          //Set pin marker to "on"
          pinArray[i] = 1;
  

    
            Serial.write(0x90);
            Serial.write(note);
            Serial.write(0x40);
  
            }          
          }
        }

      //Trigger if sensor is receiving less light than ambient light
      if (sensorValue < lightIntensity) {

        //Set pin marker to "off"
        pinArray[i] = 0;

        //Print "off" if diagnostics is enabled
        if (diagnostics == true) {

          Serial.print(" Sensor ");
          Serial.print(i);
          Serial.print(" - ");
          Serial.print(sensorValue);
          Serial.println(" - OFF");

          }
      //Turn off note if diagnostics is not enabled
      else {
  
        Serial.write(0x90);
        Serial.write(note);
        Serial.write(0x00);

        }
        
      }
    }

    if (diagnostics == true) {
      delay(1000);
    }
  }

  }

  




//Old code below


  
  /*
    for (int i = 1; i <= 16; i++) {

      int pin = 15 + i;

      int note = 55 + i;

      sensorValue = analogRead(pin);

      if (sensorValue < 800) {

        Serial.write(0x90);
        Serial.write(note);
        Serial.write(0x00);
      }
    }
  */


/*
  void loop() {
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  for (int note = 0x1E; note < 0x5A; note ++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    noteOn(0x90, note, 0x45);
    delay(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    noteOn(0x90, note, 0x00);
    delay(100);
  }
  }
*/




/*
  // play notes from F#-0 (0x1E) to F#-5 (0x5A):
  for (int note = 0x38; note < 0x47; note ++) {
   //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
   noteOn(0x90, note, 0x40);
   delay(1000);
   //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
   noteOn(0x90, note, 0x00);
   delay(1000);
  }
*/



// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
/*
  void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
  }
*/
