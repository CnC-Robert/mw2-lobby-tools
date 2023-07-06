#pragma once

#include "../detour.h"

using InputEventFunction = LRESULT(*)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class InputEventDetour : public Detour {
public:
	static InputEventFunction m_originalInputEvent;

	long applyDetour() override;
	long restoreDetour() override;

	static LRESULT hookInputEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};