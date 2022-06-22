#pragma once
#include "GeometricObjects.h"
class Box : public GeometricObjects
{
public:
	Box(Elite::FPoint3 center,float width, float height, Elite::FVector3 normal, Elite::RGBColor color, Material* mat,Elite::FPoint3 startpoint);
	~Box() = default;

	Box(const Box&) = delete;
	Box(Box&&) noexcept = delete;
	Box& operator=(const Box&) = delete;
	Box& operator=(Box&&) noexcept = delete;

	bool PointInBox(std::vector<Elite::FPoint4> trianglePoints, const Elite::FVector2 & widthHeight);
	Elite::FPoint2 GetLeftBottom();
	bool Hit(const Ray& ray, HitRecord& hitRecord) override;
	void Rotate(Elite::FPoint3 center);
	void RotateObject(Elite::FPoint3 center);
	Elite::FVector3 m_Normal;

	void update();
private:
	Elite::FVector3 m_StartPoint;
	Elite::FPoint2 m_topLeft{};
	Elite::FPoint2 m_RighBottom{};
	float m_width;
	float m_height;
};