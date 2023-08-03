#include "Scripts.h"
#include "settings/Settings.h"
#include "util/Message.h"
#include <iw4/iw_string.h>
#include <iw4/party.h>
#include <iw4/server.h>
#include <ultimate/Ultimate.h>

namespace Proxies {

	bool GiveWeaponControl(const scr_entref_t entref) {
		const auto weaponName = Script::GetString(0);

		const auto replace = Ultimate::m_ultimate->m_loadoutControl.shouldWeaponBeReplaced(weaponName);
		if (replace) {
			Script::g_scrVmPub->top->u.stringValue = String::GetString(Ultimate::m_ultimate->m_loadoutControl.m_replacementWeapon.build().c_str(), 0);
		}

		//        if (strstr(weaponName, "deserteagle") != nullptr) {
		//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
		//        } else if (entref.entnum == *g_hostId && strstr(weaponName, "usp") != nullptr) {
		//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
		//        }

		return true;
	}

	bool SetSpawnWeaponControl(const scr_entref_t entref) {
		const auto weaponName = Script::GetString(0);

		const auto weaponIndex = BG_FindWeaponIndexForName(weaponName);

		if (IsWeapon(weaponIndex)) {
			const auto replace = Ultimate::m_ultimate->m_loadoutControl.shouldWeaponBeReplaced(weaponName);

			if (replace) {
				Script::g_scrVmPub->top->u.stringValue = String::GetString(Ultimate::m_ultimate->m_loadoutControl.m_replacementWeapon.build().c_str(), 0);
			}

			//        if (strstr(weaponName, "deserteagle") != nullptr) {
			//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
			//        } else if (entref.entnum == *g_hostId && strstr(weaponName, "usp") != nullptr) {
			//            Script::g_scrVmPub->top->u.stringValue = String::GetString("deserteaglegold_mp", 0);
			//        }
		}

		//const auto fovString = String::Format("s cg_fov \"%d\"", g_settings.m_gameSettings.m_forcedFov);
		//SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, fovString);
		SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_ScoresPing_MaxBars \"4\"");
		SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_chatHeight \"8\"");
		SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_hudChatPosition \"5 204\"");
		SV_GameSendServerCommand(entref.entnum, svscmd_type::SV_CMD_RELIABLE, "s cg_hudChatIntermissionPosition \"5 110\"");

		return true;
	}

	bool SetPerk(const scr_entref_t entref) {
		const auto playerName = Party::g_partyData->partyMembers[entref.entnum].name;
		const auto perkName = Script::GetString(0);

		const auto replace = Ultimate::m_ultimate->m_loadoutControl.shouldPerkBeReplaced(perkName);

		if (replace) {
			Script::g_scrVmPub->top->u.stringValue = String::GetString(Ultimate::m_ultimate->m_loadoutControl.m_replacementPerk.c_str(), 0);
		}

		if (g_settings.m_logSettings.m_logPerks) {
			std::printf("PlayerCmd_SetPerk -> setting perk %s on %s\n", perkName, playerName);
		}

		return true;
	}

	bool Spawn(const scr_entref_t entref) {
		Ultimate::m_ultimate->m_activeGame.playerSpawned(entref.entnum);
		return true;
	}

} // namespace Proxies
