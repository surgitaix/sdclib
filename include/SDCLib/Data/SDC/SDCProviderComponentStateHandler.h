/*
 * SDCProviderComponentStateHandler.h
 *
 *  Created on: 23.01.18, buerger
 *  Modified on: 27.11.2019, baumeister
 *
 *  Use this state hander for the component related states such as MdsState, VmdState, ClockState ...
 */

#ifndef SDCPROVIDERCOMPONENTSTATEHANDLER_H_
#define SDCPROVIDERCOMPONENTSTATEHANDLER_H_

#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{
			template <class TState>
			class SDCProviderComponentStateHandler : public SDCProviderStateHandler
			{
			public:
				SDCProviderComponentStateHandler(std::string p_descriptorHandle)
				: SDCProviderStateHandler(p_descriptorHandle)
				{ }
				virtual ~SDCProviderComponentStateHandler() = default;

				/**
				* @brief the initial state has to be defined. It is needed to be called from within the framework.
				*
				* @return The initial state
				*/
				virtual TState getInitialState() = 0;
			};
		}
	}
}

#endif
