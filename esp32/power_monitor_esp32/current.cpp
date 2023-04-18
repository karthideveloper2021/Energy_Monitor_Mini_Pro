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

    float getCurrent(int sample=1000,int averageSampleCount=10){
      int sampleReadSum=0;
      float currentMean=0;
      for(int j=0;j<averageSampleCount;j++){
        for(int i=0;i<sample;i++){
          sampleReadSum+=sq(analogRead(_pin)-1820);
          delay(0.1);
        }
        currentMean+=sqrt(sampleReadSum/sample);
        sampleReadSum=0;
      }

      _currentsum=currentMean/averageSampleCount;
      _currentsum=_currentsum-_offset;

      if(_currentsum<=0.2) _currentsum=0;

      return (_currentsum * _calibrateValue);
      
    }
};