#pragma once
#include "EMath.h"
#include "ERGBColor.h"
class Material_LambertPhong
{
public:
	Material_LambertPhong(float diffuseRef, Elite::RGBColor color,float specularRef,int phongExp);
	

private:
	float m_DiffuseRef;
	Elite::RGBColor m_Color;
	float m_SpecularRef;
	int m_PhongExp;
};

