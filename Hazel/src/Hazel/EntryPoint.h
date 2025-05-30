#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char* argv[])
{
	Hazel::Log::Init();
	int a = 5;
	HZ_CORE_ERROR("Initialized Log!");
	HZ_INFO("Hello! Var = {0}" , a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif