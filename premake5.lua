workspace "Hazel"
	architecture "x64"
	startproject "SandBox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"
IncludeDir["imgui"] = "Hazel/vendor/imgui"

group "ThirdParty"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"
group ""

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..  outputdir .. "/%{prj.name}")
	
	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"ImGui",
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		buildoptions "/utf-8"
		symbols "ON"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "ON"

	filter "configurations:DIST"
		defines "HZ_DIST"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "ON"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off" 
	-- static runtime is off for shared libraries
	-- static runtime is on Set <RuntimeLibrary> to MultiThreaded (/MT) for static runtime
	-- static runtime is off Set <RuntimeLibrary> to MultiThreadedDLL (/MD) for dynamic runtime
	
	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..  outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links
	{
		"Hazel",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS";
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		buildoptions "/utf-8"
		symbols "ON"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "ON"

	filter "configurations:DIST"
		defines "HZ_DIST"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "ON"