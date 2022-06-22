#pragma once
#include "ERGBColor.h"
#include "EMath.h"
#include "GeometricObjects.h"
static class BRDF
{
public:
	BRDF(float diffuseReflectance, Elite::RGBColor diffuseColor);
	~BRDF() = default;

	BRDF(const BRDF&) = delete;
	BRDF(BRDF&&) noexcept = delete;
	BRDF& operator=(const BRDF&) = delete;
	BRDF& operator=(BRDF&&) noexcept = delete;

	static Elite::RGBColor Lambert(float diffuseReflectance,Elite::RGBColor diffuseColor);
	static Elite::RGBColor Phong(float specularReflectance, int m_phoneExponent,const Elite::FVector3& l,const Elite::FVector3& v,const HitRecord hit);

protected:
	float m_DReflectance;
	Elite::RGBColor m_DColor;
};
