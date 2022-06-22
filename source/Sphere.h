#pragma once
#include "ERenderer.h"
#include "GeometricObjects.h"
class Sphere : public GeometricObjects
{
public:
	Sphere(Elite::FPoint3 center, Elite::RGBColor color,float radious,Material* mat);
	~Sphere() = default;

	Sphere(const Sphere&) = delete;
	Sphere(Sphere&&) noexcept = delete;
	Sphere& operator=(const Sphere&) = delete;
	Sphere& operator=(Sphere&&) noexcept = delete;

	bool Hit(const Ray& ray,HitRecord& hitRecord) override;
	void Rotate(Elite::FPoint3 center);
	void RotateObject(Elite::FPoint3 center);
	float m_Radious;
	void update();
protected:
	
};