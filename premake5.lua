assert(_ACTION ~= nil, "no action (vs20**, gmake or xcode for example) provided!")

-- Clean Function --
newaction {
   trigger     = "clean",
   description = "clean the software",
   execute     = function()
      print("Cleaning project")
      os.rmdir("./includr")
   end
}

if _ACTION ~= "vs2019" and _ACTION ~= "clean" then
	error("The only supported compilation platform for this project (includr) on Windows is Visual Studio 2019.")
end


workspace "includr"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	toolset "clang"

	kind "ConsoleApp"

	location "includr"
	objdir "includr/intermediate"

	flags { "NoPCH", "MultiProcessorCompile" }
	defines({
		"_CRT_NONSTDC_NO_WARNINGS",
		"_CRT_SECURE_NO_WARNINGS",
		"STRICT"
	})
	vectorextensions "SSE2"
	configurations { "Release", "Debug" }
	architecture "x86_64"
	--staticruntime "on"

	filter "configurations:Release"
		symbols "Off"
		optimize "Speed"
		floatingpoint "Fast"
		omitframepointer "On"
		flags { "LinkTimeOptimization" }
		--buildoptions { "/Qpar", "/GR-", "/Gw" }

		defines "NDEBUG"
		targetdir "includr/release"

	filter "configurations:Debug"
		symbols "Full"
		optimize "Debug"

		defines { "DEBUG", "_DEBUG" }
		targetdir "includr/debug"

	filter {}

	project "includr"
		files { "source/**.h", "source/**.cpp" }
		vpaths {
			["Header Files/*"] = "source/**.h",
			["Source Files/*"] = "source/**.cpp"
		}
