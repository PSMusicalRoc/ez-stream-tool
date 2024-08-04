#include "ColorInput.h"

#include "imgui.h"
#include <iostream>
#include "misc/cpp/imgui_stdlib.h"

#include "Update.h"

ColorInput::ColorInput(int x, int y, int width, const std::string& label, const std::string& json_label, float r, float g, float b)
    :Widget(x, y, width, 0)
{
    this->_label = label;
    this->_json_label = json_label;
    this->_color = ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f); //Red, Green, Blue, Alpha

    createPallet();

    Update::get()->set(_json_label, getHexCode((this->_color).x, (this->_color).y, (this->_color).z, (this->_color).w));
}

void ColorInput::render()
{
    
    ImGui::SetCursorPos(ImVec2(_x, _y));
    ImGui::SetNextItemWidth(_width);

    ImGuiColorEditFlags color_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoDragDrop;
    bool popup_open = ImGui::ColorButton((_label + " Button").c_str(), _color, color_flags); 
    if (popup_open)
    {
        ImGui::OpenPopup(("colorPicker" + _label).c_str());
    }

    if (ImGui::BeginPopup(("colorPicker" + _label).c_str()))
    {
        ImGui::Text(_label.c_str());
        ImGui::ColorPicker4(("##" + _label).c_str(), (float*)&_color, color_flags);

        ImGui::BeginGroup(); 
        ImGui::Text("Palette");
        ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop;
        for (int n = 0; n < IM_ARRAYSIZE(_saved_palette); n++)
        {
            if (ImGui::ColorButton(("palette color " + n), _saved_palette[n], palette_button_flags, ImVec2(20, 20)))
            {
                _color = ImVec4(_saved_palette[n].x, _saved_palette[n].y, _saved_palette[n].z, _saved_palette[n].w);
            }
            if(n != IM_ARRAYSIZE(_saved_palette) - 1)
            {
                ImGui::SameLine();
            }  
        }
        ImGui::EndGroup();

        ImGui::EndPopup();

        Update::get()->set(_json_label, getHexCode((this->_color).x, (this->_color).y, (this->_color).z, (this->_color).w));
    }
}

void ColorInput::createPallet()
{
    //red
    _saved_palette[0].x = 1.0f;
    _saved_palette[0].y = 0.0f;
    _saved_palette[0].z = 0.0f;
    _saved_palette[0].w = 1.0f;
    //blue
    _saved_palette[1].x = 0.0f;
    _saved_palette[1].y = 0.0f;
    _saved_palette[1].z = 1.0f;
    _saved_palette[1].w = 1.0f;

    //I dont know what the other colors are
    //green
    _saved_palette[2].x = 0.0f;
    _saved_palette[2].y = 1.0f;
    _saved_palette[2].z = 0.0f;
    _saved_palette[2].w = 1.0f;
    //yellow
    _saved_palette[3].x = 1.0f;
    _saved_palette[3].y = 1.0f;
    _saved_palette[3].z = 0.0f;
    _saved_palette[3].w = 1.0f;
}

ImVec4 ColorInput::getColor()
{
    return _color;
}

std::string ColorInput::getLabel()
{
    return _label;
}

std::string ColorInput::getHexCode(float r, float g, float b, float a)
{
    //there are some rounding errors sometimes

    int red = (r * 255);
    int green = (g * 255);
    int blue = (b * 255);
    int alpha = (a * 255);

    char hexStr[16];
    snprintf(hexStr, sizeof(hexStr), "#%02x%02x%02x%02x", (red & 0xff), (green & 0xff), (blue & 0xff), (alpha & 0xff));
    return hexStr;
}


