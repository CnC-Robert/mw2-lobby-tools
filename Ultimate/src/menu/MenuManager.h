#pragma once
//#include "disasembler/Disassembler.h"
#include <d3d9.h>

class MenuManager {
public:
    MenuManager();

    HWND m_window;
    bool m_open;

    void initializeImGui() const;
	static void shutdownImGui();

    void onEndScene();
    bool onMessage(MSG* message) const;
    bool isMenuOpen() const;
};
