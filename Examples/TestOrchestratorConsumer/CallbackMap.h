/*
 * CallbackMap.h
 *
 *  Created on: Jul 31, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_CALLBACKMAP_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_CALLBACKMAP_H_

#include <unordered_map>
#include <functional>
#include <sstream>
#include <type_traits>
#include <iostream>
#include <list>

typedef std::function<bool(const std::string& args)> Callback;

struct functionDescription {
	std::string functionName;
	std::list<std::string> args;

	bool operator==(const functionDescription &rhs) const
	{
		return (this->functionName == rhs.functionName);
	}

};


struct hashFunction {
	std::size_t operator() (const functionDescription &funcDesc) const
	{
		std::size_t h1 = std::hash<std::string>()(funcDesc.functionName);

		return h1;
	}
};

class CallbackMap {
public:
	enum Error {
		CALLBACK_NOT_FOUND,
		CALLBACK_BAD_ARGS,
		CALLBACK_NO_ERROR
	};
//	void setCallback(const std::string& callbackName, const std::string& callbackArg, Callback callback);
	void setCallback(const std::string& callbackName, const std::list<std::string>& callbackArgs, Callback callback);
	Error call(const std::string&callbackName, const std::string& args);
	std::unordered_map<functionDescription, Callback, hashFunction> getCallbacks();

	static Callback defineCallback(std::function<void(void)> func);
	template <class T>
	static Callback defineCallback(std::function<void(T)> func);
	template <class T1, class T2>
	static Callback defineCallback(std::function<void(T1,T2)> func);
	template <class T1, class T2, class T3>
	static Callback defineCallback(std::function<void(T1,T2,T3)> func);
private:
	std::unordered_map<functionDescription, Callback, hashFunction> map;
};



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




#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_CALLBACKMAP_H_ */
