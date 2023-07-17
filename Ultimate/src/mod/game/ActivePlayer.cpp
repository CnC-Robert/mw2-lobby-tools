#include "ActivePlayer.h"
#include "iw4/iw_string.h"
#include "ultimate/Ultimate.h"
#include "util/Message.h"
#include <imgui/imgui.h>

void ActivePlayer::reset() {
    m_active = false;
}

PartyClient* ActivePlayer::getPartyClient() const {
    return &Party::g_partyData->partyMembers[m_index];
}

void ActivePlayer::draw() {
    const auto client = getPartyClient();

    ImGui::Text("Name: %s", client->name);
    ImGui::Text("SteamID: %lld", client->steamId);
    ImGui::Text("Local ip: %d.%d.%d.%d", client->localIp[0], client->localIp[1], client->localIp[2], client->localIp[3]);
    ImGui::Text("Remote ip: %d.%d.%d.%d", client->remoteIp[0], client->remoteIp[1], client->remoteIp[2], client->remoteIp[3]);

    ImGui::Separator();

    if (ImGui::Button("Kick")) {
        Ultimate::m_ultimate->m_accessControl.kickClient(m_index, "you have been kicked from the server");
    }

    if (ImGui::Button("Ban")) {
        Ultimate::m_ultimate->m_accessControl.banClient(m_index, "you have been banned from the server");
    }
}
