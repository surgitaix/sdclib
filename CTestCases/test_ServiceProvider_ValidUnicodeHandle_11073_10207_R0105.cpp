/*
 * test_ServiceProvider_ValdiUnicodeHandle_11073_10207_R0105.cpp
 *
 *  Created on: Dec 5, 2018
 *      Author: rosenau
 */
/*
 * Test against requirement 11073-10207-R0105 A HANDLE SHALL consist of characters that match only valid Unicode codes greater than U+0020, except for U+FFFD (replacement character)
 */

#include <iostream>
#include <string.h>
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const std::string HANDLE_NUMERICMETRIC("handle_numericmetric");

class NumericMetricStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:
	NumericMetricStateHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

	InvocationState onStateChangeRequest(const NumericMetricState &, const OperationInvocationContext &) override {
		return InvocationState::Fail;
	}

	NumericMetricState getInitialState() override {
		NumericMetricState result(HANDLE_NUMERICMETRIC);
		return result;
	}
};

//Unicode encoding structure table. The x are replaced by the bits of the code point -> eg. U+07FF -> 1101 1111 1011 1111
//Number
//of bytes 	Bits for code point 	First code point 	Last code point 	Byte 1 		Byte 2 		Byte 3		Byte 4
//1 		7 						U+0000 				U+007F 				0xxxxxxx
//2 		11 						U+0080 				U+07FF 				110xxxxx 	10xxxxxx
//3 		16 						U+0800 				U+FFFF 				1110xxxx 	10xxxxxx 	10xxxxxx
//4 		21 						U+10000 			U+10FFFF 			11110xxx 	10xxxxxx 	10xxxxxx 	10xxxxxx

void GetUnicodeCharAsUtf8(unsigned int code, char chars[5])
{
    if (code <= 0x7F) {
        chars[0] = (code & 0x7F);
        chars[1] = '\0';
    } else if (code > 0x10FFFF) {
        throw std::invalid_argument("code out of unicode range");
    } else {
        int count;
        if (code <= 0x7FF) {
            // one continuation byte
            count = 1;
        } else if (code <= 0xFFFF) {
            // two continuation bytes
            count = 2;
        } else {
            // three continuation bytes
            count = 3;
        }
        for (int i = 0; i < count; ++i) {
            chars[count-i] = 0x80 | (code & 0x3F);
            code >>= 6;
        }
        chars[0] = (0x1E << (6-count)) | (code & (0x3F >> count));
        chars[1+count] = '\0';
    }
}



int main()
{
	std::cout << "Test against requirement 11073-10207-R0105 A HANDLE SHALL consist of characters "
			  << "that match only valid Unicode codes greater than U+0020, except for U+FFFD (replacement character)"
			  << std::endl;
	std::map<std::string, bool> testCases;

	//Unicode Symbols < U+0021 as single character and inside of a string
	for (int i = 0; i < 21; i++)
	{
		char chars[5];
		GetUnicodeCharAsUtf8(i, chars);
		testCases.insert(std::make_pair(chars, true));
		testCases.insert(std::make_pair("test" + std::string(chars) + "string", true));
	}

	//Replacement Character U+FFFD as single character and inside of a string
	testCases.insert(std::make_pair("\uFFFD", true));
	testCases.insert(std::make_pair("test" + std::string("\uFFFD") + "string", true));

	//Valid Boundary values
	testCases.insert(std::make_pair("\u0021", false));
	testCases.insert(std::make_pair("test" + std::string("\u0021") + "string", false));
	testCases.insert(std::make_pair("\uFFFC", false));
	testCases.insert(std::make_pair("test" + std::string("\uFFFC") + "string", false));
	testCases.insert(std::make_pair("\uFFFE", false));
	testCases.insert(std::make_pair("test" + std::string("\uFFFE") + "string", false));


	for(const auto& testCase : testCases)
	{
		bool exception = false;
		try {
			NumericMetricStateHandler testStateHandler(testCase.first);
		}
		catch(...)
		{
			exception = true;
		}
		if(exception != testCase.second)
		{
			std::cout << "Test failed at: " << testCase.first << std::endl;
			exit(0);
		}
	}

	std::cout << "Test passed";
}

