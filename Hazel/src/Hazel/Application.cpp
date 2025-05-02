#include "hzpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

#include <glad/glad.h>

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		// 设置事件回调
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerSatck.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerSatck.PushOverlay(layer);
		layer->OnAttach();
	}

	// 事件处理
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		// HZ_CORE_TRACE("{0}", e.ToString());

		// 优先处理上层事件
		for (auto it = m_LayerSatck.end(); it != m_LayerSatck.begin(); )
		{
			(*--it)->OnEvent(e);
			if(e.m_Handled)
				break;
		}
	}

	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(1, 0, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerSatck)
				layer->OnUpdate();

			/*auto [x, y] = Input::GetMousePosition();
			HZ_CORE_TRACE("{0},{1}", x, y);*/

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}