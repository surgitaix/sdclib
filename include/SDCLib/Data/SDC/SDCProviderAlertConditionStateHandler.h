/*
 * SDCProviderAlertConditionStateHandler.h
 *
 *  Created on: 26.01.2018, buerger
 *  Modified on: 27.11.2019, baumeister
 *
 *  This state handler extends alert state handlers. The sourceHasChanged method is called each time when a referenced state changes.
 *  Use it e.g. to check for defined boundaries.
 *
 */

#ifndef SDCPROVIDERALERTCONDITIONSTATEHANDLER_H_
#define SDCPROVIDERALERTCONDITIONSTATEHANDLER_H_

#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Util/DebugOut.h"

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{
			template <class TState>
			class SDCProviderAlertConditionStateHandler : public SDCProviderMDStateHandler<TState>
			{
			public:

				/**
				* @brief The constructor gets a handle as an argument referencing the regarding descriptor of the state
				*/
				SDCProviderAlertConditionStateHandler(std::string p_descriptorHandle)
				: SDCProviderMDStateHandler<TState>(p_descriptorHandle)
				{ }
				virtual ~SDCProviderAlertConditionStateHandler() = default;

				virtual void sourceHasChanged(const std::string & sourceHandle) = 0;
				virtual void alertConditionHasChanged()
				{
					SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Default, "SDCProviderAlertConditionStateHandler") << "Soon to be pure virtual function alertConditionHasChanged called." << std::endl;
				}

			};
		}
	}
}

#endif
