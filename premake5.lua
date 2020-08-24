workspace "mycraft"
	architecture "x64"
	startproject "mycraft"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "mycraft/vendor/GLFW/include"
IncludeDir["glad"] = "mycraft/vendor/glad/include"
IncludeDir["glm"] = "mycraft/vendor/glm/include"

--include "mycraft/vendor/GLFW" --include GLFW premake here
include "mycraft/vendor/glad" --include GLAD premake here
	
project "mycraft"
	location "mycraft"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	--pchheader "craftpch.h"
	--pchsource "mycraft/src/craftpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.glsl"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		--"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}"
	}
	
	libdirs 
	{
		"%{prj.name}/vendor/GLFW/lib",
	}
	
	links
	{
		"glfw3.lib",
		"glad",
		"opengl32.lib"
	}
		
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"HZ_PLATFORM_WINDOWS", 
		}
		
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "On"	
		
	filter "configurations:Dist"
		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "On"
		