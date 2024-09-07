#include "PoiseAVHUD.h"
#include "StaggerHandler.h"
#include "Hooks/PoiseRegenHandler.h"
#include "PoiseDamageCalculator.h"
#include "PoiseHealthHandler.h"
#include "Utils.h"

/*
const auto totalPoiseHealth = PoiseHealthHandler::GetTotalPoiseHealth(a_target);
auto currentPoiseHealth = PoiseHealthHandler::GetCurrentPoiseHealth(a_target);

*/


float PoiseAVHUD::GetMaxSpecial(RE::Actor* a_actor)
{
	if (a_actor) {
		const auto totalPoiseHealth = MaxsuPoise::PoiseHealthHandler::GetTotalPoiseHealth(a_actor);
		return totalPoiseHealth;
	}
	return 1.0f;
}

float PoiseAVHUD::GetCurrentSpecial(RE::Actor* a_actor)
{
	if (a_actor) {

		auto currentPoiseHealth = MaxsuPoise::PoiseHealthHandler::GetCurrentPoiseHealth(a_actor);
		return currentPoiseHealth + FLT_MIN;
	}
	return 1.0f;
}