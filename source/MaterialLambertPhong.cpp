#include "MaterialLambertPhong.h"

Material_LambertPhong::Material_LambertPhong(float diffuseRef, Elite::RGBColor color, float specularRef, int phongExp)
	:m_DiffuseRef{diffuseRef}
	,m_Color{color}
	,m_SpecularRef{specularRef}
	,m_PhongExp{phongExp}
{

}
