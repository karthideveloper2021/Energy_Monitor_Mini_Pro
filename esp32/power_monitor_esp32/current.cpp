#include "math.h"
#include "arduino.h"

class Current{
  float _offset=0;
  float _currentsum;
  int _pin;
  float _calibrateValue;

  public:
  
    void calibrate(int pin,float offset,float calibrateValue){
      this->_offset=offset;
      this->_pin=pin;
      this->_calibrateValue=calibrateValue;

      

    }

    // float getCurrent(int sample=1000,int averageSampleCount=10){
    //   int sampleReadSum=0;
    //   float currentMean=0;
    //   for(int j=0;j<averageSampleCount;j++){
    //     for(int i=0;i<sample;i++){
    //       sampleReadSum+=sq(analogRead(_pin)-2482); //1820     //2482=>2*4096/3.3
    //     }
    //     currentMean+=sqrt(sampleReadSum/sample);
    //     sampleReadSum=0;
    //   }

    //   _currentsum=currentMean/averageSampleCount;
    //   _currentsum=(_currentsum+2482)*3.3/4096;
    //   // _currentsum=_currentsum-;
    //   // _currentsum=_currentsum-_offset;


    //   return (_currentsum * 5/2.65);
      
    // }

  
    float getCurrent(int sample=1000,int averageSampleCount=10){
      int Imax=0;
      int Imin=100000;
      int sampleRead;
      float averageCurrent=0;
      for(int j=0;j<averageSampleCount;j++){
        for(int i=0;i<sample;i++){
          sampleRead=analogRead(_pin);
          if(sampleRead>=Imax) Imax=(Imax+sampleRead)/2;
          if(sampleRead<=Imin) Imin=(Imin+sampleRead)/2;
          delay(0.1);
        }
        averageCurrent+=(Imax-Imin)/2481.0;
        Imax=0;
        Imin=100000;
      }

      _currentsum=averageCurrent/averageSampleCount;
      _currentsum=_currentsum-_offset;
      _currentsum=_currentsum *5* _calibrateValue;

      if(_currentsum<=0.05) _currentsum=0;

      // float sensor;
      // float A_read=0;
      // float val=0;
      // for(int i=0;i<100;i++){
      //   val+=analogRead(_pin);
      // }
      // A_read=val/100.0;
      // sensor=A_read*(3.3/4095.0);
      // return (sensor-1.65);
      return _currentsum;
      
    }
    
};