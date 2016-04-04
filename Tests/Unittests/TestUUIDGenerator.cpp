/*
 * TestUuidGenerator.cpp
 *
 *  Created on: 20.02.2013
 *      Author: roehser
 */

#include "OSCLib/OSCL.h"
#include "../UnitTest++/src/UnitTest++.h"

using namespace OSCLib;

SUITE(Basics) {
	TEST(uuidgenerator) {
		Util::DebugOut(Util::DebugOut::Default, "UUID Generator")  << "Testing UUID generator ..." << std::endl;
		{
			std::set<std::string> uuids;
			const size_t sampleValues = 5000;

			// Checking for duplicates in the output of one uuid generator.
			{
				Util::DefaultUUIDGenerator * generator = new Util::DefaultUUIDGenerator();

				for (size_t i = 0; i < sampleValues; i++) {
					uuids.insert(generator->getUUID());
				}

				CHECK_EQUAL(sampleValues, uuids.size());

				delete generator;
			}

			// Recreate uuid generator and check if new uuids are also unique.
			// Additionally the uuids from the test above mustn't repeat
			{
				Util::DefaultUUIDGenerator * generator = new Util::DefaultUUIDGenerator();

				for (size_t i = 0; i < sampleValues; i++) {
					uuids.insert(generator->getUUID());
				}

				CHECK_EQUAL( 2 * sampleValues, uuids.size());

				delete generator;
			}

			// Checking for duplicates in the output of one uuid generator.
			// Additionally the uuids from the tests above mustn't repeat
			{
				Util::DefaultUUIDGenerator * generator1 = new Util::DefaultUUIDGenerator();
				Util::DefaultUUIDGenerator * generator2 = new Util::DefaultUUIDGenerator();
				for (size_t i = 0; i < sampleValues; i++) {
					uuids.insert(generator1->getUUID());
					uuids.insert(generator2->getUUID());
				}

				CHECK_EQUAL( 4 * sampleValues, uuids.size());

				delete generator1;
				delete generator2;
			}
		}
	}
}
