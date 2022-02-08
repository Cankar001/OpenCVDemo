include "./vendor/bin/premake/solution_items.lua"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies.lua"

workspace "OpenCVDemo"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "OpenCVDemo"
	
	solution_items
	{
		".editorconfig"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

	group "Dependencies"
		include "OpenCVDemo/vendor/opencv"
	group ""
	
	include "OpenCVDemo"
	
	