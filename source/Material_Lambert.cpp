#include "Material_Lambert.h"
#include "BRDF.h"

Material_Lambert::Material_Lambert(float diffuseReflectance,RGBColor diffuseColor, float specularRef, int phongExp, float metalness,float roughness)
	:Material(diffuseReflectance,diffuseColor,specularRef,phongExp,metalness,roughness)	
{

}
RGBColor Material_Lambert::Shade( HitRecord& hitRecord, const FVector3& l, const FVector3& v)
{
	// half vector calculation

	Elite::FVector3 half = ((v + l) / Elite::Magnitude(v + l));

	// calculate fresnel
	Elite::RGBColor fresnel = Schlick(half, v, m_DiffuseColor, m_metalness); // pass metalness

	float normalDist = ND(hitRecord, half, m_Roughness);
	float geometry = Geometric_Smith(hitRecord, v, l, m_Roughness);
	Elite::RGBColor cookTorrance = (fresnel*normalDist * geometry) /(4* Elite::Dot(v, hitRecord.normal) * Elite::Dot(l, hitRecord.normal));
	Elite::RGBColor kd = RGBColor(1, 1, 1) - fresnel;
	
	// check metalness
	if (m_metalness == 1)
	{
		kd = RGBColor{ 0,0,0 };
	}

	Elite::RGBColor diffuse = kd* BRDF::Lambert(0.7f, Elite::RGBColor(m_DiffuseReflectance, m_DiffuseReflectance, m_DiffuseReflectance));
	
	return diffuse+cookTorrance;
	
}


float Material_Lambert::ND(HitRecord hitrecord, Elite::FVector3 half, float roughness)
{
	float alphaSquared = powf(roughness, 4);
	float dotNHsquared = pow(Elite::Dot(hitrecord.normal, half), 2);
	float alphaminone = (alphaSquared - 1);
	float deno = (dotNHsquared * alphaminone) + 1;
	return alphaSquared / (E_PI * pow(deno, 2));
}

Elite::RGBColor Material_Lambert::Schlick(Elite::FVector3 half, Elite::FVector3 v, Elite::RGBColor f0, int metalness)
{
	if (metalness == 0)
	{
		f0 = Elite::RGBColor{ 0.4,0.4,0.4 };
	}
	float halfDotView = Elite::Dot(half, v);
	float powFive = pow(1 - halfDotView, 5);
	//Fo + (1 - Fo)(1 - (h.v)) ^ 5;
	return f0 + ((Elite::RGBColor{ 1,1,1 } - f0) * powFive);

}

float Material_Lambert::Geometric_SchlickGGX(HitRecord hit, Elite::FVector3 v, float roughness)
{
	float dotnv = Elite::Dot(hit.normal, v);
	if (dotnv < 0)
	{
		return 0.0f;
	}

	float alpha = roughness;

	float alphaPlusONe = alpha + 1;
	float k = pow(alphaPlusONe, 2) / 8;
	float deno = (dotnv * (1 - k)) + k;
	float Gschlick = dotnv / deno;

	return Gschlick;
}

float Material_Lambert::Geometric_Smith(HitRecord hit, Elite::FVector3 v, Elite::FVector3 l, float roughness)
{

	float alpha = roughness;

	float kdir = (pow((alpha + 1), 2)) / 8;

	float dotnl = Elite::Dot(Elite::GetNormalized(hit.normal), Elite::GetNormalized(l));
	if (dotnl < 0)
	{
		return 0.0f;
	}
	float deno = (dotnl * (1 - kdir)) + kdir;
	float Gsmith = dotnl / deno;

	return Geometric_SchlickGGX(hit, v, roughness) * Gsmith;

}

