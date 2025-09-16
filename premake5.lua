require "export-compile-commands"

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

  local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Raykout"
  kind "ConsoleApp"
  language "C++"
  warnings "Default"

  targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
  objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
  debugdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")

  postbuildcommands {
   "{MKDIR} ".."\"%{wks.location}../bin/\"",
   "{COPYFILE} %[%{!cfg.buildtarget.abspath}] \"%{wks.location}../bin/%{cfg.buildtarget.name}\"",
   "{COPYDIR} \"%{wks.location}../assets/\" \"%{wks.location}../bin/assets\"",
   "{COPYDIR} \"%{wks.location}../assets/\" \"%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/assets\"",
  }

  -- Generate asm
  -- buildoptions {"/FA"}

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
    "deps/soloud/lib/",
  }

  links {"raylib", "soloud_x64", "winmm", "gdi32", "opengl32"}
