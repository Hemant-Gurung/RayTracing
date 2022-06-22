#include "Ray.h"

Ray::Ray(Elite::FPoint3 origin, Elite::FVector3 direction)
	:m_Origin{origin},
	m_Direction{direction},
	m_tMax{FLT_MAX},
	m_tMin{0.0001f}

{

}

Elite::FPoint3 Ray::At(float t) const
{
	return m_Origin + (t * m_Direction);
}


