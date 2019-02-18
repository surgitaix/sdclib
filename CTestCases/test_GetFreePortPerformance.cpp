/*
 * test_GetFreePortPerformance.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: sebastian
 */

#include <chrono>
#include <iostream>

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/ServerSocket.h"

bool isLocalPortFree(int port) {
    try {
    	Poco::Net::ServerSocket(port).close();
        return true;
    } catch (...) {
        return false;
    }
}

int nextFreePort() {
   	for (int i = 14000; i < 15000; i++) {
   		isLocalPortFree(i+1);
   		//isLocalPortFree(i+2);
   		if (isLocalPortFree(i)) {
   			return i;
		}
   	}
}


int main() {

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	unsigned short portNumber = 0;
	for (int i = 0; i < 15000; i++) {
		nextFreePort();
	}

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << duration;
    return 0;

}

