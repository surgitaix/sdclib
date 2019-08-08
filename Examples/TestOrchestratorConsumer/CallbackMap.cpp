/*
 * CallbackMap.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#include <CallbackMap.h>



//void CallbackMap::setCallback(const std::string& callbackName, const std::string& callbackArg, Callback callback)
//{
//	functionDescription funcDesc;
//	funcDesc.functionName = callbackName;
//	funcDesc.args.push_back(callbackArg);
//	map[funcDesc] = callback;
//}

void CallbackMap::setCallback(const std::string& callbackName, const std::list<std::string>& callbackArgs, Callback callback)
{
	functionDescription funcDesc;
	funcDesc.functionName = callbackName;
	funcDesc.args = (callbackArgs);
	map[funcDesc] = callback;

}

CallbackMap::Error CallbackMap::call(const std::string& callbackName, const std::string& args)
{
	functionDescription funcDesc;
	funcDesc.functionName = callbackName;
	auto iter = map.find(funcDesc);
	if (iter == map.end()) {
		std::cout << "CALLBACK_NOT_FOUND" << std::endl;
		return CALLBACK_NOT_FOUND;
	}

	bool success = iter->second(args);
	if (!success) {
		std::cout << "CALLBACK_BAD_ARGS" << std::endl;
		return CALLBACK_BAD_ARGS;
	}

	return CALLBACK_NO_ERROR;
}

Callback CallbackMap::defineCallback(std::function<void(void)> func)
{
	auto f = [func](const std::string& args) {
		func();
		return true;
	};
	return f;
}

std::unordered_map<functionDescription, Callback, hashFunction> CallbackMap::getCallbacks()
{
	return map;
}
