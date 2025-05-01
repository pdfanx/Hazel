#pragma once

#include "Hazel/Input.h"

namespace Hazel
{
	class WindowsInput : public Input
	{
	public:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int keycode) override;
		std::pair<float, float> GetMousePositionImpl() override;
		bool GetMouseXImpl() override;
		bool GetMouseYImpl() override;
	};
}