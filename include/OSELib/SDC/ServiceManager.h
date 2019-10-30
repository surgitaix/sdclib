/*
 * ServiceManager.h
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_SERVICEMANAGER_H_
#define OSELIB_SDC_SERVICEMANAGER_H_


#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"
#include "SDCLib/Prerequisites.h"

namespace OSELib
{
	namespace SDC
	{
		class HelloReceivedHandler {
		public:
			HelloReceivedHandler() = default;
			virtual ~HelloReceivedHandler() = default;

			virtual void helloReceived(const std::string & epr);
		};

		class ServiceManager final: public OSELib::Helper::WithLogger
		{

		private:

			mutable std::mutex m_mutex;

			SDCLib::SDCInstance_shared_ptr m_SDCInstance = nullptr;
			std::unique_ptr<DPWS::MDPWSDiscoveryClientAdapter> m_dpwsClient;

			std::unique_ptr<DPWS::HelloCallback> m_helloCallback;


		public:

			ServiceManager(SDCLib::SDCInstance_shared_ptr p_SDCInstance);
			// Special Member Functions
			ServiceManager(const ServiceManager& p_obj) = delete;
			ServiceManager(ServiceManager&& p_obj) = delete;
			ServiceManager& operator=(const ServiceManager& p_obj) = delete;
			ServiceManager& operator=(ServiceManager&& p_obj) = delete;
			~ServiceManager();

			/**
			* @brief Set a handler that will be called when device send DPWS hello.
			*
			* @param handler The handler
			*/
			void setHelloReceivedHandler(HelloReceivedHandler * p_handler);

			/**
			* @brief Create a consumer and connect to Xaddr.
			*
			* @param p_xaddr The address
			* @return The consumer or nullptr
			*/
			std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> connect(const std::string & p_xaddr);

			/**
			* @brief Create a consumer and try to discover provider using endpointreference (EPR).
			*
			* @param p_epr The endpointreference
			* @return The consumer or null
			*/
			std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> discoverEndpointReference(const std::string & p_epr);

			/**
			* @brief Discover all SDC providers currently available
			*
			* @return List of all providers
			*/
			using DiscoverResults = std::vector<std::unique_ptr<SDCLib::Data::SDC::SDCConsumer>>;
			DiscoverResults discover();

			/**
			 * @deprecated Discover all SDC providers currently available in an async manner
			 *
			 * @return std::future of a list of all providers (DiscoverResults)
			 */
			using AsyncDiscoverResults = std::future<DiscoverResults>;
			AsyncDiscoverResults async_discover();

		private:

			std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> connectXAddress(const SDCLib::StringVector& pl_xAddresses, const std::string & p_epr);
			bool resolveServiceURIsFromMetadata(const WS::MEX::MetadataSection & p_metadata, OSELib::DPWS::DeviceDescription & p_deviceDescription);
		};

	}
}

#endif
