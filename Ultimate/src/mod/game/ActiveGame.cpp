#include "ActiveGame.h"
#include "iw4/iw_string.h"
#include "iw4/party.h"
#include "iw4/server.h"
#include "mod/weapon/WeaponClassRule.h"
#include "ultimate/Ultimate.h"
#include "util/Message.h"

ActivePlayer& ActiveGame::getActivePlayer(const uint32_t playerNum)
{
    return m_activePlayers[playerNum];
}

void ActiveGame::playerSpawned(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    if (!player.m_active) {
        player.m_index = playerNum;
        player.m_active = true;
    }
}

void ActiveGame::playerDisconnected(const uint32_t playerNum)
{
    auto& player = getActivePlayer(playerNum);

    player.reset();
}

void ActiveGame::gameOver()
{
    for (auto& activePlayer : m_activePlayers) {
        activePlayer.reset();
    }
}

void ActiveGame::drawActiveGame()
{
    ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Button("Restart")) {
        Cmd::AddCommandToBuffer(0, "map_restart");
    }

    ImGui::Separator();

    for (auto& player : m_activePlayers) {

        const auto text = String::Format("%2d - %s", player.m_index, player.m_active ? player.getPartyClient()->name : "---");

        if (ImGui::TreeNodeEx(text)) {
            if (player.m_active) {
                player.draw();
            }

            ImGui::TreePop();
        }
    }

    ImGui::End();
}
