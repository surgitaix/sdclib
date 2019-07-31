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

typedef std::function<bool(const std::string& args)> Callback;

class CallbackMap {
public:
	enum Error {
		CALLBACK_NOT_FOUND,
		CALLBACK_BAD_ARGS,
		CALLBACK_NO_ERROR
	};
	void setCallback(const std::string&callbackName, Callback callback);
	Error call(const std::string&callbackName, const std::string& args);

	static Callback defineCallback(std::function<void(void)> func);
	template <class T1>
	static Callback defineCallback(std::function<void(T1)> func);
	template <class T1, class T2>
	static Callback defineCallback(std::function<void(T1,T2)> func);
	template <class T1, class T2, class T3>
	static Callback defineCallback(std::function<void(T1,T2,T3)> func);
private:
	std::unordered_map<std::string, Callback> map;
};





#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_CALLBACKMAP_H_ */
