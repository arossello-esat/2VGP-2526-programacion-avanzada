-- premake5.lua
workspace "Parcheesi"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Parcheesi"
   location "build"
   libdirs {"."}

project "PlayerYVuestroNombre"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   files { "VuestroPlayer.h", "VuestroPlayer.cc"}

project "BoardYVuestroNombre"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"

   files { "VuestroParcheesi.cc", "VuestroParcheesi.h" }

project "Parcheesi"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   links {"ParcheesiPlayer","ParcheesiBoard", "PlayerPaco.lib"}

   files
   {
      "game.h",
      "iparcheesi.h",
      "mock_parcheesi.h",

      "game.cc",
      "main.cc"
   }
