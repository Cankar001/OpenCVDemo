project "OpenCVDemo"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	entrypoint "mainCRTStartup"

	targetdir ("bin/" .. outputdir)
	debugdir ("bin/" .. outputdir)
	objdir ("bin-obj/" .. outputdir)
	
	files
	{ 
		"src/**.h",
		"src/**.cpp"
	}
	
	includedirs
	{
		"src",
		"%{IncludeDir.opencv}"
	}
	
	libdirs
	{
		"%{LibDir.opencv_lib_path}"
	}
	
	postbuildcommands
	{
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_world455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_text455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_tracking455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_video455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_videoio455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_face455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_stitching455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_highgui455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_imgproc455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_core455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_dnn455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_calib3d455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_features2d455d.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_flann455d.dll %{cfg.targetdir}"),

		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_videoio_msmf455_64d.dll %{cfg.targetdir}"),
			
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_world455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_text455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_tracking455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_video455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_videoio455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_face455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_highgui455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_imgproc455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_core455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_dnn455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_calib3d455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_features2d455.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_flann455.dll %{cfg.targetdir}"),

		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_videoio_msmf455_64.dll %{cfg.targetdir}"),
		("{COPY} %{wks.location}OpenCVDemo/vendor/opencv/lib/opencv_videoio_ffmpeg455_64.dll %{cfg.targetdir}"),
	}
	
	filter "configurations:Debug"
		symbols "On"
		defines "OPENCVDEMO_DEBUG"
	
		links
		{
			"%{LibDir.opencv_world_debug}",
			"%{LibDir.opencv_text_debug}",
			"%{LibDir.opencv_tracking_debug}",
			"%{LibDir.opencv_video_debug}",
			"%{LibDir.opencv_videoio_debug}",
			"%{LibDir.opencv_face_debug}",
			"%{LibDir.opencv_stitching_debug}",
			"%{LibDir.opencv_highgui_debug}",
		}
	
	filter "configurations:Release"
		optimize "On"
		defines "OPENCVDEMO_RELEASE"
	
		links
		{
			"%{LibDir.opencv_world}",
			"%{LibDir.opencv_text}",
			"%{LibDir.opencv_tracking}",
			"%{LibDir.opencv_video}",
			"%{LibDir.opencv_videoio}",
			"%{LibDir.opencv_face}",
			"%{LibDir.opencv_stitching}",
			"%{LibDir.opencv_highgui}",
		}
	
	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		systemversion "latest"
	
		links
		{
			"OpenCV"
		}
	
	filter "system:macos"
		systemversion "latest"
		