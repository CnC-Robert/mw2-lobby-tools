#pragma once

#include "UltimateConsole.h"
#include "mod/LoadoutControl.h"
#include "mod/game/ActiveGame.h"
#include "security/AccessControl.h"
#include <memory>
#include <menu/MenuManager.h>
#include <patch/PatchManager.h>

class Ultimate {

public:
    static std::shared_ptr<Ultimate> m_ultimate;

    Ultimate();

    void hook();
    void unhook();

    UltimateConsole m_console;
    PatchManager m_patchManager;
    MenuManager m_menuManager;
    AccessControl m_accessControl;
    LoadoutControl m_loadoutControl;
	ActiveGame m_activeGame;

    bool m_hooked;
};
