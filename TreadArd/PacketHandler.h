#ifndef PACKET_HANDLER
#define PACKET_HANDLER

#include "MotorApps.h"

// Packet Handler namespace to hold everything relavent to the Packet Handler
namespace PacketHandler
{

// All possible commands to be sent to the arudino
enum Command
{
    MOVE_FORWARD,
    MOVE_BACKWARD,
    TURN_C,         //Clockwise
    TURN_CC,        //Counter ClockWise
    STOP
};

// All Command Packets will have the following struct layout 
struct CommandPacket
{
    Command cmd;
    int data;
};

static int MAX_CMD_VAL = 3;

// Static variable to hold the current command 
static CommandPacket *CURRENT_CMD_PACKET;

// Start serial communication with Raspberry Pi
void StartSerial()
{
    // @TODO: need to check for the right baud rate for serial COM
    Serial.begin(9600);
    while(!Serial)
    {
        // Wait for serial to connect successfully
    };
}

// Retrieves the data from the Serial line and sets it to CMD_PACKET
void GetCommandPacket() 
{
    // Data is available on serial line
    if(Serial.available() >= 2 )
    {
        int cmdByte = Serial.read();
        if(cmdByte <= MAX_CMD_VAL)
        {
            CURRENT_CMD_PACKET->cmd = (Command)(cmdByte);
        }
        // Recieved command was not valid
        else
        {
            // @TODO: Handle error for invalid command
        }
        CURRENT_CMD_PACKET->data = Serial.read();
    }
    // Data is not available on serial line
    else
    {
        // @TODO: Handle error for no available data on serial line
    }
}

void RunCommand()
{
    switch(CURRENT_CMD_PACKET->cmd)
    {
        case MOVE_FORWARD:
            moveForward(CURRENT_CMD_PACKET->data);
            break;
        case MOVE_BACKWARD:
            moveBackward(CURRENT_CMD_PACKET->data);
            break;
        case TURN_C:
            turnCenterRight(CURRENT_CMD_PACKET->data);
            break;
        case TURN_CC:
            turnCenterLeft(CURRENT_CMD_PACKET->data);
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
