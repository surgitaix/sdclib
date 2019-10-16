/*
 * Command.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_COMMAND_H_
#define SOAP_COMMAND_H_

#include "OSELib/fwd.h"

namespace OSELib
{
	namespace SOAP
	{
		class Command
		{
		public:
			virtual ~Command() = default;

			virtual std::unique_ptr<MESSAGEMODEL::Envelope> Run() = 0;
		};
	}
}

#endif
