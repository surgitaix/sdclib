
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
//#include "OSCLib/Data/SDC/MDIB/Base64Binary.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/DicomNetworkAe.h"
#include "OSCLib/Data/SDC/MDIB/DicomNetworkConnection.h"
#include "OSCLib/Data/SDC/MDIB/DicomTransferCapability.h"
#include "OSCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MetaData.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::SDC;

namespace OSCLib {
namespace Tests {
namespace DICOMOSCP {

const std::string DEVICE_ENDPOINT_REFERENCE("EPR_DICOM_GATEWAY");
const std::string MDS_HANDLE("dicom_mds");

class OSCPHoldingDeviceProvider {
public:

    OSCPHoldingDeviceProvider() : oscpProvider(), dicomDescriptor(MDS_HANDLE) {
    	oscpProvider.setEndpointReference(DEVICE_ENDPOINT_REFERENCE);

    	std::vector<char> fakeCert;
    	fakeCert.push_back('a');
    	fakeCert.push_back('b');
    	fakeCert.push_back('c');
    	fakeCert.push_back('x');

    	xml_schema::Idrefs tempIdrefs;
    	tempIdrefs.push_back(xml_schema::Idref("connection_1"));
    	//tempIdrefs.push_back(xml_schema::Idref("connection_1"));
//    	asdf.push_back();
    	dicomDescriptor
			.setType(CodedValue("MDCX_CODE_ID_DICOM_GATEWAY").setCodingSystem("OR.NET.Codings"))
			.addNetworkConnection(
					DicomNetworkConnection(xml_schema::Id("dicom_network_connection_1"),"test_hostname"))
			.addNetworkAe(DicomNetworkAe("AE Title", tempIdrefs, true, false)
					.addTransferCapability(DicomTransferCapability("undfined SOP class", DicomTransferRole::Scp)
							.addTransferSyntax("unknown syntax")));
//			.addPublicCertificate(
//					Base64Binary().
//					setData(fakeCert));

    	MdDescription holdingDeviceDescription;
    	holdingDeviceDescription.addMdsDescriptor(dicomDescriptor);

    	// set the providers description
    	oscpProvider.setMdDescription(holdingDeviceDescription);

    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }



private:
    // Provider object
    SDCProvider oscpProvider;

    // The current weight
    DicomDeviceDescriptor dicomDescriptor;
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
        Tests::DICOMSDC::OSCPHoldingDeviceProvider provider;
        provider.startup();    

        // Consumer
        OSELib::SDC::ServiceManager oscpsm;
        std::shared_ptr<SDCConsumer> c(oscpsm.discoverEndpointReference(Tests::DICOMSDC::DEVICE_ENDPOINT_REFERENCE));

        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

		if (c != nullptr) {
			SDCConsumer & consumer = *c;
            // MDIB test
            MdibContainer mdib(consumer.getMdib());

            { // test access to some member of the dicom device.
            	std::vector<DicomDeviceDescriptor> dicomDevices(mdib.getMdDescription().collectAllDicomDeviceDescriptors());

            	CHECK_EQUAL(false, dicomDevices.empty());
            	if (!dicomDevices.empty()) {
            		DicomDeviceDescriptor & device(dicomDevices.front());
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
