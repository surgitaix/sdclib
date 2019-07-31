/*
 * CallbackMap.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#include <CallbackMap.h>

void CallbackMap::setCallback(const std::string& callbackName, Callback callback)
{
	map[callbackName] = callback;
}

CallbackMap::Error CallbackMap::call(const std::string& callbackName, const std::string& args)
{
	auto iter = map.find(callbackName);
	if (iter == map.end()) {
		return CALLBACK_NOT_FOUND;
	}

	bool success = iter->second(args);
	if (!success) {
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

template <class T1>
Callback CallbackMap::defineCallback(std::function<void(T1)> func)
{
	Callback f = [func](const std::string& args) {
		T1 v1;
		std::stringstream sstream;
		sstream << args;
		sstream >> v1;
		if (sstream.fail()) {
			return false;
		}
		func(v1);
		return true;
	};
	return f;
}

template <class T1, class T2>
Callback CallbackMap::defineCallback(std::function<void(T1,T2)> func)
{
	Callback f = [func](const std::string& args) {
		T1 v1;
		T2 v2;
		std::stringstream sstream;
		sstream << args;
		sstream >> v1 >> v2;
		if (sstream.fail()) {
			return false;
		}
		func(v1,v2);
		return true;
	};
	return f;
}

template <class T1, class T2, class T3>
Callback CallbackMap::defineCallback(std::function<void(T1,T2,T3)> func)
{
	Callback f = [func](const std::string& args) {
		T1 v1;
		T2 v2;
		T3 v3;
		std::stringstream sstream;
		sstream << args;
		sstream >> v1 >> v2 >> v3;
		if (sstream.fail()) {
			return false;
		}
		func(v1,v2,v3);
		return true;
	};
	return f;
}
