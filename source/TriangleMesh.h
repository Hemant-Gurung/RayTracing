#pragma once

#include <vector>
#include "GeometricObjects.h"
#include "Triangle.h"
#include "SceneGraph.h"
using namespace Elite;
class  TriangleMesh:public GeometricObjects
{
public:


	TriangleMesh(Elite::FPoint3 center, Elite::RGBColor color, Material* mat, std::vector<FPoint3> vertexBuffer,std::vector<int> indexBuffer);
	~TriangleMesh()= default ;

	TriangleMesh(const TriangleMesh&) = delete;
	TriangleMesh(TriangleMesh&&) noexcept = delete;
	TriangleMesh& operator=(const TriangleMesh&) = delete;
	TriangleMesh& operator=(TriangleMesh&&) noexcept = delete;

     bool Hit(const Ray& ray, HitRecord& hitrecord);
	 void Rotate(Elite::FPoint3 center);
	 void update();
	 void RotateObject(Elite::FPoint3 center);

private:
	std::vector<FPoint3> m_VertexBuffer;
	std::vector<int> m_IndexBuffer;
	std::vector<Triangle*> m_pTriangles;
};

