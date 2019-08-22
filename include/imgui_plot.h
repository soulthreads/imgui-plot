#pragma once
#include <cstdint>
#include <imgui.h>

namespace ImGui {
struct PlotConfig {
    struct Values {
        const float *xs = nullptr;
        const float *ys;
        int count;
        int offset = 0;
        ImU32 color = 0;
    } values;
    struct Scale {
        float min = FLT_MAX;
        float max = FLT_MAX;
        enum Type {
            Linear,
            Log10,
        };
        Type type = Linear;
    } scale;
    struct Tooltip {
        bool show = false;
        const char* format = "%g: %8.4g";
    } tooltip;
    struct Grid {
        bool show = false;
        float size = 100;
        int subticks = 10;
    } grid_x, grid_y;
    struct Selection {
        bool show = false;
        uint32_t* start = nullptr;
        uint32_t* length = nullptr;
        uint32_t(*sanitize_fn)(uint32_t);
    } selection;
    struct Lines {
        bool show = false;
        const size_t* indices = nullptr;
        size_t count = 0;
    } lines;
    ImVec2 frame_size = ImVec2(0.f, 0.f);
    float line_thickness = 1.f;
    bool skip_small_lines = true;
    const char* overlay_text = nullptr;
};

enum class PlotStatus {
    nothing,
    selection_updated,
};

IMGUI_API PlotStatus Plot(const char* label, const PlotConfig& conf);
}
