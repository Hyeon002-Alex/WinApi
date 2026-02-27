#include "stdafx.h"
#include "Core.h"
#include "Systems/Window.h"
#include "Systems/Input.h"
#include "Systems/Time.h"
#include "Game/Program.h"

Core::Core()
{
	m_input = std::make_unique<Input>();
	m_time = std::make_unique<Time>();
}

Core::~Core()
{
}

WPARAM Core::Run(HINSTANCE hInstance)
{
	WinDesc desc;
	desc.appName = L"WinAPI";
	desc.hInstance = hInstance;
	desc.width = WIN_DEFAULT_WIDTH;
	desc.height = WIN_DEFAULT_HEIGHT;

	m_window = std::make_unique<Window>(desc);


	return WPARAM();
}