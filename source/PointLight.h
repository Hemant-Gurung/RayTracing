#pragma once
#include "EMath.h"
#include "Lights.h"
using namespace Elite;
class PointLight: public Lights
{
public:
	PointLight(FPoint3 position, RGBColor color, float LightIntensity);
	~PointLight() = default;

	PointLight(const PointLight&) = delete;
	PointLight(PointLight&&) noexcept = delete;
	PointLight& operator=(const PointLight&) = delete;
	PointLight& operator=(PointLight&&) noexcept = delete;

	FPoint3 GetDirection();
	Elite::RGBColor Lights::GetIrridiance(Elite::FPoint3 pointToShade);
};