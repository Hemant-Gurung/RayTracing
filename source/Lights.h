#pragma once
#include "EMath.h"
#include "ERGBColor.h"
class Lights
{
public:
	Lights(Elite::FPoint3 position, Elite::RGBColor color, float lightIntensity);
	~Lights() = default;

	Lights(const Lights&) = delete;
	Lights(Lights&&) noexcept = delete;
	Lights& operator=(const Lights&) = delete;
	Lights& operator=(Lights&&) noexcept = delete;

	virtual Elite::FPoint3 GetDirection() = 0;
	virtual Elite::RGBColor GetIrridiance(Elite::FPoint3 pointToShade) = 0;
	 
protected:
	Elite::FPoint3 m_Position;
	Elite::RGBColor m_Color;
	float m_LightIntensity;
};