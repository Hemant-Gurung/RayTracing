#include "Material.h"
#include "GeometricObjects.h"

Material::Material(float diffuseReflectance, Elite::RGBColor diffuseColor,float specularRef,int phongExp,float metalness,float roughness)
	:m_DiffuseColor{diffuseColor}
	,m_DiffuseReflectance{diffuseReflectance}
	,m_SpecularReflectance{specularRef}
	,m_PhongExponent{phongExp}
	,m_metalness{metalness}
	,m_Roughness{roughness}
{

}
