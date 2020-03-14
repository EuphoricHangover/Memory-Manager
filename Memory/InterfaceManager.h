#pragma once

#include "VMTManager.h"

template<typename T>
class InterfaceManager {
public:
	VirtualTable* vtable;
	T* members;
	InterfaceManager(T* pClass) {
		main = pClass;
		vtable = new VirtualTable(*(void***)pClass);
	}
};