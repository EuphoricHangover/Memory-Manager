#pragma once

#include <Windows.h>
#include <map>

class VMTManager {
public:
	VMTManager(void** table) {
		aTable = table;
	}

	bool Hook(int index, void(__stdcall* function)(__int64, int)) {
		if (IsHooked(index))
			return false;

		aOriginals[index] = aTable[index];

		DWORD originalAccess;
		VirtualProtect(&aTable[index], sizeof(function), PAGE_READWRITE, &originalAccess);
		aTable[index] = function;
		VirtualProtect(&aTable[index], sizeof(function), originalAccess, &originalAccess);

		return true;
	}

	template<class T, class T1>
	bool Hook(int index, T(*function)(__int64, T1)) {
		if (IsHooked(index))
			return false;

		aOriginals[index] = aTable[index];

		DWORD originalAccess;
		VirtualProtect(&aTable[index], sizeof(function), PAGE_READWRITE, &originalAccess);
		aTable[index] = function;
		VirtualProtect(&aTable[index], sizeof(function), originalAccess, &originalAccess);

		return true;
	}

	bool UnHook(int index) {
		if (aOriginals[index] == nullptr)
			return false;

		DWORD originalAccess;
		VirtualProtect(&aTable[index], sizeof(void*), PAGE_READWRITE, &originalAccess);
		aTable[index] = aOriginals[index];
		VirtualProtect(&aTable[index], sizeof(void*), originalAccess, &originalAccess);
	}

private:
	void** aTable;
	std::map<int, void*> aOriginals;

	bool IsHooked(int index) {
		return aOriginals[index] != nullptr;
	}
};