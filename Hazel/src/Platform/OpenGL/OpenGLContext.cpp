#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Hazel
{

	OpenGLContext::OpenGLContext(GLFWwindow* glfwWindow)
		: m_WindowHandle(glfwWindow)
	{
		HZ_CORE_ASSERT(m_WindowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad");

		HZ_CORE_INFO("OpenGL Renderer: ");
		HZ_CORE_INFO(" Vendor: {0}", (const char *)glGetString(GL_VENDOR));
		HZ_CORE_INFO(" Renderer: {0}", (const char *)glGetString(GL_RENDERER));
		HZ_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

} 