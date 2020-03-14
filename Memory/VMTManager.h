#pragma once

#include <Windows.h>
#include <map>

class VMTManager {
public:
	VMTManager(void** table);

	bool Hook(int index, void(__stdcall* function)(__int64, int));

	template<class T, class T1>
	bool Hook(int index, T(*function)(__int64, T1));

	bool UnHook(int index);

private:
	void** aTable;
	std::map<int, void*> aOriginals;

	bool IsHooked(int index);
};