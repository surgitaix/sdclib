/*
 * DefaultSDCSchemaGrammarProvider.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/WSDL/schema.h"


namespace OSELib {
namespace SDC {

DefaultSDCSchemaGrammarProvider::DefaultSDCSchemaGrammarProvider() : WithLogger(Log::SCHEMA) {

	auto addSchemaWithErrorHandling([this](const std::string & name, const std::string & schema) {
		if (!addSchema(name, schema)) {
			log_error([&]{ return "Error loading schema: " + name + "\n" + schema; });
		}
	});

	// Note: The order matters here! The schemas must included in the same order they are used within other schemas.

	addSchemaWithErrorHandling(SCHEMA::SCHEMA_EXTENSION_POINT_NAME, SCHEMA::SCHEMA_EXTENSION_POINT_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_DATAMODEL_NAME, SCHEMA::SCHEMA_DATAMODEL_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_MESSAGEMODEL_NAME, SCHEMA::SCHEMA_MESSAGEMODEL_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_DICOM_DATAMODEL_NAME, SCHEMA::SCHEMA_DICOM_DATAMODEL_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_WSADDRESSING_NAME, SCHEMA::SCHEMA_WSADDRESSING_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_WSEVENTING_NAME, SCHEMA::SCHEMA_WSEVENTING_CONTENT);
	addSchemaWithErrorHandling(SCHEMA::SCHEMA_SOAPMESSAGE_NAME, SCHEMA::SCHEMA_SOAPMESSAGE_CONTENT);
	seal();
}

DefaultSDCSchemaGrammarProvider::~DefaultSDCSchemaGrammarProvider() = default;

} /* namespace Helper */
} /* namespace OSELib */
