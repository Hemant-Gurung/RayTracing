#include "Triangle.h"
using namespace Elite;
Triangle::Triangle(Elite::FPoint3 center, const Elite::RGBColor color, const FPoint3& tp1,const FPoint3& tp2, const FPoint3& tp3, Material* mat)
	:GeometricObjects(center,color,mat)
	,m_tp1{tp1}
	,m_tp2{tp2}
	,m_tp3{tp3}	
{
	m_Center= { (m_tp1.x + m_tp2.x + m_tp3.x) / 3,(m_tp1.y + m_tp2.y + m_tp3.y) / 3,(m_tp1.z + m_tp2.z + m_tp3.z) / 3 };
}

bool Triangle::Hit(const Ray& ray, HitRecord& hitrecord)
{
    //calculate center
	m_Center = {(m_tp1.x+m_tp2.x+m_tp3.x)/3,(m_tp1.y + m_tp2.y + m_tp3.y) / 3,(m_tp1.z + m_tp2.z + m_tp3.z) / 3 };

	FVector3 a = (m_tp2 - m_tp1);
	FVector3 b = (m_tp3 - m_tp1);
	m_Normal =GetNormalized(Cross(a, b));

	Elite::FVector3 pp = m_Center - ray.m_Origin;
  
    float t = (Dot(pp, m_Normal) / Dot(ray.m_Direction, m_Normal));

    if (t > ray.m_tMin && t < ray.m_tMax)
    {
        hitrecord.tValue = t;
        hitrecord.color = m_Color;
        hitrecord.hitPoint = ray.At(t);
		hitrecord.normal = m_Normal;
		float result{Dot(m_Normal, ray.m_Direction)};
		
		switch (m_face)
		{
		case Triangle::faces::backface:
			if(result>0)
				return PointInTriangle(hitrecord.hitPoint);

			break;
		case Triangle::faces::frontface:
			if (result < 0)
				return PointInTriangle(hitrecord.hitPoint);
			break;
		case Triangle::faces::both:
			return PointInTriangle(hitrecord.hitPoint);
			break;
		default:
			break;
		}
        return false;
    }
    return false;
}

bool Triangle::PointInTriangle(const FPoint3& P)
{
	/*m_P = P;*/
	// triangle vector points

	Elite::FVector3 ab = m_tp2 - m_tp1;
	Elite::FVector3 bc = m_tp3 - m_tp2;
	Elite::FVector3 ca = m_tp1 - m_tp3;

	// normal calculation
	Elite::FVector3 ac = m_tp3 - m_tp1;
	
	// vector to point P
	FVector3 m_Ptp1 = P - m_tp1;
	FVector3 m_Ptp2 = P - m_tp2;
	FVector3 m_Ptp3 = P - m_tp3; 
	

	 Elite::FVector3 n = Elite::Cross(ab, ac);
	 Elite::GetNormalized(n);
	// do cross product 
	Elite::FVector3 first = GetNormalized(Cross(ab, m_Ptp1));
	Elite::FVector3 second = GetNormalized(Cross(bc, m_Ptp2));
	Elite::FVector3 third = GetNormalized(Cross(ca, m_Ptp3));

	
	if (Dot(n, first) > 0 && Dot(n, second) > 0 && Dot(n, third) > 0)
	{
		return true;
	}

	//and see if it has same direction as normal

	return false;
}

void Triangle::Rotate(Elite::FPoint3 center)
{

	FMatrix4 T1 = MakeTranslation(FVector3(-center.x, -center.y,-center.z));
	FMatrix4 R = MakeRotationY(0.1f);
	
	FMatrix4 TB1 = MakeTranslation(FVector3(center.x, center.y, center.z));
	
	FMatrix4 p{TB1*R*T1};
	
	//p = MakeRotation(0.5f, FVector3{ 0,0,1 });
	FPoint4 tp1 =	 { m_tp1.x,m_tp1.y,m_tp1.z,1 };
	FPoint4 tp2 =	 { m_tp2.x,m_tp2.y,m_tp2.z,1 };
	FPoint4 tp3 =	 { m_tp3.x,m_tp3.y,m_tp3.z,1 };
	FPoint4 normal = { m_Normal.x,m_Normal.y,m_Normal.z ,1};


	FPoint4 TransformPix1 = (p * tp1);
	FPoint4 TransformPix2 = (p * tp2);
	FPoint4 TransformPix3 = (p * tp3);
	normal = (p * normal);

	
	m_tp1 =(TransformPix1.xyz);
	m_tp2 = TransformPix2.xyz;
    m_tp3 = TransformPix3.xyz;

	m_Normal =(FVector3{normal.xyz});


}

void Triangle::switchMode()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_F]) {
		m_face = faces::frontface;
	}
	else if (state[SDL_SCANCODE_B]) {
		m_face = faces::backface;
	}
	else if(state[SDL_SCANCODE_G])
	{
		m_face = faces::both;
	}
}

void Triangle::update()
{
	switchMode();
}

void Triangle::RotateObject(Elite::FPoint3 center)
{
	FMatrix4 R = MakeRotationY(0.1f);

	//FMatrix4 TB1 = MakeTranslation(FVector3(center.x, center.y, center.z));

	FMatrix4 p{R};

	//p = MakeRotation(0.5f, FVector3{ 0,0,1 });
	FPoint4 tp1 = { m_tp1.x,m_tp1.y,m_tp1.z,1 };
	FPoint4 tp2 = { m_tp2.x,m_tp2.y,m_tp2.z,1 };
	FPoint4 tp3 = { m_tp3.x,m_tp3.y,m_tp3.z,1 };
	FPoint4 normal = { m_Normal.x,m_Normal.y,m_Normal.z ,1 };


	FPoint4 TransformPix1 = (p * tp1);
	FPoint4 TransformPix2 = (p * tp2);
	FPoint4 TransformPix3 = (p * tp3);
	normal = (p * normal);


	m_tp1 = (TransformPix1.xyz);
	m_tp2 = TransformPix2.xyz;
	m_tp3 = TransformPix3.xyz;

	m_Normal = (FVector3{ normal.xyz });

}
