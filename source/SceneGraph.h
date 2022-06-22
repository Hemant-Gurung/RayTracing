#pragma once
#include "Singleton.h"
#include "GeometricObjects.h"
#include <list>
#include "Material.h"
#include "Lights.h"
#include "Box.h"
class SceneGraph:public Singleton<SceneGraph>
{
public:
	//objects
	void AddObject(GeometricObjects* object);
	void RemoveObjects(GeometricObjects* object);
	std::list<GeometricObjects*>& GetObjectFromScence();

	//Lights
	void AddLights(Lights* light);
	void RemoveLights(Lights* object);
	std::list<Lights*>& GetLights();
	//Materials
	void AddMaterial(Material* light);
	void RemoveMaterial(Material* object);
	Material* GetMaterial(int index);

	void AddBox(Box* box);
	std::list<Box*>& GetBoxFromScence();
private:
	std::list<GeometricObjects*> m_objects;
	std::list<Lights*> m_Lights;
	std::vector<Material*> m_Materials;
	std::list<Box*> m_Boxes;
//	std::list<GeometriObjects*> m_objects;
	//std::list<li

	
};

