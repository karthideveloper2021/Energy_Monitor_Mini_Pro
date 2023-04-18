void process(struct deviceInfo* device){
  if(device->current>0.015 || device->voltage>200)
  {
    if (device->statusFlag){
      publishStatus(device->id,1); 
      device->statusFlag=false;
    }    
    else{
      publishData(*device);
    }

  }else{
    if(!device->statusFlag){
      publishStatus(device->id,0);
      device->statusFlag=true;
    }
  }
}