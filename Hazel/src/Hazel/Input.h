#pragma once

#include "Core.h"

namespace Hazel {

	class HAZEL_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual bool GetMouseXImpl() = 0;
		virtual bool GetMouseYImpl() = 0;  

	private:
		static Input* s_Instance;
	};


}