#include "MouseMoveDetour.h"
#include "ultimate/Ultimate.h"
#include <detours/detours.h>

MouseMoveFunction MouseMoveDetour::m_originalMouseEvent = nullptr;

long MouseMoveDetour::applyDetour()
{
    m_originalMouseEvent = reinterpret_cast<MouseMoveFunction>(0x4C1880);

    const auto result = DetourAttach(&reinterpret_cast<PVOID&>(m_originalMouseEvent), &hookMouseEvent);

    std::printf("Hooked CL_MouseEvent\n");

    return result;
}

long MouseMoveDetour::restoreDetour()
{
    const auto result = DetourDetach(&reinterpret_cast<PVOID&>(m_originalMouseEvent), &hookMouseEvent);

    std::printf("Restored CL_MouseEvent\n");

    return result;
}

int MouseMoveDetour::hookMouseEvent(const int x, const int y, const int dx, const int dy)
{
    if (Ultimate::m_ultimate->m_menuManager.isMenuOpen()) {
        return 0;
    }

    return m_originalMouseEvent(x, y, dx, dy);
}
