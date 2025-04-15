#include "hzpch.h"

#include "Log.h"

namespace Hazel
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// ���������ʽ
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// �������߳���־��¼��
		s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);	// ���ü�¼������

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	Log::Log()
	{

	}

	Log::~Log()
	{

	}
}