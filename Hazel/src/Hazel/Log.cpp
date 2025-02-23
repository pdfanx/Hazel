#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::Init()
	{
		// 日志信息格式
		/*
			%^			start color range (can be used only once)
			%T or %X	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S
			%n			Logger's name
			%v			The actual text to log
			%$			end color range (for example %^[+++]%$ %v) (can be used only once)
		*/
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Hazel");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}
}

