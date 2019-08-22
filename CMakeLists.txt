# This is only really useable inside another project with imgui already in

set (srcs
	src/imgui_plot.cpp
)

set(hdrs
	include/imgui_plot.h
)

set(IMGUI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/imgui CACHE PATH "Path to Dear ImGui headers")

add_library(imgui_plot ${srcs} ${hdrs})
target_include_directories(imgui_plot PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_include_directories(imgui_plot PRIVATE
	${IMGUI_INCLUDE_DIR}
)
