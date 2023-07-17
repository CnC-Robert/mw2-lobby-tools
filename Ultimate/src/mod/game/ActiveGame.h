#pragma once
#include "ActivePlayer.h"
#include <array>
#include <random>

class ActiveGame {

    std::array<ActivePlayer, 18> m_activePlayers{};

    ActivePlayer& getActivePlayer(uint32_t playerNum);

    std::random_device m_randomDevice;
    std::mt19937 m_weaponRng;
    std::uniform_int_distribution<int> m_weaponDistribution;
	std::uniform_int_distribution<int> m_equipmentDistribution;;

public:
	ActiveGame()
		: m_weaponRng{ m_randomDevice() }
		, m_weaponDistribution(3, 1143)
		, m_equipmentDistribution(1144, 1152)
    {
    }

    void playerSpawned(uint32_t playerNum);
    void playerKilled(uint32_t victimPlayerNum, uint32_t killerPlayerNum);
    void setKillStreak(uint32_t killerPlayerNum, int32_t streak);
    void playerSuicide(uint32_t playerNum);
    void playerDisconnected(uint32_t playerNum);
    void gameOver();

	void drawActiveGame();
};
