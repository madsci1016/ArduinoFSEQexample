/*
* fseq.cpp - fseq file reader for ESPixelStick
*
* Project: ESPixelStick - An ESP8266 and E1.31 based pixel driver
* Copyright (c) 2015 Shelby Merrick
* http://www.forkineye.com
*
* Fseq code by Bill Porter
*   http://www.billporter.info  
*
*  This program is provided free for you to use in any way that you wish,
*  subject to the laws and regulations where you are using it.  Due diligence
*  is strongly suggested before using this code.  Please give credit where due.
*
*  The Author makes no warranty of any kind, express or implied, with regard
*  to this program or the documentation contained in this document.  The
*  Author shall not be liable in any event for incidental or consequential
*  damages in connection with, or arising out of, the furnishing, performance
*  or use of these programs.
*
*/


#include "fseq.h"

uint8_t fileid[]="PSEQ";

//open file, parse header
int Fseq::begin(File fp){
  
  _file = fp;
  
  //check for vaild fseq file. Frist 4 bytes should be 'FSEQ'
  for(int i=0; i<4; i++){
    if(_file.read() != fileid[i])
      return false;
  }
  
  //read header size
  _file.seek(FSEQ_HEADER_SIZE);
  _header_size = _file.read();
  _header_size += ((uint16_t)_file.read() << 8);
  
  //read number of channels
  _file.seek(FSEQ_NUM_CHANNELS);
  _channels = _file.read();
  _channels += ((uint32_t)_file.read() << 8);
  _channels += ((uint32_t)_file.read() << 16);
  _channels += ((uint32_t)_file.read() << 24);
  
  //read number of frames
  _file.seek(FSEQ_NUM_FRAMES);
  _frames = _file.read();
  _frames += ((uint32_t)_file.read() << 8);
  _frames += ((uint32_t)_file.read() << 16);
  _frames += ((uint32_t)_file.read() << 24);
  
  //read frame period in ms
  _file.seek(FSEQ_FRAME_PERIOD);
  _period = _file.read();
  _period += (_file.read() << 8);
  
  return true;
  
}

//close file
void Fseq::close(){
  
  //not sure if i need this
  
  
}

//return a buffer of all the channels of said frame
//1 frame index, so frame 1 is the first frame
//1 channel index, so 1 is the first channel
int Fseq::readFrame(uint8_t* buf, uint32_t frame, uint32_t start_channel, uint32_t end_channel){
   
  //see if frame is out of bounds. 
  if(frame >= _frames)
    return false;
  
  //calcualte file offset for frame number and seek
  _file.seek(_header_size + ((frame - 1) * _channels) + (start_channel - 1));
  
  //pull buffer from file
  if(!_file.read(buf, ((end_channel-start_channel)+1)))
    return false;
  
  return true;
  
}