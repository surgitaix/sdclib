/*
 * SDC-fwd.h
 *
 *  Created on: 04.05.2015, roehser
 *  Modified on: 22.08.2019, baumeister
 *
 */

#ifndef SDCLIB_DATA_SDC_SDCFWD_H_
#define SDCLIB_DATA_SDC_SDCFWD_H_

#include "MDIB/MDIB-fwd.h"

namespace SDCLib
{
	class SDCInstance;
	class SDCLibrary;

	namespace Config
	{
		class NetworkConfig;
		class SDCConfig;
		class SSLConfig;
	}
	namespace Data
	{
		namespace SDC
		{
			class AsyncProviderInvoker;

			class FutureInvocationState;
			class SDCConsumer;
			class SDCConsumerAdapter;
			class SDCConsumerConnectionLostHandler;
			template<class T> class SDCConsumerMDStateHandler;
			class SDCConsumerOperationInvokedHandler;
			class SDCConsumerSubscriptionLostHandler;
			class SDCProvider;
			class SDCProviderActivateOperationHandler;
			class SDCProviderAdapter;
			template<class T> class SDCProviderAlertConditionStateHandler;
			template<class T> class SDCProviderComponentStateHandler;
			template<class T> class SDCProviderMDStateHandler;
			class SDCProviderStateHandler;

			class SDCConsumerSystemContextStateChangedHandler; // Unused?
		}
	}

	namespace Dev
	{
		class DeviceCharacteristics;
	}

	namespace Util
	{
		class DebugOut;
		class Task;
	}
}


#endif
