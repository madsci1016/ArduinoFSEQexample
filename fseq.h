/*
* fseq.h - fseq file reader for ESPixelStick
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


#ifndef FSEQ_H_
#define FSEQ_H_

#include <Arduino.h>
#include <SD.h>

// header byte offsets
#define FSEQ_HEADER_SIZE        4   //uint16
#define FSEQ_VER                6   //uint16
#define FSEQ_FIXED_HEADER_SIZE  8   //uint16
#define FSEQ_NUM_CHANNELS       10  //uint32
#define FSEQ_NUM_FRAMES         14  //uint32
#define FSEQ_FRAME_PERIOD       18  //uint16  in ms? 
#define FSEQ_NUM_UNIVERSES      20  //uint16  Whats this? 
#define FSEQ_UNIVERSE_SIZE      22  //uint16  no idea


class Fseq {
 public:
    int begin(File fp);
    void close();
    int readFrame(uint8_t* buf, uint32_t frame, uint32_t start_channel, uint32_t end_channel);
    uint32_t getFrames() {return _frames;}
    uint16_t getPeriod() {return _period;}
    uint32_t getChannels() {return _channels;}
    
 private:
    File _file;                 //file pointer
    uint32_t _channels;          //channels in file
    uint32_t _frames;            //number of frames in file
    uint16_t _period;            //period for each frame in ms
    uint16_t _header_size;       //size of header. Data starts afterwords
    
  
};

#endif /* FSEQ_H_ */
