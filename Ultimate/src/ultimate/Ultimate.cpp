#include "Ultimate.h"
#include "hook/DetourManager.h"

std::shared_ptr<Ultimate> Ultimate::m_ultimate;

Ultimate::Ultimate()
    : m_hooked{ false }
{
    static_assert(sizeof(gentity_s) == 0x274);
}

void Ultimate::hook() {
    m_patchManager.applyPatches();
    m_menuManager.initializeImGui();
    g_detours.hook();
    m_hooked = true;
}

void Ultimate::unhook() {
    g_detours.unhook();
    m_menuManager.shutdownImGui();
	m_patchManager.restorePatches();
    m_hooked = false;
}
