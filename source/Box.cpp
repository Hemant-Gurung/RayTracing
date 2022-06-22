#include "Box.h"

Box::Box(Elite::FPoint3 center,float width,float height, Elite::FVector3 normal, Elite::RGBColor color, Material* mat,Elite::FPoint3 startPoint)
	:GeometricObjects(center,color,mat)
	,m_StartPoint{startPoint}
	,m_width{width}
	,m_height{height}
{

}

bool Box::Hit(const Ray& ray, HitRecord& hitRecord)
{
    Elite::FVector3 pp = m_Center - ray.m_Origin;
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

bool Box::PointInBox(std::vector<Elite::FPoint4> trianglePoints, const Elite::FVector2& widthHeight)
{
	//m_leftBottom = 
	float xMin = std::min(trianglePoints[0].x, std::min(trianglePoints[1].x, trianglePoints[2].x));
	float yMin = std::min(trianglePoints[0].y, std::min(trianglePoints[1].y, trianglePoints[2].y));
	float xMax = std::max(trianglePoints[0].x, std::max(trianglePoints[1].x, trianglePoints[2].x));
	float yMax = std::max(trianglePoints[0].y, std::max(trianglePoints[1].y, trianglePoints[2].y));

	//      0 >= xValues <= (width-1)  0 >= yValues <= (height-1)


	if (xMin < 0)xMin = 0;
	if (yMin < 0)yMin = 0;
	if (xMax > widthHeight.x) xMax = widthHeight.x - 1;
	if (yMax > widthHeight.y) yMax = widthHeight.y - 1;

	m_topLeft = { xMin,yMin };
	m_RighBottom = { xMax,yMax };
	return true;
}
void Box::Rotate(Elite::FPoint3 center)
{

}

void Box::RotateObject(Elite::FPoint3 center)
{
}

void Box::update()
{

}
