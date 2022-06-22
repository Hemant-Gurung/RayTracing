#pragma once
#include "EMath.h"
#include"Material.h"

class Lambert: public Material 
{
public:
	Lambert(float m_DiffuseReflectance,RGBColor color);
	~Lambert() = default;

	RGBColor Shade(const GeometricObjects::HitRecord& hit , const FVector3& w0, const FVector3& w1);

private:
};