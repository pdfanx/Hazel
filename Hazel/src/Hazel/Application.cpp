#include "hzpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"

#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/RendererAPI.h"

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

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// 28.First triangle
		// Vertex Array
		// Vertex Buffer
		// Index Buffer
		// Shader

		/////////////////////////////////////////////////////////////////////
		/// 绘制三角形 ///////////////////////////////////////////////////////

		// 创建顶点数组
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,	-0.5f,	0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f,	-0.5f,	0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,	0.5f,	0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		// 创建顶点缓冲区
        std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		// error： 两次隐式转换；需要使用 std::initializer_list<BufferElement>
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// 创建索引缓冲区	
		uint32_t indices[3] = { 0,1,2 };
		
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;	
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;
	
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		/////////////////////////////////////////////////////////////////////
		/// 绘制正方形 ///////////////////////////////////////////////////////
		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };

		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string blueshadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;			

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string blueshaderfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
	
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Shader(blueshadervertexSrc, blueshaderfragmentSrc));
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
			// 定义背景颜色
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_BlueShader->Bind();
			Renderer::Submit(m_SquareVA);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerSatck)
				layer->OnUpdate();

			/*auto [x, y] = Input::GetMousePosition();
			HZ_CORE_TRACE("{0},{1}", x, y);*/

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerSatck)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}