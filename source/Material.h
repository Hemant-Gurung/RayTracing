#pragma once

#include "ERGBColor.h"
#include "EMath.h"

struct HitRecord;

class Material
{
public:
	Material(float diffuseReflectance, Elite::RGBColor diffuseColor,float specularRef,int phongExp,float metalness,float roughness);
	~Material() = default;

	Material(const Material&) = delete;
	Material(Material&&) noexcept = delete;
	Material& operator=(const Material&) = delete;
	Material& operator=(Material&&) noexcept = delete;

	virtual Elite::RGBColor Shade( HitRecord& hit, const Elite::FVector3& w0, const Elite::FVector3& w1) = 0;
	
protected:


	float m_DiffuseReflectance;
	Elite::RGBColor m_DiffuseColor;
	float m_SpecularReflectance;
	int m_PhongExponent;
	float m_metalness;
	float m_Roughness;
};
//