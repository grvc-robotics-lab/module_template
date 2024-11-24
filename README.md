# module_template
Project template for creating C++ software modules relying on UDP socket communications

# Description

This project is a C++ program template intended to facilitate the communication of software modules interfaced through the ModuleInterface class, relying on UDP sockets and C-style structures used as data packets for sending requests and messages from/to other software modules or a program manager.

A software module is defined here as a program intended to conduct a particular task or providing a specific functionality of service. A software module may send or receive data to/from other software modules or to/from a program manager that coordinates the execution of a complex system like a robot.

The ModuleInterface class provides two basic services: sending messages, and receiving messages. These messages may be requests for doing something, or data required by other module to conduct a task. For example, one module can be used to provide the grasping points obtained from a perception method for the control program of one robotic arm.

The user needs to specify three parameters when creating the module interface: the IP address of the end point of the communication (for example, another module or an operation manager), the UDP port for transmitting the data to the specified IP address, and a UDP port for receiving the data from any source.

This project template is intended to be customized according to user's requirements. The data apcket has been designed to be as general as possible for implementing diverse services. The developer should provide the correct interpretation and use of fields like the message code or message option.

# About data packets

Data packets are the information units interchanged by software modules. These are implemented as C/C++ style data structures within the ModuleInterface.h file. The data structure (packet) is DATA_PACKET_MODULE_MSG. It includes the following fields:
	(1) Three bytes (characters) header for recognizing the type of data packet.
	(2) One byte for the ID of the module.
	(3) One byte for the ID of the remote host that sends/receives the message.
	(4) One byte indicating the code of the message, whose meaning is defined by the user.
	(5) One byte indicating the option of the message, whose meaning is defined by the user.
	(6) A data buffer of MAX_SIZE_USER_BUFFER bytes that can be used to attach user data.
	(7) Two bytes (uint16_t) indicating the length in bytes of the user buffer.
	(8) A checksum byte corresponding to the XOR operation over the bytes from filed (2) to last byte of field (7). 
	
This data packet is intended to be generic and customizable according to user needs.

It is very important to include the modifier __attribute__((packed)) in the definition of the structure to avoid zero padding, which may affect the size of the packet and prevent correct communication.


# Requirements

No particular library is required, only standard C/C++ libraries and the cmake tool for compiling.

The ModuleTemplate project is intended to be easily integrated in any Linux system, removing any dependency from non standard libraries.


# Installation

Download or clone the project in your desired folder. Create a build folder (mkdir build), go inside the folder (cd build), generate compilation files (cmake ..) and compile (make). The executable can be fund in the buil/Main folder.


# Usage

To run the module, it is necessary to provide as input arguments the IP address of the destination module or program manager, the UDP port for sending data, and the UDP port for receiving the data. Example:

./ModuleTemplate 192.168.0.43 33001 34001

IMPORTANT: if your software module sends data through the UDP Tx port 33001 (for example), the UDP port on the reception side will be 33001; if your module receives data through the UDP Rx port 34001, the sender should employ the same Tx port. 

ADVICE: define a UDP Ports table to ensure the communications between the different software modules in your application are correctly linked.

# Customization

This software is designed to be customized as required by the project. It is important to ensure that the data structure representing the data packet sent/received is exactly the same in for both sender and receiver. Otherwise, messages/requests will not be correctly interchanged.


# Contact

This sofware has been developed by Alejandro Suarez (asuarezfm@us.es) from the GRVC Robotics Lab of the University of Seville (Spain). Please, cite or include link of this repository in your publications.


# Disclaimer

This open-source software comes with absolutely no warranty. 
