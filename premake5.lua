--premake5.lua
workspace "2D-Physic-Simulator"
	architecture "x64"
	startproject "Test"
	configurations
	{
		"Debug",
		"Release"
	}

outputsDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "2D-Physic-Simulator"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputsDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputsDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Dependencies/include"
	}

	libdirs
	 { 
		"%{prj.name}/Dependencies/libs" 
	}
	links 
	{ 
		"glew/glew32s", 
		"glfw/glfw3_mt",
		"opengl32",
		"ImGui"
	 }

	filter "system:windows"

		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"PYS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PYS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PYS_RELEASE"
		runtime "Release"
		optimize "on"
	
project "Test"
	kind "ConsoleApp"
	location "Test"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputsDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputsDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"2D-Physic-Simulator/Dependencies/include",
		"2D-Physic-Simulator/src"
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"PYS_PLATFORM_WINDOWS"
	}
	
	links
	{
		"2D-Physic-Simulator"
	}
	

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"PYS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PYS_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "PYS_RELEASE"
		optimize "on"

project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputsDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputsDir .. "/%{prj.name}")

	files
	{
		"2D-Physic-Simulator/Dependencies/include/ImGui/**.h",
		"2D-Physic-Simulator/Dependencies/include/ImGui/**.cpp"
	}

	includedirs
	{
		"2D-Physic-Simulator/Dependencies/include"
	}

	libdirs { 
		"2D-Physic-Simulator/Dependencies/libs" 
	}
	links { 
		"glew/glew32", 
		"glfw/glfw3_mt",
		"opengl32"
	 }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
		}
	filter "configurations:Release"
		defines "PYS_RELEASE"
		runtime "Release"
		optimize "on"