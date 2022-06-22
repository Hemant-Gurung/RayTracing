#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(Elite::FPoint3 center, Elite::RGBColor color, Material* mat,std::vector<FPoint3> vertexBuffer, std::vector<int> indexBuffer)
	:GeometricObjects(center,color,mat)
	,m_VertexBuffer{vertexBuffer}
	,m_IndexBuffer{indexBuffer}
	,m_pTriangles{}
{
	FPoint3 p1, p2, p3;
	int n{};
	SceneGraph* scenegraph{ SceneGraph::GetInstance() };
	for (int i = 0; i < m_IndexBuffer.size();)
	{
		p1 = m_VertexBuffer.at(m_IndexBuffer.at(i)-1); //0
		i++;
		p2 = m_VertexBuffer.at(m_IndexBuffer.at(i)-1); //1
		i++;
		p3 = m_VertexBuffer.at(m_IndexBuffer.at(i)-1); //2
		i++; 
		scenegraph->AddObject(new Triangle(m_Center, m_Color, p1, p2, p3, m_material));
	}

}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitrecord)
{
	return false;
	
}

void TriangleMesh::Rotate(Elite::FPoint3 center)
{

}

void TriangleMesh::update()
{
}

void TriangleMesh::RotateObject(Elite::FPoint3 center)
{
}
