//FSEQ test

#include "fseq.h"
#include <SD.h>


File fp; 
Fseq fseq;

int frame=1;

void setup(){
  Serial.begin(115200);
  
  SD.begin(4);
  
  fp = SD.open("test.fse");
   
  if(!fp)
    Serial.print("File Not Open");
  
  if(!fseq.begin(fp))
    Serial.print("fseq parse fail");
  
  Serial.print("Num Channels  ");
  Serial.println(fseq.getChannels());
  Serial.print("Num Frames  ");
  Serial.println(fseq.getFrames());
  Serial.print("Period  ");
  Serial.println(fseq.getPeriod());
  
}

void loop(){
  
  
   
  //allocate buffer to read in frames from SD card. Creatting a 10 byte buffer for this test
  uint8_t* buf = (uint8_t*)malloc(10);
  if(!buf)
    Serial.print("**** MALLOC FAILED ****");
  
  //to request a frame, pass a buffer pointer (where the data will be written too)
  // the frame number, the start channel and the end channel
  //make sure your buffer is big enough to hold that many channels
  if(!fseq.readFrame(buf, frame++, 1, 10))
    Serial.println(F("**** ERROR READING FRAME ****"));  
  
  //print out values in that frame
  for(int i =0; i<10; i++)
    Serial.println(buf[i]);
  
  free(buf);
  delay(25);
  
}