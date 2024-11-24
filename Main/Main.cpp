/*
 * Copyright (c) 2024 Alejandro Suarez, asuarezfm@us.es
 *
 * University of Seville - Robotics, Vision and Control Group
 *
 * File name: Main.cpp
 */


// Standard library
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Specific library
#include "../ModuleInterface/ModuleInterface.h"


// Structure definition
typedef struct
{
	float pos[3];
	float quat[4];
} __attribute__((packed)) DATA_PACKET_ROBOT_POSE;



// Namespaces
using namespace std;


int main(int argc, char ** argv)
{
	int requestCode = 0;
	int requestOption = 0;
	int errorCode = 0;
	
	
	cout << endl;
	cout << "Software Module Interface - Program Template" << endl;
	cout << "Author: Alejandro Suarez, asuarezfm@us.es" << endl;
	cout << "Date: 14 November 2024" << endl;
	cout << "Organization: GRVC - University of Seville" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << endl;
	
	if(argc != 4)
	{
		errorCode = 1;
		cout << "ERROR [in Main]: invalid number of arguments." << endl;
		cout << "Specify host IP address, UDP Tx port, and UDP Rx port." << endl;
		cout << "Example: ./ModuleTemplate 192.168.0.140 34102 35102" << endl;
	}
	else
	{
		// Create the module interface, indicating module ID and name	
		ModuleInterface mi = ModuleInterface(1, "LiCAS_module");
		cout << "Module interface created" << endl;
		
		// Open the UDP interface with the host, indicating host IP, Tx port and Rx port
		mi.openUDPSocket(argv[1], atoi(argv[2]), atoi(argv[3]));
		cout << "Module interface socket opened" << endl;
		
		// Send a message to the host with code 1, option 2, and robot data
		DATA_PACKET_ROBOT_POSE dataPacketRobotPose = {0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
		int msgCode = 1;
		int msgOption = 2;
		
		// Send a data packet containing robot pose		
		mi.sendMessage(msgCode, msgOption, (uint8_t*)&dataPacketRobotPose, sizeof(dataPacketRobotPose));
		
		while(true)
		{
			// Wait for a request
			while(mi.isRequestReceived() == 0)
				usleep(100000);	// Wait 100 ms
				
			mi.getRequest(requestCode, requestOption);
			cout << "Request code: " << requestCode << endl;
			cout << "Request option: " << requestOption << endl;
			cout << "---" << endl;
			
			// Send reply message
			mi.sendMessage(msgCode, msgOption, NULL, 0);
		}
			
		// Close interface
		mi.closeInterface();
		mi.~ModuleInterface();
	}
	
	
	return errorCode;
}



