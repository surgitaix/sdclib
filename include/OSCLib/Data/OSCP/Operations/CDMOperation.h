/*
 * CDMOperation.h
 *
 *  Created on: 09.06.2015
 *      Author: roehser
 */

#ifndef OSCLIB_DATA_OSCP_OPERATIONS_CDMOPERATION_H_
#define OSCLIB_DATA_OSCP_OPERATIONS_CDMOPERATION_H_

#include "OSCLib/Data/Operation.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/FromString.h"
#include "OSCLib/Util/ToString.h"

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

template<class Traits>
class CDMOperation : public Operation {
public:
	CDMOperation(OSCPProvider & provider) :
		provider(provider)
	{
		setPortType(Traits::PortType());
		setInputAction(Traits::RequestAction());
		setOutputAction(Traits::ResponseAction());
	}

    virtual ~CDMOperation() {

    }

    Parameters invoke(Parameters & p) {
    	if (p.empty()) {
    		Util::DebugOut(Util::DebugOut::Error, Traits::RequestAction()) << "no parameter object" << std::endl;
    		throw;
    	}

        // Last parameter contains body raw content
        const Parameter & rawParam = p.back();
        if (rawParam.getType() != Parameter::Type::CDM) {
    		Util::DebugOut(Util::DebugOut::Error, Traits::RequestAction()) << "Parameter object has wrong type" << std::endl;
    		throw;
        }

        std::unique_ptr<typename Traits::Request> request(CDM::FromString::validateAndConvert<typename Traits::Request>(rawParam.getValue()));

        Parameters ret;
        if (request != nullptr) {
        	OSCLib::Data::Parameter response("CDMResponse", OSCLib::Data::Parameter::Type::CDM);
        	response.setValue(CDM::ToString::convert(Traits::dispatch(provider, *request)));
        	ret.push_back(response);
        }
        else {
        	// Error
        	OSCLib::Data::Parameter response("CDMResponse", OSCLib::Data::Parameter::Type::ERR);
        	ret.push_back(response);
        }
    	return ret;
    }

private:
	OSCPProvider & provider;
};

}
}
}

#endif /* OSCLIB_DATA_OSCP_OPERATIONS_CDMOPERATION_H_ */
