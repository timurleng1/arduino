int sensorValue = 0;

void setup() {
  // Set MIDI baud rate:
  Serial.begin(31250);

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 16; i <= 31; i++) {
  sensorValue = analogRead(i);
 // int j = 0;

   if (sensorValue > 20) {

      Serial.write(0x90);
      Serial.write(0x38);
      Serial.write(0x40);
        
    //noteOn(0x90, 0x38, 0x40);
    //Note on channel 1 (0x90), some note value (note),  velocity (0x40):
 }
    else {
      
      Serial.write(0x90);
      Serial.write(0x38);
      Serial.write(0x00);
      }

    delay(100);
   
  }

  /*
    for (int i = 16; i < 31; i++) {
  sensorValue = analogRead(i);
  if  (sensorValue < 20) {

    noteOn(0x90, 0x38, 0x00);    
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    }
    //j++;
}
  
*/


}



// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:

/*
void noteOn(int cmd, int pitch, int velocity) {
 Serial.write(cmd);
      Serial.write(pitch);
      Serial.write(velocity);
}
*/
