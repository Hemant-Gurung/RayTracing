//External includes
#include "SDL.h"
#include "SDL_surface.h"
#include <iostream>
//Project includes
#include "ERenderer.h"
#include "ERGBColor.h"
#include "SceneGraph.h"

Elite::Renderer::Renderer(SDL_Window* pWindow)
{
	// seclet scene to be rendered ------>
	//=================== SELECT SCENE ===============================//
	m_sceneOneSelceted =true;


	//Initialize
	m_Key = keys::none;
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
	m_IsBRDFon = { true };
	m_ShowShadow = true;

	// add objects to Scengraph
	addMaterialsToScengraph();

	// parse the obj file
	if (!m_sceneOneSelceted)
	{
		m_parse.Parse();

		m_VertexBuffer = m_parse.GetVertices();
		m_IndexBuffer = m_parse.GetIndex();

	}
	
	if (m_sceneOneSelceted)
	{

		std::cout << "===TRIANGLE === \n";
		std::cout << "F:frontface\n" << "B: backface\n" << " G:bothface";

		//scene one ----->
		Scene1();
		//camera
		m_Camera = new Camera(FPoint3(0.f, 3.f, 9.f), 45);
	}
	else
	{
		// scene two ----->
		Scene2();
		//camera
		m_Camera = new Camera(FPoint3(0, 3, 9), 45);
		//m_Camera = new Camera(FPoint3(0.f, 3.f, 9.f), 45);
	}
	
	// aspect ratio calculation.
	m_AspectRatio = { ((float)m_Width / (float)m_Height) };

}
Elite::Renderer::~Renderer()
{
	for (GeometricObjects* obj : SceneGraph::GetInstance()->GetObjectFromScence())
	{
		delete obj;
	}
	delete m_Camera;
}

void Elite::Renderer::Render()
{
	SDL_LockSurface(m_pBackBuffer);

	// field of view calculation
	m_FOV = tan(ToRadians(m_Camera->m_Fov) / 2);

	// point to shade initialize
	FPoint3 pointToShade;
	RGBColor BRDFrgb{};
	RGBColor irradiance{};

	// create bounding box for the triangle
	

	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			//change into screen space, taking aspect ratio into account makes it in world space
			float xs = (2 * ((c + 0.5f) / m_Width) - 1.f) * m_AspectRatio * m_FOV;
			float ys = (1 - 2 * ((r + 0.5f) / m_Height)) * m_FOV;

			// this is in world space beacause of aspect ratio
			Elite::FPoint4 PixelWorldLocation{ -xs,ys,1.f,0.f };

			//look at matrix i.e ONB camera
			FMatrix4 lookAt = m_Camera->CameraLookAt();

			//Transform to take camera orientation into account
			FPoint4 TransformPix = Elite::FPoint4((lookAt * PixelWorldLocation));

			//calculate ray 
			Ray ray = Ray(m_Camera->m_Position, (TransformPix).xyz - m_Camera->m_Position);

			//check for closest hit record
			float ClosestHitRecord{ FLT_MAX };


			//FPoint3 LightPos;
			RGBColor radianceColor{};
			// go through all the objects in scenegraph
			for (GeometricObjects* object : SceneGraph::GetInstance()->GetObjectFromScence())
			{

				// check if object is hit by ray
				if (object->Hit(ray, object->m_Hit))
				{
					//check if it is closese hit record
					if (object->m_Hit.tValue <= ClosestHitRecord)
					{
						// assign closese hit
						ClosestHitRecord = object->m_Hit.tValue;

						//point to shade calculation
						pointToShade = ray.At(ClosestHitRecord);

						// run through all the lights in the scence
						for (Lights* light : SceneGraph::GetInstance()->GetLights())
						{
							Elite::FPoint3 lightPosition = light->GetDirection();
							
							FVector3 lightToPoint = lightPosition - pointToShade;

							// for hard shadow check if light is visible from pointToshade
							Elite::FVector3 rayDir = Elite::GetNormalized(lightToPoint);

							//make point to light ray 
							Ray pointRay = Ray(pointToShade, rayDir);
							pointRay.m_tMin = 0.001f;
							pointRay.m_tMax = Elite::Magnitude(lightToPoint);


							// check if pointtoshade is seen from light
							if (!IsHit(pointRay))
							{
								// calculate cosine i.e visibility
								float cosine{ Dot(object->m_Hit.normal,rayDir) };

								// if visible
								if (cosine > 0)
								{
									// call shade functionda in materials
									BRDFrgb = object->m_material->Shade(object->m_Hit,rayDir, { Elite::GetNormalized(m_Camera->m_Position - pointToShade) });

									// get irradiancec
									irradiance = light->GetIrridiance(pointToShade);
									if (m_IsBRDFon)radianceColor += irradiance * cosine * BRDFrgb;
									else radianceColor += irradiance * cosine;
								}
								
							}

							
						}
						
					}
					
					radianceColor.MaxToOne();
				}
				
			}
		

			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(radianceColor.r * 255.f),
				static_cast<uint8_t>(radianceColor.g * 255.f),
				static_cast<uint8_t>(radianceColor.b * 255.f));
		}
	}

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

