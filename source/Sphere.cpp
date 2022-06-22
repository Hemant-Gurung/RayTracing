#include "Sphere.h"

Sphere::Sphere(Elite::FPoint3 center, Elite::RGBColor color, float radious,Material* mat)
	:GeometricObjects(center,color,mat),
	 m_Radious{radious}

{

}

bool Sphere::Hit(const Ray& ray, HitRecord& hitRecord)
{

	float a = Dot(ray.m_Direction, ray.m_Direction);
	float b = Dot(2 * ray.m_Direction, ray.m_Origin - m_Center);
	float c = Dot(ray.m_Origin - m_Center, ray.m_Origin - m_Center) - Elite::Square(m_Radious);

	//calculate discriminant
	float discriminant = Square(b) - 4 * a * c;

	if (discriminant > 0)
	{
	//Calculate t.
		float t = (-b - sqrt(discriminant)) / (2 * a);
		if (!(t > ray.m_tMin && t <ray.m_tMax))
		{
			//t is out of allowed range, check for t1 instead
			t = (-b + sqrt(discriminant)) / (2 * a);

			if (!(t > ray.m_tMin && t < ray.m_tMax))
				//return false if both t-values are out of bounds
				return false;
		}

		hitRecord.tValue = t;
		hitRecord.hitPoint = ray.At(t);
		hitRecord.color = m_Color;
		hitRecord.normal =GetNormalized(hitRecord.hitPoint -m_Center);
		hitRecord.mat = m_material;
		return true;
	}
	return false;
}

void Sphere::Rotate(Elite::FPoint3 center)
{
}

void Sphere::RotateObject(Elite::FPoint3 center)
{
}

void Sphere::update()
{
}


