 #pragma once
#include "hook/party/ClientHandshakeDetour.h"
#include "iw4/gclient.h"
#include "iw4/hudelem.h"
#include <array>
#include <cstdint>

class ActivePlayer {

public:
    ActivePlayer()
        : m_index(0)
        , m_active(false)
    {
    }

    uint32_t m_index;

    bool m_active;

    void reset();

    PartyClient* getPartyClient() const;

    void draw();
};
