#ifndef PACKET_HANDLER
#define PACKET_HANDLER

#include "MotorApps.h"

// Packet Handler namespace to hold everything relavent to the Packet Handler
namespace PacketHandler
{

// All possible commands to be sent to the arudino
enum Command
{
    MOVE_FORWARD = 0U,
    MOVE_BACKWARD = 1U,
    TURN_C = 2U,         //Clockwise
    TURN_CC = 3U,        //Counter ClockWise
    STOP = 4U
};


static Command PACKET_COMMAND;
static int COMMAND_DATA;
static int MAX_CMD_VAL = 3;

// Start serial communication with Raspberry Pi
void StartSerial()
{
    // @TODO: need to check for the right baud rate for serial COM
    Serial.begin(9600);
    while(!Serial)
    {
        // Wait for serial to connect successfully
    };
    PACKET_COMMAND = (Command)0U;
    COMMAND_DATA = 0;
}

// Flushes the input buffer
void serialFlush()
{
  while(Serial.available() > 0)
  {
    char t = Serial.read();
  }
}   


// This function is called whenever new data is recieved
void GetCommandPacket() 
{
    if(Serial.available() > 0)
    {
        int cmdByte = Serial.read();
        delay(20);
        if(cmdByte <= MAX_CMD_VAL)
        {
            PACKET_COMMAND = (Command)(cmdByte);
        }
        // Recieved command was not valid
        else
        {
            // @TODO: Handle error for invalid command
        }
        COMMAND_DATA = Serial.read();
        delay(20);
        // Flush any other data that was accidentally loaded
        serialFlush();
    }
    else
    {
      // Error case for when nothing is recieved
    }
    delay(20);
}

void RunCommand()
{
    switch(PACKET_COMMAND)
    {
        case MOVE_FORWARD:
            moveForward(COMMAND_DATA);
            break;
        case MOVE_BACKWARD:
            moveBackward(COMMAND_DATA);
            break;
        case TURN_C:
            turnCenterRight(COMMAND_DATA);
            break;
        case TURN_CC:
            turnCenterLeft(COMMAND_DATA);
            break;
        case STOP:
            motorStop();
            break;
        default:
            motorStop();
            // @TODO: throw some error?
            break;
    }
};


// Send any data back to Rasberry Pi
void SendPacket()
{
}

}

#endif
