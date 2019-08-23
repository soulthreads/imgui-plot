# imgui-plot
An improved plot widget for Dear ImGui, aimed at displaying audio data

## Screenshots
Displaying waveform and spectrum:

![Displaying Waveform and Spectrum](https://linuxoids.net/static/waveform_and_spectrum.png)

Custom tooltip:

![Custom Tooltip](https://linuxoids.net/static/custom_tooltip.png)

## Rationale
The `PlotLines()` function in Dear ImGui is nice and simple, but it does lack some basic features, such as grids, logarithmic scaling, custom tooltips etc.

My work involves handling lots of waveforms and their spectrums, so I decided to extend `PlotLines()` with these features to display this data in a nice(r) way.

## Usage
Instead of feeding all the parameters into plot function via its arguments, I decided that, with all the configurability, it would be cleaner to have a struct `PlotConfig` with all the neccessary stuff in it. See `imgui_plot.h` for its description.

Simple usecase:
```cpp
ImGui::PlotConfig conf;
conf.values.xs = x_data; // this line is optional
conf.values.ys = y_data;
conf.values.count = data_count;
conf.scale.min = -1;
conf.scale.max = 1;
conf.tooltip.show = true;
conf.tooltip.format = "x=%.2f, y=%.2f";
conf.grid_x.show = true;
conf.grid_y.show = true;
conf.frame_size = ImVec2(400, 400);
conf.line_thickness = 2.f;

ImGui::Plot("plot", conf);
```

## Installation
Just copy `include/imgui_plot.h` and `src/imgui_plot.cpp` to where your imgui is, and it should work like that.

### CMake
Alternatively, you can use [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) like this:

```cmake
include(FetchContent)
FetchContent_Declare(
    imgui_plot
    GIT_REPOSITORY https://github.com/soulthreads/imgui-plot.git
    GIT_TAG v0.1.0
    EXCLUDE_FROM_ALL
)
FetchContent_GetProperties(imgui_plot)
if(NOT imgui_plot_POPULATED)
    FetchContent_Populate(imgui_plot)
    add_subdirectory(${imgui_plot_SOURCE_DIR} ${imgui_plot_BINARY_DIR})
endif()
```
and then just link `imgui_plot` into your application. If you have ImGui located not in `{repo}/imgui` you can set `IMGUI_INCLUDE_DIR` variable to the according value.
