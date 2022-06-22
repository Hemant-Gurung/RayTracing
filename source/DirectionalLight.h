#pragma once
#include "EMath.h"
#include "Lights.h"
using namespace Elite;
class DirectionLight: public Lights
{
public:
	DirectionLight(FPoint3 positon, RGBColor color, float lightIntensity);
	~DirectionLight() = default;

	DirectionLight(const DirectionLight&) = delete;
	DirectionLight(DirectionLight&&) noexcept = delete;
	DirectionLight& operator=(const DirectionLight&) = delete;
	DirectionLight& operator=(DirectionLight&&) noexcept = delete;

	FPoint3 GetDirection();
	Elite::RGBColor Lights::GetIrridiance(Elite::FPoint3 pointToShade);
private:

};