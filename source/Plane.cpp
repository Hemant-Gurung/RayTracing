#include "Plane.h"

Plane::Plane(Elite::FPoint3 center, Elite::FVector3 normal,Elite::RGBColor color, Material* mat)
	:GeometricObjects(center,color,mat),
	 m_Normal{normal}
  
{

}

bool Plane::Hit(const Ray& ray, HitRecord& hitRecord)
{
    Elite::FVector3 pp =  m_Center - ray.m_Origin;
    float t = (Dot(pp, m_Normal) / Dot(ray.m_Direction, m_Normal));

    if (t > ray.m_tMin && t < ray.m_tMax)
    {
        hitRecord.tValue = t;
        hitRecord.color = m_Color;
        hitRecord.hitPoint = ray.At(t);
        hitRecord.normal = m_Normal;
        return true;
    }
    return false;
}

void Plane::Rotate(Elite::FPoint3 center)
{

}

void Plane::RotateObject(Elite::FPoint3 center)
{
}

void Plane::update()
{
}


