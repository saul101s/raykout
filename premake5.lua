workspace "Raykout"
  location(path.join(path.getdirectory(_SCRIPT), "build"))
  startproject "Raykout"

  configurations {"Release", "Debug"}
  platforms {"x64", "x86"}

  filter "configurations:x86"
    architecture "x86"

  filter "configurations:x64"
    architecture "x86_64"

  filter "configurations:Debug"
    runtime "Debug"
    symbols "On"
    targetsuffix "_d"

  filter "configurations:Release"
    runtime "Release"
    optimize "On"

  outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Raykout"
  kind "ConsoleApp"
  language "C++"
  warnings "Default"

  targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
  objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

  postbuildcommands {
   "{MKDIR} ".."\"%{wks.location}../bin/\"",
   "{COPYFILE} %[%{!cfg.buildtarget.abspath}] \"%{wks.location}../bin/%{cfg.buildtarget.name}\""
  }

  -- Generate asm
  buildoptions {"/FA"}

  files {
    "include/*.h",
    "include/**/*.h",
    "src/*.cc",
    "src/**/*.cc",
  }

  includedirs {
    "include/",
    "deps/**/include/",
  }

  libdirs { 
    "deps/raylib/lib/",
  }

  links {"raylib", "winmm", "gdi32", "opengl32"}
