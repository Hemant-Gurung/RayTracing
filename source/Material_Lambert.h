#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "Material.h"

using namespace Elite;
class Material_Lambert: public Material
{

public:
	
	Material_Lambert(float DiffuseReflectance,RGBColor diffuseColor, float specularRef, int phongExp,float metalness,float roughness);
	~Material_Lambert() = default;
	Elite::RGBColor Shade(HitRecord& hit, const Elite::FVector3& w0,const Elite::FVector3& w1);

	Material_Lambert(const Material_Lambert&) = delete;
	Material_Lambert(Material_Lambert&&) noexcept = delete;
	Material_Lambert& operator=(const Material_Lambert&) = delete;
	Material_Lambert& operator=(Material_Lambert&&) noexcept = delete;

private:

	float  ND(HitRecord, Elite::FVector3 half, float roughness);
	RGBColor Schlick(Elite::FVector3 half, Elite::FVector3 view, Elite::RGBColor baseReflectivity, int metalness);
	float Geometric_SchlickGGX(HitRecord hit, Elite::FVector3 view, float roughness);
	float Geometric_Smith(HitRecord hit, Elite::FVector3 view, Elite::FVector3 light, float roughness);
	
};