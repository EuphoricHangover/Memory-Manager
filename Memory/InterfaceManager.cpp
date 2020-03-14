#include "InterfaceManager.h"

template<typename T>
InterfaceManager<T>::InterfaceManager(T* pClass) {
	members = pClass;
	vmt = new VMTManager(*(void***)pClass);
}