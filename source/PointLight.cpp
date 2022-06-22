#include "PointLight.h"

PointLight::PointLight(FPoint3 position,RGBColor color,float intensity)
	:Lights(position,color,intensity)
{

}

FPoint3 PointLight::GetDirection()
{
	return m_Position;
}

Elite::RGBColor PointLight::GetIrridiance(Elite::FPoint3 pointToShade)
{
	return m_Color * ((m_LightIntensity) / Elite::SqrMagnitude( m_Position - pointToShade));
}
