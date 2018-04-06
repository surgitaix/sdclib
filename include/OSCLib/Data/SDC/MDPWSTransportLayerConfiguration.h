/*
 * MDPWSTransportLayerConfiguration.h
 *
 *  @file MDPWSTransportLayerConfiguration.h
 *  @project SDCLib
 *  @date 04.04.18
 *  @author buerger
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef INCLUDE_OSELIB_SDC_MDPWSTRANSPORTLAYERCONFIGURATION_H_
#define INCLUDE_OSELIB_SDC_MDPWSTRANSPORTLAYERCONFIGURATION_H_

#include "Poco/Net/IPAddress.h"

namespace SDCLib {
namespace Data {
namespace SDC {

class MDPWSTransportLayerConfiguration {
public:

	/**
	* @brief Constructor initializes object with a free port
	*
	*/
	MDPWSTransportLayerConfiguration();

	/**
	* @brief Destructor frees the port (puts it back into library singleton)
	*
	*/
	~MDPWSTransportLayerConfiguration();

	/**
	* @brief Get the IP address the socket will be bound to or is bound to.
	*
	* @return the ip address to be bound to.
	*/
	Poco::Net::IPAddress getBindAddress();


    /**
    * @brief Set the IP address the socket should be bound to. Use this if more than one network adapter is installed.
    *
    * @param httpBindAddress the ip address to be bound to.
    */
	void setBindAddress(Poco::Net::IPAddress httpBindAddress);

    /**
    * @brief Get the port to bind the httpServer to
    *
    * @return The port
    */
	unsigned int getPort();

	/**
	* @brief Set the port to bind the httpServer to. By default the port is assigned automatically to a free one.
	* 			If the port shall be set a specific port, use this setting or define another port range in the
	* 			SDCLib singleton.
	*
	* @param port the port
	*/
	void setPort(unsigned int port);

private:
	Poco::Net::IPAddress m_httpBindAddress;
	unsigned int m_port;
	// set if a custom port is set. In such a case the port is not returned to the free ports list after deletion.
	bool customPortFlag;
};
} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* INCLUDE_OSELIB_SDC_MDPWSTRANSPORTLAYERCONFIGURATION_H_ */
