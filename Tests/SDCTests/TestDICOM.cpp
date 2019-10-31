
#include <thread>

#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/DicomDeviceDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/DicomNetworkAe.h"
#include "SDCLib/Data/SDC/MDIB/DicomNetworkConnection.h"
#include "SDCLib/Data/SDC/MDIB/DicomTransferCapability.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"
#include "../AbstractSDCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace SDCLib {
namespace Tests {
namespace DICOMSDC {

const std::string DEVICE_ENDPOINT_REFERENCE("EPR_DICOM_GATEWAY");
const std::string MDS_HANDLE("dicom_mds");

class SDCHoldingDeviceProvider {
public:

    SDCHoldingDeviceProvider() : sdcProvider(), dicomDescriptor(MDS_HANDLE) {
    	sdcProvider.setEndpointReference(DEVICE_ENDPOINT_REFERENCE);

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
    	sdcProvider.setMdDescription(holdingDeviceDescription);

    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }



private:
    // Provider object
    SDCProvider sdcProvider;

    // The current weight
    DicomDeviceDescriptor dicomDescriptor;
};

}
}
}

struct FixtureDICOMSDC : Tests::AbstractSDCLibFixture {
	FixtureDICOMSDC() : AbstractSDCLibFixture("FixtureDICOMSDC", OSELib::LogLevel::Notice, SDCLib::Config::SDC_ALLOWED_PORT_START + 20) {}
};

SUITE(SDC) {
TEST_FIXTURE(FixtureDICOMSDC, dicomSDC)
{
	try
	{
        // Provider
        Tests::DICOMSDC::SDCHoldingDeviceProvider provider;
        provider.start();
        provider.startup();

        // Consumer
        OSELib::SDC::ServiceManager t_serviceManager;
        std::shared_ptr<SDCConsumer> c(t_serviceManager.discoverEndpointReference(Tests::DICOMSDC::DEVICE_ENDPOINT_REFERENCE));

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
    		std::this_thread::sleep_for(std::chrono::milliseconds(10000));

            DebugOut(DebugOut::Default, "dicomSDC") << "Finished...";
            consumer.disconnect();
		}

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        provider.shutdown();
    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, "dicomSDC") << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, "dicomSDC") << "Unknown exception occurred!";
	}
}
}
