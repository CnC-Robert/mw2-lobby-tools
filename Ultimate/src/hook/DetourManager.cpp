#include "DetourManager.h"
#include "detours/detours.h"
#include "game/ClientDisconnectDetour.h"
#include "game/MenuResponseDetour.h"
#include "input/MouseEventDetour.h"
#include "input/KeyboardPressDetour.h"
#include "party/CanHostServerDetour.h"
#include "party/ClientHandshakeDetour.h"
#include "script/RegisterMethodDetour.h"
#include "script/Scripts.h"
#include "user32/DispatchMessageDetour.h"

DetourManager::DetourManager() {
    registerDetour(std::make_shared<DispatchMessageDetour>()); // Input for imgui
    registerDetour(std::make_shared<MouseEventDetour>()); // Hook mouse input when menu is open
	registerDetour(std::make_shared<KeyboardPressDetour>()); // Allow alt-tab ingame
	registerDetour(std::make_shared<CanHostServerDetour>()); // Force host
	registerDetour(std::make_shared<RegisterMethodDetour>()); // Install hooks when game round starts
    registerDetour(std::make_shared<ClientHandshakeDetour>()); // Check if player is banned
    registerDetour(std::make_shared<ClientDisconnectDetour>()); // Client disconnect
    registerDetour(std::make_shared<MenuResponseDetour>()); // Prevents endgame command it seems

	m_scriptManager.registerHook(230, Proxies::ExitLevel); // Reset ActiveGame when round ends
	m_scriptManager.registerHook(430, Proxies::SetSpawnWeaponControl);
	m_scriptManager.registerHook(438, Proxies::Spawn); // Adds player to ActiveGame
	m_scriptManager.registerHook(467, Proxies::GiveWeaponControl);
	m_scriptManager.registerHook(563, Proxies::SetPerk);
}

void DetourManager::hook() {
    m_d3dHooks.hook();

    beginTransaction();

    std::printf("Applying %Iu detours...\n", m_detours.size());

    for (const auto& detour : m_detours) {
        const auto error = detour->applyDetour();
        if (error != NO_ERROR) {
            std::printf("ApplyDetour failed: %ld\n", error);
        }
    }

    commitTransaction();
}

void DetourManager::unhook() {
    m_d3dHooks.unhook();

    beginTransaction();

    std::printf("Restoring %Iu detours...\n", m_detours.size());

    for (auto detour = m_detours.rbegin(); detour != m_detours.rend(); ++detour) {
        const auto error = (*detour)->restoreDetour();
        if (error != NO_ERROR) {
            std::printf("RestoreDetour failed: %ld\n", error);
        }
    }

    m_scriptManager.resetHooks();

    commitTransaction();
}

void DetourManager::registerDetour(const std::shared_ptr<Detour>& detour) {
    m_detours.push_back(detour);
}

long DetourManager::beginTransaction() {
    auto error = DetourTransactionBegin();
    if (error != NO_ERROR) {
        std::printf("DetourTransactionBegin failed: %ld\n", error);
        return error;
    }

    error = DetourUpdateThread(GetCurrentThread());
    if (error != NO_ERROR) {
        std::printf("DetourUpdateThread failed: %ld\n", error);
        return error;
    }

    return error;
}

long DetourManager::commitTransaction() {
    const auto error = DetourTransactionCommit();
    if (error != NO_ERROR) {
        std::printf("DetourTransactionCommit failed: %ld\n", error);
    }

    return error;
}
