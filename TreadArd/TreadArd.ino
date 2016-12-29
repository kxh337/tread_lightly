#include "PacketHandler.h"
#include "MotorApps.h"
#include "UltraSonic.h"

void setup(){
  	motorInit();
    PacketHandler::StartSerial();    
}

void loop(){
     PacketHandler::GetCommandPacket();
     PacketHandler::RunCommand();
}


