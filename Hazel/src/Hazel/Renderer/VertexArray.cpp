#include "hzpch.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h" // Ensure this header is included

namespace Hazel {

Hazel::VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "return nullptr");

	case RendererAPI::API::OpenGL:		return new OpenGLVertexArray(); // Ensure OpenGLVertexArray is defined
	}

	HZ_CORE_ASSERT(false, "UnKnown RendererAPI!");
	return nullptr;
}

}