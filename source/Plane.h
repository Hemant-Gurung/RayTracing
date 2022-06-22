#pragma once
#include "EMath.h"
#include "GeometricObjects.h"
#include "Material.h"

class Plane: public GeometricObjects
{
public:
	Plane(Elite::FPoint3 center, Elite::FVector3 normal,Elite::RGBColor color,Material *mat);
	~Plane()= default;

	Plane(const Plane&) = delete;
	Plane(Plane&&) noexcept = delete;
	Plane& operator=(const Plane&) = delete;
	Plane& operator=(Plane&&) noexcept = delete;

	bool Hit(const Ray& ray, HitRecord& hitRecord) override;
	void Rotate(Elite::FPoint3 center);
	void RotateObject(Elite::FPoint3 center);
	Elite::FVector3 m_Normal;
	void update();
private:
};