#include "DispatchMessageDetour.h"
#include "detours/detours.h"
#include <ultimate/Ultimate.h>

DispatchMessageFunction DispatchMessageDetour::m_originalDispatchMessage = nullptr;

long DispatchMessageDetour::applyDetour()
{
    const auto module = GetModuleHandle(L"User32.dll");
    m_originalDispatchMessage = reinterpret_cast<DispatchMessageFunction>(GetProcAddress(module, "DispatchMessageA"));

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalDispatchMessage), hookDispatchMessage);

    std::printf("Hooked DispatchMessageA\n");

    return result;
}

long DispatchMessageDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalDispatchMessage), hookDispatchMessage);

    std::printf("Restored DispatchMessageA\n");

    return result;
}

LRESULT DispatchMessageDetour::hookDispatchMessage(MSG* message)
{
	Ultimate::m_ultimate->m_menuManager.onMessage(message);

	if (Ultimate::m_ultimate->m_menuManager.isMenuOpen()) {
		return DefWindowProcA(message->hwnd, message->message, message->wParam, message->lParam);
	}

    return m_originalDispatchMessage(message);
}
