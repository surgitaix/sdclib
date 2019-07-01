/*
 * SerialConnectionEventHandler.h
 *
 *  Created on: Jun 18, 2019
 *      Author: sebastian
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTIONEVENTHANDLER_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTIONEVENTHANDLER_H_

#include "SerialConnection.h"

namespace Serial {

class SerialConnectionEventHandler : public SerialConnection{
public:
	SerialConnectionEventHandler(const std::string& port, unsigned baud_rate);
	virtual ~SerialConnectionEventHandler();

	int getSpo2();
	int getPulseRate();

protected:
    void onConnected() override;
    void onDisconnected() override;
    void onSent(const void* data, size_t size) override;
    void onReceived(const void* data, size_t size) override;
    void onError(const std::string& category, const std::string& message) override;

private:
    int spo2;
    int pulseRate;
    int dataPackage;

};

} /* namespace Serial */

#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTIONEVENTHANDLER_H_ */
