#include "BRDF.h"

BRDF::BRDF(float diffuseReflectance, Elite::RGBColor diffuseColor)
	:m_DColor{diffuseColor}
	,m_DReflectance{diffuseReflectance}
{
}

 Elite::RGBColor BRDF::Lambert(float diffuseReflectance, Elite::RGBColor diffuseColor)
{
	return (diffuseColor) * (diffuseReflectance);
}

Elite::RGBColor BRDF::Phong(float specularReflectance, int phoneExponent,const Elite::FVector3& l, const Elite::FVector3& v, const HitRecord hit)
{
	auto reflect = l - 2 * (Elite::Dot(hit.normal,l)) * hit.normal;
	float cos = Elite::Dot(reflect, v);
     float specRef = (specularReflectance* (powf(cos, phoneExponent)));
	return Elite::RGBColor(specRef,specRef,specRef);
}

