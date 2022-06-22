/*=============================================================================*/
// Copyright 2017-2019 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
// ERenderer.h: class that holds the surface to render to, does traverse the pixels 
// and traces the rays using a tracer
/*=============================================================================*/
#ifndef ELITE_RAYTRACING_RENDERER
#define	ELITE_RAYTRACING_RENDERER

#include <cstdint>
#include "GeometricObjects.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Triangle.h"
#include"Camera.h"
#include <vector>
#include <list>
#include"PointLight.h"
#include "DirectionalLight.h"
#include "Lights.h"
#include "Material.h"
#include"Material_Lambert.h"
#include <list>
#include "TriangleMesh.h"
#include "Parser.h"

struct SDL_Window;
struct SDL_Surface;
namespace Elite
{
	class Renderer final
	{
	public:

		enum class keys
		{
			none,
			left,
			right,
			up,
			down,
			T,
		};

		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Update();
		void Render();
		bool SaveBackbufferToImage() const;

		keys m_Key{ keys::none };
	private:
		SDL_Window* m_pWindow = nullptr;
		SDL_Surface* m_pFrontBuffer = nullptr;
		SDL_Surface* m_pBackBuffer = nullptr;
		uint32_t* m_pBackBufferPixels = nullptr;

		uint32_t m_Width = 0;
		uint32_t m_Height = 0;


		float m_Scale{};
		Camera* m_Camera{ nullptr };
		float m_AspectRatio{}, m_FOV{};


		RGBColor m_Color;
		float m_Intensity;


		bool m_IsBRDFon{};
		void SwitchKeyMouse();
		bool IsHit(Ray& ray);


		void addMaterialsToScengraph();

		//box
		Box* m_Box;

		// triangle vertices for vertex buffer
		Elite::FPoint3 m_v1{ -0.75f, 1.5f, 0.f };
		Elite::FPoint3 m_v2{ -0.75f, 0.f, 0.f };
		Elite::FPoint3 m_v3{0.75f, 0.f, 0.f};
		Elite::FPoint3 m_v4{ 0.5f, 1.5f, 1.f };
		Elite::FPoint3 m_v5{ -0.75,2.5f,-2.f };
		// front face and back face boolean
		bool m_backFace{};
		bool m_frontFace{};

		// shadow bool
		bool m_ShowShadow;

		// select scence
		bool m_sceneOneSelceted;
		std::vector<FPoint3> m_VertexBuffer;
		std::vector<int> m_IndexBuffer;

		// scenes
		//first two triangles
		Elite::FPoint3 m_Scene1v1{ -0.75f, 1.5f, 0.f };
		Elite::FPoint3 m_Scene1v2{ -0.75f, 0.f, 0.f };
		Elite::FPoint3 m_Scene1v3{ 0.75f, 0.f, 0.f };
		
		void Scene1();

		// scene two
		void Scene2();
		Parser m_parse;
	};
}

#endif