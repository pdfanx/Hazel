﻿#include "hzpch.h"

#include "Log.h"

namespace Hazel
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// 设置输出格式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// 创建多线程日志记录器
		s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);	// 设置记录器级别

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