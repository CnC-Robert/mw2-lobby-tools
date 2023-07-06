#include "KeyboardPressDetour.h"
#include "detours/detours.h"

KeyboardPressFunction KeyboardPressDetour::m_originalKeyboardPress;

long KeyboardPressDetour::applyDetour() {
	m_originalKeyboardPress = reinterpret_cast<KeyboardPressFunction>(0x5CC660);

	const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalKeyboardPress), &hookKeyboardPress);

	std::printf("Hooked Keyboard_press\n");

	return result;
}

long KeyboardPressDetour::restoreDetour() {
	const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalKeyboardPress), &hookKeyboardPress);

	std::printf("Restored Keyboard_press\n");

	return result;
}

LRESULT KeyboardPressDetour::hookKeyboardPress(int param_1, WPARAM param_2, int *param_3) {
	LRESULT result;

	result = CallNextHookEx((HHOOK)0x0, param_1, param_2, (LPARAM)param_3);

	return result;
}