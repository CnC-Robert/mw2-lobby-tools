#pragma once
#include "../Detour.h"

using MouseMoveFunction = int (*)(int x, int y, int dx, int dy);

class MouseMoveDetour : public Detour {
public:
    static MouseMoveFunction m_originalMouseEvent;

    long applyDetour() override;

    long restoreDetour() override;

    static int hookMouseEvent(int x, int y, int dx, int dy);
};
