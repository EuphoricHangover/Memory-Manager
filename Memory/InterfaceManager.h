#pragma once

#include "VMTManager.h"

template<typename T>
class InterfaceManager {
public:
	VMTManager* vmt;
	T* members;
	InterfaceManager(T* pClass);
};