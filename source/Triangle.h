#pragma once
#include "SDL.h"
#include "SDL_surface.h"
#include "GeometricObjects.h"
#include <list>

using namespace Elite;
class Triangle : public GeometricObjects
{
public:
	Triangle(Elite::FPoint3 center,const Elite::RGBColor color, const  FPoint3& tp1, const  FPoint3& tp2,const  FPoint3& tp3, Material* mat);
	~Triangle() = default;

	Triangle(const Triangle&) = delete;
	Triangle(Triangle&&) noexcept = delete;
	Triangle& operator=(const Triangle&) = delete;
	Triangle& operator=(Triangle&&) noexcept = delete;


	bool Hit(const Ray& ray, HitRecord& hitrecord) override;
	bool PointInTriangle(const FPoint3& P);
	void Rotate(Elite::FPoint3 center);
	void switchMode();
	void update();

	// object
	void RotateObject(Elite::FPoint3 center);
private:
	FPoint3 m_tp1;
	FPoint3 m_tp2;
	FPoint3 m_tp3;
	
	FVector3 m_Normal;

	
	enum class faces
	{
		backface,
		frontface,
		both,
	};
	faces m_face{ faces::frontface};


};