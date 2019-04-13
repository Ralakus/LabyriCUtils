
is_64_bit = true





linux, windows = 1, 2

build_os = linux

if package.config:sub(1,1) == '\\' then
    build_os = windows
end

workspace "Labyri"
    language "C"
    cdialect "C11"

    location "build"

    if is_64_bit then
        architecture "x86_64"
    else
        architecture "x86"
    end

    configurations { "Debug", "Release" }

    filter { "configurations:Debug" }
            symbols "On"

    filter { "configurations:Release" }
            optimize "On"
    filter { }

    targetdir ("build/bin/")

    objdir ("build/obj/")


project "labcutils"
    kind "StaticLib"

    files { "src/**.h", "src/**.c"}

    if is_64_bit then
        defines { "LAB_64_BIT" }
    else 
        defines { "LAB_32_BIT" }
    end

    filter "configurations:Debug"
        defines { "DEBUG" }

        if build_os == linux then 
            buildoptions { "-fprofile-arcs", "-ftest-coverage" }
            linkoptions  { "-fprofile-arcs", "-ftest-coverage" }
        end

    filter "configurations:Release"
        defines { "NDEBUG" }

    filter {}