void Elite::Renderer::Update()
{
	//KeySDL input
	for (GeometricObjects* obj : SceneGraph::GetInstance()->GetObjectFromScence())
	{
		
		FPoint3 midpoint = { (m_Scene1v1.x + m_Scene1v3.x) / 2,(m_Scene1v1.y + m_Scene1v3.y) / 2,(m_Scene1v1.z + m_Scene1v3.z) / 2 };
		if (m_sceneOneSelceted)
		{
			obj->Rotate(obj->m_Center);
		}
		else
		{
			obj->RotateObject(obj->m_Center);
		}
		
		obj->update();
	}

	m_Camera->GetRelativeMouseState();//useState();

	SwitchKeyMouse();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT]) {
		m_Key = keys::left;
	}
	else if (state[SDL_SCANCODE_RIGHT]) {
		m_Key = keys::right;
	}
	else if (state[SDL_SCANCODE_E])
	{
		m_Key = keys::T;
	}
	else if (state[SDL_SCANCODE_Q])
	{
		if (m_ShowShadow)
		{
			m_ShowShadow = false;
		}
		else m_ShowShadow = true;
	}
	else m_Key = keys::none;
}



void Elite::Renderer::SwitchKeyMouse()
{
	switch (m_Key)
	{
	case keys::none:
		break;
	case keys::left:
		//set Fov camera
		//m_Camera->SetFov(5);
		printf("LEFT key  Pressed.\n");
		m_Key = keys::none;
		break;
	case keys::right:
		//m_Camera->SetFov(-5);
		printf("RIGHT key  Pressed.\n");
		m_Key = keys::none;
		break;
	case keys::up:
		break;
	case keys::down:
		break;
	case keys::T:
		if (m_IsBRDFon)
		{
			m_IsBRDFon = false;
		}
		else m_IsBRDFon = true;
		break;

	default:
		break;
	}


}

bool Elite::Renderer::IsHit(Ray& lightRay)
{
	HitRecord hit;
	if (m_ShowShadow)
	{
		for (GeometricObjects* object : SceneGraph::GetInstance()->GetObjectFromScence())
		{
			if (object->Hit(lightRay, hit))
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
	// go through all the objects, if not even one is hit return false
	return false;
}

void Elite::Renderer::addMaterialsToScengraph()
{
	SceneGraph* scenegraph{ SceneGraph::GetInstance() };

	
	// from pdf
	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{ 0.972f,0.960f, 0.915f }, 1.f, 60, 1.f, 1.f)); // metal rough
	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{ 0.972f,0.960f, 0.915f }, 1.f, 60, 1.f, 0.6f)); // medium rough metal 
	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{ 0.972f,0.960f, 0.915f }, 1.f, 60, 1.f, 0.1f)); // smooth metal

	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{ 0.75f,0.75f, 0.75f }, 1.f, 60, 0.f, 1.f)); // rough
	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{ 0.75f, 0.75f, 0.75f }, 1.f, 60, 0.f, 0.6f)); // metal smooth
	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{ 0.75f, 0.75f, 0.75f }, 1.f, 60, 0.f, 0.1f)); //metal rough

	//plane material
	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{ 0.49f,0.57f,0.57f }, 1.f, 60, 0.f, 0.8f)); // non metal
	// triangle material
	scenegraph->AddMaterial(new Material_Lambert(1.f, RGBColor{1.f,1.f,1.f }, 1.f, 60, 0.f, 1.f)); // non metal
}

