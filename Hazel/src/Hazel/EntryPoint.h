#pragma once

#ifdef HZ_PLATFORM_WINDOWS
// 人口点位于Hazel引擎内部
extern Hazel::Application* Hazel::CreateApplication();

void main(int argc,char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	int a = 5;
	HZ_INFO("Hello! {0}",a);

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif