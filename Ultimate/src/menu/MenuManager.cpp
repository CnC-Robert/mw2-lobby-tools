#include "MenuManager.h"
#include "iw4/menu.h"
#include "iw4/render.h"
#include "settings/Settings.h"
#include "ultimate/Ultimate.h"
#include <imgui/imgui.h>
#include <imgui/impl/imgui_impl_dx9.h>
#include <imgui/impl/imgui_impl_win32.h>

MenuManager::MenuManager()
    : m_open{ false }
{
    D3DDEVICE_CREATION_PARAMETERS parameters{};
    g_device->GetCreationParameters(&parameters);
    m_window = parameters.hFocusWindow;
}

void MenuManager::initializeImGui() const {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(m_window);
    ImGui_ImplDX9_Init(g_device);
    ImGui::StyleColorsDark();
}

void MenuManager::shutdownImGui() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void MenuManager::onEndScene() {
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX9_NewFrame();
    ImGui::NewFrame();

    if (ImGui::IsKeyPressed(VK_F2)) {
        Menu::OpenMenu(0, "popup_gamesetup");
    }

    if (ImGui::IsKeyPressed(VK_F8)) {
        m_open = !m_open;

        ImGui::GetIO().MouseDrawCursor = m_open;
    }

    if (m_open) {
        Dvar::Draw();

        g_settings.drawSettings();
        Ultimate::m_ultimate->m_loadoutControl.drawLoadoutControls();
        Ultimate::m_ultimate->m_activeGame.drawActiveGame();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool MenuManager::onMessage(MSG* message) const {
    return ImGui_ImplWin32_WndProcHandler(message->hwnd, message->message, message->wParam, message->lParam);
}

bool MenuManager::isMenuOpen() const {
    return m_open;
}
