#pragma once
#include "EMath.h"
class Ray
{
public:
	Ray(Elite::FPoint3 origin, Elite::FVector3 direction);
	~Ray() = default;

	float m_tMin {0.0001f};
	float m_tMax {FLT_MAX};
	Elite::FPoint3 m_Origin;
	Elite::FVector3 m_Direction;

	Elite::FPoint3 At(float t) const;
private:
	

};