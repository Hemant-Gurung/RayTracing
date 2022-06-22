#include "DirectionalLight.h"

DirectionLight::DirectionLight(FPoint3 direction, RGBColor color, float lightIntensity)
	:Lights(direction,color,lightIntensity)
{
}

FPoint3 DirectionLight::GetDirection()
{
	return m_Position;
}

Elite::RGBColor DirectionLight::GetIrridiance(Elite::FPoint3 pointToShade)
{
	return m_Color * (m_LightIntensity);
}