// scenes
void Elite::Renderer::Scene1()
{
	SceneGraph* scenegraph{ SceneGraph::GetInstance() };


	// ==================NEW COORDINATES=============>

	//LIGHTS
	scenegraph->AddLights(new PointLight({ 0,5,-5 }, { 1.f,0.61f,0.45f }, 25));
	scenegraph->AddLights(new PointLight({ -2.5,5,5 }, { 1.f,0.8f,0.45f }, 25));
	scenegraph->AddLights(new PointLight({ 2.5,2.5,5 }, { 0.34f,0.47f,0.68f }, 25));
	

	//// Metal Sphere
	scenegraph->AddObject(new Sphere({ -1.75,1,0. }, { 0.8f,0.8f,0.8f }, 0.75f, scenegraph->GetInstance()->GetMaterial(0)));
	scenegraph->AddObject(new Sphere({ 0,1,0 },      { 0.8f,0.8f,0.8f }, 0.75f, scenegraph->GetInstance()->GetMaterial(1)));
	scenegraph->AddObject(new Sphere({ 1.75,1,0},    { 0.8f,0.8f,0.8f }, 0.75f, scenegraph->GetInstance()->GetMaterial(2)));
	
	//// Dielectric sphere
	scenegraph->AddObject(new Sphere({ -1.75,3,0 }, { 0.8f,0.8f,0.8f }, 0.75f, scenegraph->GetInstance()->GetMaterial(3)));
	scenegraph->AddObject(new Sphere({ 0.0,3.f,0 }, { 0.8f,0.8f,0.8f }, 0.75f, scenegraph->GetInstance()->GetMaterial(4)));
	scenegraph->AddObject(new Sphere({ 1.75,3,0 },  { 0.8f,0.8f,0.8f }, 0.75f, scenegraph->GetInstance()->GetMaterial(5)));


//	pLANES
	scenegraph->AddObject(new Plane({ 0.f,0.f,0.f }, { 0.f,1.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ 0.f,0.f,-10.f }, { 0.f,0.f,1.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ 0.f,10.f,0.f }, { 0.f,-1.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ 5.f,0.f,0.f }, { -1.f,0.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ -5.f,0.f,0.f }, { 1.f,0.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));

	

	// first scence two triangles
	m_Scene1v1.y = m_Scene1v1.y + 4.5f;
	m_Scene1v2.y = m_Scene1v2.y + 4.5f;
	m_Scene1v3.y = m_Scene1v3.y + 4.5f;
	scenegraph->AddObject(new Triangle(FPoint3{ 0,0,0 }, { 1,0,0 }, m_Scene1v1, m_Scene1v2, m_Scene1v3, scenegraph->GetInstance()->GetMaterial(7)));

	m_Scene1v1.x = m_Scene1v1.x - 2;
	m_Scene1v2.x = m_Scene1v2.x - 2;
	m_Scene1v3.x = m_Scene1v3.x - 2;

	scenegraph->AddObject(new Triangle(FPoint3{ 0,0,0 }, { 1,0,0 }, m_Scene1v1, m_Scene1v2, m_Scene1v3, scenegraph->GetInstance()->GetMaterial(7)));

	m_Scene1v1.x = m_Scene1v1.x + 4;
	m_Scene1v2.x = m_Scene1v2.x + 4;
	m_Scene1v3.x = m_Scene1v3.x + 4;
	scenegraph->AddObject(new Triangle(FPoint3{ 0,0,0 }, { 1,0,0 }, m_Scene1v1, m_Scene1v2, m_Scene1v3, scenegraph->GetInstance()->GetMaterial(7)));
	
	//add box
	scenegraph->AddBox(new Box(Elite::FPoint3(0, 0, 0), 400.f, 400.f, { 0,1,0 }, Elite::RGBColor(0, 0, 1), scenegraph->GetInstance()->GetMaterial(6), Elite::FPoint3{ 0,0,0 }));
	m_Box = SceneGraph::GetInstance()->GetBoxFromScence().front();
}

void Elite::Renderer::Scene2()
{
	SceneGraph* scenegraph{ SceneGraph::GetInstance() };

	//LIGHTS
	scenegraph->AddLights(new PointLight({ 1,5,-5 }, { 1.f,0.61f,0.45f }, 25));
	scenegraph->AddLights(new PointLight({ 0,5,5 }, { 1.f,0.8f,0.45f }, 25));
	scenegraph->AddLights(new PointLight({ 2.5,2.5,5 }, { 0.34f,0.47f,0.68f }, 25));
	scenegraph->AddLights(new PointLight({ 2,4,5 }, { 0.5f,0.6f,0.3f }, 25));
	
	// add obj vetrices
	scenegraph->AddObject(new TriangleMesh({ 0,0,0 }, { 1,0,0 }, scenegraph->GetInstance()->GetMaterial(7), m_VertexBuffer, m_IndexBuffer));

	// new
	scenegraph->AddObject(new Plane({ 0.f,0.f,0.f }, { 0.f,1.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ 0.f,0.f,-10.f }, { 0.f,0.f,1.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ 0.f,10.f,0.f }, { 0.f,-1.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ 5.f,0.f,0.f }, { -1.f,0.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	scenegraph->AddObject(new Plane({ -5.f,0.f,0.f }, { 1.f,0.f,0.f }, { 0.5f,0.5f,0.5f }, scenegraph->GetInstance()->GetMaterial(6)));
	
}

