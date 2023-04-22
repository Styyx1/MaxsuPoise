#include "LoadGame.h"
#include "HitEventHandler.h"
#include "PerkEntry_Hooks.h"
#include "PoiseRegenHandler.h"
#include "SettingsHandler.h"

namespace MaxsuPoise
{
	void EventCallback(SKSE::MessagingInterface::Message* msg)
	{
		if (msg->type == SKSE::MessagingInterface::kPostPostLoad) {
			MaxsuPoise::SettingsHandler::Register();
			MaxsuPoise::HitEventHandler::InstallHooks();
			MaxsuPoise::PoiseRegenHandler::CharacterEx::InstallHook();
			MaxsuPoise::PoiseRegenHandler::PlayerEx::InstallHook();
			MaxsuPoise::PerkEntryHook::Install();
		}
	}

}
