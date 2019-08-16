/*
 * PingManager.h
 *
 *  Created on: 14.12.2015, matthias
 *  Modified on: 05.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_PINGMANAGER_H_
#define OSELIB_DPWS_PINGMANAGER_H_

#include <Poco/Thread.h>
#include <Poco/RunnableAdapter.h>

#include "SDCLib/Prerequisites.h"
#include "OSELib/fwd.h"

namespace OSELib
{
	namespace DPWS
	{
		class PingManager
		{
		private:
			Poco::Thread m_thread;
			Poco::RunnableAdapter<PingManager> m_runnableAdapter;
			SDCLib::Data::SDC::SDCConsumer & m_consumer;

		public:

			// Special Member Functions
			PingManager(SDCLib::Data::SDC::SDCConsumer & p_consumer);
			PingManager(const PingManager& p_obj) = delete;
			PingManager(PingManager&& p_obj) = delete;
			PingManager& operator=(const PingManager& p_obj) = delete;
			PingManager& operator=(PingManager&& p_obj) = delete;
			~PingManager();

			void disable();

		private:

			void run();
		};

	} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_PINGMANAGER_H_ */
