#include "Lambert.h"

Lambert::Lambert(float DiffuceReflectance, RGBColor color)
	:Material(DiffuceReflectance,color)
{
}

RGBColor Lambert::Shade(const GeometricObjects::HitRecord& hitRecord , const FVector3& w0, const FVector3& w1)
{
	return (hitRecord.color*m_DiffuseColor)/E_PI;
}
