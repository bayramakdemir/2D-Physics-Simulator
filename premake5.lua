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
	kind "SharedLib"
	language "C++"

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

	libdirs { 
		"%{prj.name}/Dependencies/libs" 
	}
	links { 
		"glew/glew32", 
		"glfw/glfw3_mt",
		"opengl32"
	 }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"PYS_PLATFORM_WINDOWS",
			"PYS_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "PYS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PYS_RELEASE"
		optimize "On"
	
project "Test"
	kind "ConsoleApp"
	location "Test"
	language "C++"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"PYS_PLATFORM_WINDOWS"
		}
		postbuildcommands
		{
			"{COPY} ../bin/" .. outputsDir .. "/%{wks.name}/*.dll ../bin/" .. outputsDir .. "/Test"
		}
		
	filter "configurations:Debug"
		defines "PYS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PYS_RELEASE"
		optimize "On"