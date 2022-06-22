#include "SceneGraph.h"


void SceneGraph::AddObject(GeometricObjects* object)
{
	m_objects.push_back(object);
}

void SceneGraph::RemoveObjects(GeometricObjects* object)
{
	m_objects.remove(object);
	delete object;
}

std::list<GeometricObjects*>& SceneGraph::GetObjectFromScence()
{
	return m_objects;
	// TODO: insert return statement here
}

void SceneGraph::AddLights(Lights* light)
{
	m_Lights.push_back(light);
}

void SceneGraph::RemoveLights(Lights* light)
{
	m_Lights.remove(light);
	delete light;
}

std::list<Lights*>& SceneGraph::GetLights()
{
	return m_Lights;
}

void SceneGraph::AddMaterial(Material* material)
{
	m_Materials.push_back(material);
}

void SceneGraph::RemoveMaterial(Material* material)
{
	//m_Materials.remove(material);
	delete material;
}

Material* SceneGraph::GetMaterial(int index)
{
	return m_Materials.at(index);
}


void SceneGraph::AddBox(Box* box)
{
	m_Boxes.push_back(box);
}

std::list<Box*>& SceneGraph::GetBoxFromScence()
{
	return m_Boxes;
	// TODO: insert return statement here
}