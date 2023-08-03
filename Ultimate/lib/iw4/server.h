#pragma once
#include "client.h"
#include "entity.h"
#include "util.h"
#include <cstdint>

enum class svscmd_type {
    SV_CMD_CAN_IGNORE = 0,
    SV_CMD_RELIABLE = 1,
};

using SV_GameDropClient_f = void (*)(int clientNum, const char* reason);
const inline auto SV_GameDropClient = reinterpret_cast<SV_GameDropClient_f>(0x588390);

using SV_GameSendServerCommand_f = void (*)(int clientNum, svscmd_type type, const char* fmt);
const inline auto SV_GameSendServerCommand = reinterpret_cast<SV_GameSendServerCommand_f>(0x588340);

void SV_GameSendServerCommandAll(svscmd_type type, const char* fmt);

const inline auto g_hostId = reinterpret_cast<int32_t*>(0x10FA938);
const inline auto g_serverId = reinterpret_cast<int32_t*>(0x20228A8);

namespace Server {

IW4_FUNCTION(SetConfigString, void, (int index, const char* val), 0x589AF0);
IW4_FUNCTION(GetConfigString, void, (int index, char* buffer, int bufferSize), 0x588E00);
IW4_FUNCTION(GetConfigStringConst, unsigned int, (int index), 0x588E30);
IW4_FUNCTION(UnlinkEntity, void, (gentity_s*), 0x590000);
IW4_FUNCTION(LinkEntity, void, (gentity_s*), 0x5900A0);
IW4_FUNCTION(SetBrushModel, bool, (gentity_s*), 0x588540);
IW4_FUNCTION(SomeBrushSetup, char, (gentity_s*), 0x5884C0);
IW4_FUNCTION(AddTestClient, gentity_s*, (), 0x588140);
IW4_FUNCTION(MapRestart, void, (int fastRestart, int unknown), 0x5850A0);

void ExecuteClientCommand(client_t* client, const char* command, int clientOk, int fromOldServer);
}
