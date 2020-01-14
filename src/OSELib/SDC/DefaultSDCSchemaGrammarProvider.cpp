/*
 * DefaultSDCSchemaGrammarProvider.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/Schema/Schema.h"


namespace OSELib {
namespace SDC {

DefaultSDCSchemaGrammarProvider::DefaultSDCSchemaGrammarProvider()
: OSELib::Helper::WithLogger(Log::SCHEMA)
{

	auto addSchemaWithErrorHandling([this](const std::string & p_name, const std::string & p_schema) {
		if (!addSchema(p_name, p_schema)) {
			log_error([&]{ return "Error loading schema: " + p_name + "\n" + p_schema; });
		}
	});

	// Note: The order matters here! The schemas must included in the same order they are used within other schemas.

	addSchemaWithErrorHandling(SCHEMA::SCHEMA_EXTENSIONPOINT_NAME, SCHEMA::SCHEMA_EXTENSIONPOINT_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_BICEPS_PARTICIPANTMODEL_NAME, SCHEMA::SCHEMA_BICEPS_PARTICIPANTMODEL_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_NAME, SCHEMA::SCHEMA_BICEPS_MESSAGEMODEL_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_DICOM_DATAMODEL_NAME, SCHEMA::SCHEMA_DICOM_DATAMODEL_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_WSADDRESSING_NAME, SCHEMA::SCHEMA_WSADDRESSING_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_WSEVENTING_NAME, SCHEMA::SCHEMA_WSEVENTING_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_SOAPMESSAGE_NAME, SCHEMA::SCHEMA_SOAPMESSAGE_CONTENT);
    addSchemaWithErrorHandling(SCHEMA::SCHEMA_WSDISCOVERY_NAME, SCHEMA::SCHEMA_WSDISCOVERY_CONTENT);
	seal();
}

}
}
