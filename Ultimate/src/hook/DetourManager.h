#pragma once

#include "Detour.h"
#include "d3d/D3DHooks.h"
#include "script/ScriptManager.h"
#include <memory>
#include <vector>

class DetourManager {
public:
    DetourManager();

    void hook();
    void unhook();

    void registerDetour(const std::shared_ptr<Detour>& detour);

    ScriptManager m_scriptManager;

private:
    std::vector<std::shared_ptr<Detour>> m_detours;

    static long beginTransaction();
    static long commitTransaction();

    D3DHooks m_d3dHooks;
};

inline DetourManager g_detours{};
