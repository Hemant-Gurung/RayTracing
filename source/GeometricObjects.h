#pragma once
#include "Ray.h"
#include "ERGBColor.h"
#include <vector>
#include "Material.h"

struct HitRecord
{
	Elite::FPoint3 hitPoint{};
	Elite::RGBColor color{};
	float tValue{};
	Elite::FVector3 normal{};
	Material* mat{};
};


class GeometricObjects
{
	
public:
	
	GeometricObjects(Elite::FPoint3 center,Elite::RGBColor color,Material* mat);
	~GeometricObjects() = default;

	GeometricObjects(const GeometricObjects&) = delete;
	GeometricObjects(GeometricObjects&&) noexcept = delete;
	GeometricObjects& operator=(const GeometricObjects&) = delete;
	GeometricObjects& operator=(GeometricObjects&&) noexcept = delete;

	virtual bool Hit(const Ray& ray,HitRecord& hitrecord) = 0;
	virtual void Rotate(Elite::FPoint3 center) = 0;
	virtual void RotateObject(Elite::FPoint3 center) =0;
	
	HitRecord m_Hit;
	Elite::FPoint3 m_Center{};
	Elite::RGBColor m_Color{};
	Material* m_material{};
	virtual void update() =0;

protected:
	
	
};