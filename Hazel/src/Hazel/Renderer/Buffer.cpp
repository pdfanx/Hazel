#include "hzpch.h"
#include "Buffer.h"

#include "Renderer.h"

// #ifdef HZ_PLATFORM_WINDOWS
#include "Platform/OpenGL/OpenGLBuffer.h"
// #endif

namespace Hazel {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "return nullptr");

// #ifdef HZ_PLATFORM_WINDOWS
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
// #endif
		}

		HZ_CORE_ASSERT(false, "UnKnown RendererAPI!");
		return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "return nullptr");

// #ifdef HZ_PLATFORM_WINDOWS
		case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count);
// #endif
		}

		HZ_CORE_ASSERT(false, "UnKnown RendererAPI!");
		return nullptr;
	}
}