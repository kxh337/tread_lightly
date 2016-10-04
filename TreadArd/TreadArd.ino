#include "PacketHandler.h"
#include "MotorApps.h"

void setup(){
  	motorInit();
    PacketHandler::StartSerial();    
}

void loop(){
     PacketHandler::GetCommandPacket();
     PacketHandler::RunCommand();
}
