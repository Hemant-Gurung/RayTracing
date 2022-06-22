#include "Camera.h"
#include <iostream>
#include "SDL.h"
#include "SDL_surface.h"

Camera::Camera(Elite::FPoint3 origin, float Fov)
	:m_Position{ origin }
	, m_Fov{ Fov }
	, m_Sensitivity{ 0.15f }
	,m_Forward{0,0,-1}
	,m_Right{1,0,0}
	,m_Up{0,1,0}
{

}

Ray Camera::GetRay(Elite::FVector3 Dir) const
{
	Ray r(m_Position, Dir);

	return r;
}

Elite::FMatrix4 Camera::CameraLookAt()
{
	
	Elite::FVector3 worldUp{ 0,1,0 };
	
	m_Right = Elite::GetNormalized(Elite::Cross(worldUp, m_Forward));
	m_Up = Elite::GetNormalized(Elite::Cross(m_Forward, m_Right));

	return Elite::FMatrix4
		(
			m_Right.x, m_Up.x, m_Forward.x, m_Position.x,  
			m_Right.y, m_Up.y, m_Forward.y, m_Position.y,
			m_Right.z, m_Up.z, m_Forward.z, m_Position.z,
			0, 0, 0, 1
		);
}


void Camera::GetRelativeMouseState()
{
	
	int x{};
	int y{};
	Uint32 buttons = SDL_GetRelativeMouseState(&x, &y); 

	if (buttons == 1)
	{
		m_MousePosX = x *0.01f;
		m_Forward = Elite::MakeRotationY(m_MousePosX * m_Sensitivity).operator*(m_Forward);
		//m_Fov += x*0.24f;
	}
	
	if (buttons == 4)//right
	{
		m_Forward = Elite::MakeRotationY(x*0.01f * m_Sensitivity).operator*(m_Forward);
		m_Forward = Elite::MakeRotationY(y*0.01f * m_Sensitivity).operator*(m_Forward);
	
	}

	if (buttons == 5)//left and right
	{
		m_Position += y * m_Sensitivity * m_Up;
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
		m_Position +=  m_Sensitivity * m_Right;
	}
	
	if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
	
		m_Position -= m_Sensitivity * m_Right;
	}
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP] ) {
		m_Position += m_Sensitivity * m_Forward;
		
	}
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
		m_Position -= m_Sensitivity * m_Forward;
		
	}
}

void Camera::GetRelativeKeyState()
{
	
}

void Camera::SetFov(float value)
{
	m_Fov += value;
}







