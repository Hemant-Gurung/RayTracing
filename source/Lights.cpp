#include "Lights.h"

Lights::Lights(Elite::FPoint3 direction, Elite::RGBColor color, float lightIntensity)
	:m_Position(direction),
	m_Color(color),
	m_LightIntensity(lightIntensity)
{

}
