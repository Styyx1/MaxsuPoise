#include "LoadGame.h"
#include "Hooks/HitEventHandler.h"
#include "Hooks/MagicStaggerHook.h"
#include "Hooks/PerkEntry_Hooks.h"
#include "Hooks/PoiseRegenHandler.h"
#include "SettingsHandler.h"
#include "PoiseAVHUD.h"

namespace MaxsuPoise
{
	void EventCallback(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kPostPostLoad) {
			static constexpr auto bdiDLLName = "BehaviorDataInjector.dll";
			auto bdiPlugin = GetModuleHandleA(bdiDLLName);
			if (!bdiPlugin) {
				ERROR("Not \"{}\" Loaded!", bdiDLLName);
				return;
			}
			MaxsuPoise::SettingsHandler::Register();
			MaxsuPoise::HitEventHandler::InstallHooks();
			MaxsuPoise::MagicStaggerHook::InstallHooks();
			MaxsuPoise::PoiseRegenHandler::CharacterEx::InstallHook();
			MaxsuPoise::PoiseRegenHandler::PlayerEx::InstallHook();
			MaxsuPoise::PerkEntryHook::Install();

			auto poiseAVHUD = PoiseAVHUD::GetSingleton();
			poiseAVHUD->trueHUDInterface = reinterpret_cast<TRUEHUD_API::IVTrueHUD3*>(TRUEHUD_API::RequestPluginAPI(TRUEHUD_API::InterfaceVersion::V3));
			if (poiseAVHUD->trueHUDInterface) {
				INFO("Obtained TrueHUD API");
			}
			else {
				WARN("Failed to obtain TrueHUD API");
			}
			if (PoiseAVHUD::trueHUDInterface) {
				if (PoiseAVHUD::trueHUDInterface->RequestSpecialResourceBarsControl(SKSE::GetPluginHandle()) == TRUEHUD_API::APIResult::OK) {
					PoiseAVHUD::trueHUDInterface->RegisterSpecialResourceFunctions(SKSE::GetPluginHandle(), PoiseAVHUD::GetCurrentSpecial, PoiseAVHUD::GetMaxSpecial, true);
				}
			}
		}
	}

}
