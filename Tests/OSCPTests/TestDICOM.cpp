
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/MDIB/Base64Binary.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMDeviceDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkAE.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMNetworkConnection.h"
#include "OSCLib/Data/OSCP/MDIB/DICOMTransferCapability.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace DICOMOSCP {

const std::string DEVICE_ENDPOINT_REFERENCE("EPR_DICOM_GATEWAY");
const std::string MDS_HANDLE("dicom_mds");

class OSCPHoldingDeviceProvider {
public:

    OSCPHoldingDeviceProvider() : oscpProvider() {
    	oscpProvider.setEndpointReference(DEVICE_ENDPOINT_REFERENCE);

    	std::vector<char> fakeCert;
    	fakeCert.push_back('a');
    	fakeCert.push_back('b');
    	fakeCert.push_back('c');
    	fakeCert.push_back('x');

    	dicomDescriptor
			.setHandle(MDS_HANDLE)
			.setType(CodedValue()
                .setCodingSystemId("OR.NET.Codings")
        		.setCodeId("MDCX_CODE_ID_DICOM_GATEWAY"))
			.addNetworkConnection(
					DICOMNetworkConnection()
					.setid("connection_1")
					.setHostname("127.0.0.1"))
			.addNetworkAE(DICOMNetworkAE()
					.setAETitle("AE Title")
					.addNetworkConnectionReference("connection_1")
					.setAssociationAcceptor(true)
					.setAssociationInitiator(false)
					.addTransferCapability(DICOMTransferCapability()
							.setSOPClass("undfined SOP class")
							.setTransferRole(DICOMTransferRole::SCP)
							.addTransferSyntax("unknown syntax"))
					)
			.addPublicCertificate(
					Base64Binary().
					setData(fakeCert));

    	MDDescription holdingDeviceDescription;
    	holdingDeviceDescription.addMDSDescriptor(dicomDescriptor);

    	// set the providers description
    	oscpProvider.setMDDescription(holdingDeviceDescription);

    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }



private:
    // Provider object
    OSCPProvider oscpProvider;

    // The current weight
    DICOMDeviceDescriptor dicomDescriptor;
};

}
}
}

struct FixtureDICOMOSCP : Tests::AbstractOSCLibFixture {
	FixtureDICOMOSCP() : AbstractOSCLibFixture("FixtureDICOMOSCP", OSELib::LogLevel::NOTICE, 9050) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureDICOMOSCP, dicomoscp)
{
	try
	{
        // Provider
        Tests::DICOMOSCP::OSCPHoldingDeviceProvider provider;
        provider.startup();    

        // Consumer
        OSELib::OSCP::ServiceManager oscpsm;
        std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(Tests::DICOMOSCP::DEVICE_ENDPOINT_REFERENCE));

        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

		if (c != nullptr) {
			OSCPConsumer & consumer = *c;
            // MDIB test
            MDIBContainer mdib(consumer.getMDIB());

            { // test access to some member of the dicom device.
            	std::vector<DICOMDeviceDescriptor> dicomDevices(mdib.getMDDescription().collectAllDICOMDeviceDescriptors());

            	CHECK_EQUAL(false, dicomDevices.empty());
            	if (!dicomDevices.empty()) {
            		DICOMDeviceDescriptor & device(dicomDevices.front());
            		const std::vector<Base64Binary> certs(device.getPublicCertificates());

            		CHECK_EQUAL(false, certs.empty());
            		if (!certs.empty()) {
            			const Base64Binary & cert(certs.front());
            			const std::vector<char> certData(cert.getData());

            			CHECK_EQUAL(std::size_t(4), certData.size());
            			if (certData.size() == 4) {
            				CHECK_EQUAL('a', certData.at(0));
            				CHECK_EQUAL('b', certData.at(1));
            				CHECK_EQUAL('c', certData.at(2));
            				CHECK_EQUAL('x', certData.at(3));
            			}
            		}
            	}
            }

            // Run for some time
    		Poco::Thread::sleep(10000);

            DebugOut(DebugOut::Default, "dicomoscp") << "Finished...";
            
            consumer.disconnect();
		}

        Poco::Thread::sleep(2000);
        provider.shutdown();
    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, "dicomoscp") << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, "dicomoscp") << "Unknown exception occurred!";
	}
}
}
