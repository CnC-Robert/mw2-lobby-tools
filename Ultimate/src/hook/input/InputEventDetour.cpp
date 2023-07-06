#include "InputEventDetour.h"
#include "detours/detours.h"
#include "ultimate/Ultimate.h"

InputEventFunction InputEventDetour::m_originalInputEvent;

long InputEventDetour::applyDetour() {
	m_originalInputEvent = reinterpret_cast<InputEventFunction>(0x5CC9f0);

	const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalInputEvent), &hookInputEvent);

	std::printf("Hooked Input_event\n");

	return result;
}

long InputEventDetour::restoreDetour() {
	const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalInputEvent), &hookInputEvent);

	std::printf("Restored Input_event\n");

	return result;
}

LRESULT InputEventDetour::hookInputEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (Ultimate::m_ultimate->m_menuManager.isMenuOpen()) {
		return DefWindowProcA(hwnd, uMsg, wParam, lParam);
	}

	return m_originalTestFunction(hwnd, uMsg, wParam, lParam);

}