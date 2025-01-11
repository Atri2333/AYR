workspace "AYR"
    architecture "x64"
    configurations { "Debug", "Release" }

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AYR"
    location "AYR"
    kind "SharedLib"
    language "C++"
    targetdir("bin/" .. output_dir .. "/%{prj.name}")
    objdir("bin-int/" .. output_dir .. "/%{prj.name}")
    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
    -- includedirs { "src" }
    includedirs { "AYR/vendor/include" }
    defines { "AYR_BUILD_DLL" }

    postbuildcommands
    {
        "{MKDIR} ../bin/" .. output_dir .. "/Outputer",
        "{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. output_dir .. "/Outputer\""
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

    filter "configurations:Debug"
        defines { "AYR_DEBUG" }
        runtime "Debug"
        symbols "On"
        
    filter "configurations:Release"
        defines { "AYR_RELEASE" }
        runtime "Release"
        optimize "On"

project "Outputer"
    location "Outputer"
    kind "ConsoleApp"
    language "C++"
    targetdir("bin/" .. output_dir .. "/%{prj.name}")
    objdir("bin-int/" .. output_dir .. "/%{prj.name}")
    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
    includedirs { "AYR" }
    links { "AYR" }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

    filter "configurations:Debug"
        defines { "AYR_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "AYR_RELEASE" }
        runtime "Release"
        optimize "On"