# imgui-plot
An improved plot widget for [Dear ImGui](https://github.com/ocornut/imgui/), aimed at displaying audio data

## TOC
1. [Screenshots](#screenshots)
2. [Rationale](#rationale)
3. [Usage](#usage)
4. [Installation](#installation)
5. [FAQ](#faq)

## Screenshots
Displaying waveform and spectrum:  
![Displaying Waveform and Spectrum](https://linuxoids.net/static/imgui-plot/waveform_and_spectrum.png)

Custom tooltip:  
![Custom Tooltip](https://linuxoids.net/static/imgui-plot/custom_tooltip.png)

Selection example:  
![Selection Example](https://linuxoids.net/static/imgui-plot/selection_example.gif)

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

Selection example (gif above):
```cpp
constexpr size_t buf_size = 512;
static float x_data[buf_size];
static float y_data1[buf_size];
static float y_data2[buf_size];
static float y_data3[buf_size];

void generate_data() {
    constexpr float sampling_freq = 44100;
    constexpr float freq = 500;
    for (size_t i = 0; i < buf_size; ++i) {
        const float t = i / sampling_freq;
        x_data[i] = t;
        const float arg = 2 * M_PI * freq * t;
        y_data1[i] = sin(arg);
        y_data2[i] = y_data1[i] * -0.6 + sin(2 * arg) * 0.4;
        y_data3[i] = y_data2[i] * -0.6 + sin(3 * arg) * 0.4;
    }
}

void draw_multi_plot() {
    static const float* y_data[] = { y_data1, y_data2, y_data3 };
    static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
    static uint32_t selection_start = 0, selection_length = 0;

    ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    // Draw first plot with multiple sources
    ImGui::PlotConfig conf;
    conf.values.xs = x_data;
    conf.values.count = buf_size;
    conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
    conf.values.ys_count = 3;
    conf.values.colors = colors;
    conf.scale.min = -1;
    conf.scale.max = 1;
    conf.tooltip.show = true;
    conf.grid_x.show = true;
    conf.grid_x.size = 128;
    conf.grid_x.subticks = 4;
    conf.grid_y.show = true;
    conf.grid_y.size = 0.5f;
    conf.grid_y.subticks = 5;
    conf.selection.show = true;
    conf.selection.start = &selection_start;
    conf.selection.length = &selection_length;
    conf.frame_size = ImVec2(buf_size, 200);
    ImGui::Plot("plot1", conf);

    // Draw second plot with the selection
    // reset previous values
    conf.values.ys_list = nullptr;
    conf.selection.show = false;
    // set new ones
    conf.values.ys = y_data3;
    conf.values.offset = selection_start;
    conf.values.count = selection_length;
    conf.line_thickness = 2.f;
    ImGui::Plot("plot2", conf);

    ImGui::End();
}

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

## FAQ
### How do I do _x_?
If something isn't obvious or your think my design is bad, please file away an issue, I'll take a look at it.

If you want to have some new feature, issues and PRs are welcome too.
