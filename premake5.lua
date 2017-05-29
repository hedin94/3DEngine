name = "3DEngine"
solution (name)
    language "C++"
    -- flags {"C++11"}
    location "build"
    -- warnings "Extra"
    -- platforms {"Static", "Shared"}
    configurations {"Debug", "Release"}
    filter {"configurations:Debug"}
        defines {"USE_DEBUG"}
        optimize "Off"
        symbols "On"
    filter {"configurations:Release"}
        defines {"RELEASE"}
        optimize "Speed"
        symbols "Off"

------ Program
project (name)
    targetdir "bin"
    kind "ConsoleApp"
    files {"src/**.cc"}
    files {"src/**.cpp"}
    files {"src/**.c"}
    includedirs {"include"}
    filter {"system:windows"} -- Inconsistent...
        defines {"WINDOWS"}
        links { "mingw32", "SDL2main", "SDL2", "SDL2_image", "glew32", "opengl32", "assimp"}
        -- buildoptions { "-mwindows", "-mconsole", "-std=c++11", "-g"}
	buildoptions { "-c", "-g", "-w", "-std=gnu++11", "-Wl,subsystem,windows", "-Wall", "-Wpedantic" }