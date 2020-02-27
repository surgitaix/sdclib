/*
 * SerialConnectionEventHandler.h
 *
 *  Created on: Jun 18, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTIONEVENTHANDLER_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTIONEVENTHANDLER_H_

#include <atomic>

#include "SerialConnection.h"

namespace Serial {

class SerialConnectionEventHandler : public SerialConnection{
public:
	SerialConnectionEventHandler(const std::string& p_port, unsigned p_baud_rate);
	virtual ~SerialConnectionEventHandler();

	int getSpo2();
	int getPulseRate();
	bool fingerIsOut();

protected:
    void onConnected() override;
    void onDisconnected() override;
    void onSent(const uint8_t* p_data, size_t p_size) override;
    void onReceived(const uint8_t* p_data, size_t p_size) override;
    void onError(const std::string& p_category, const std::string& p_message) override;

private:
    bool m_fingerOut{false};
    int m_spo2{0};
    int m_pulseRate{0};
    int m_dataPackage{0};

};

} /* namespace Serial */

#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_SERIALCONNECTIONEVENTHANDLER_H_ */
