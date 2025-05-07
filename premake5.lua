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
IncludeDir["glm"] = "Hazel/vendor/glm"

group "ThirdParty"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"
group ""

project "Hazel"
	location "Hazel"
	kind "StaticLib" -- or "SharedLib" for dynamic library
	language "C++"
	staticruntime "on"
	cppdialect "C++17"

	targetdir ("bin/" ..  outputdir .. "/%{prj.name}")
	objdir ("bin-int/" ..  outputdir .. "/%{prj.name}")
	
	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"ImGui",
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		buildoptions "/utf-8"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "on"

	filter "configurations:DIST"
		defines "HZ_DIST"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"
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
		"Hazel/src",
		"Hazel/vendor",
		"%{IncludeDir.glm}",
	}

	links
	{
		"Hazel",
	}

	filter "system:windows"

		systemversion "latest"

		defines
		{
			"HZ_PLATFORM_WINDOWS";
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		buildoptions "/utf-8"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "on"

	filter "configurations:DIST"
		defines "HZ_DIST"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "on"