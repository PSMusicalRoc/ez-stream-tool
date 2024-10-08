#include "ScoreInput.h"

#include "imgui.h"
#include <iostream>
#include "misc/cpp/imgui_stdlib.h"

#include "Update.h"

ScoreInput::ScoreInput(int x, int y, int width, const std::string& label, const std::string& json_label)
    :Widget(x, y, width, 0)
{
    this->_label = label;
    this->_json_label = json_label;
    this->_score = 0;

    Update::get()->set(json_label, 0);
}

void ScoreInput::render()
{
    
    ImGui::SetCursorPos(ImVec2(_x, _y));
    ImGui::SetNextItemWidth(_width);
    if(ImGui::InputScalar(("##" + _label).c_str(), ImGuiDataType_U16, &_score, NULL, NULL, "%u"))
    {
        Update::get()->set(_json_label, _score);
    }
    ImGui::SetCursorPos(ImVec2(_x, _y - 25));
    if (ImGui::ArrowButton(("##" + _label + "upButton").c_str(), ImGuiDir_Up)) 
    { 
        if (_score < 65535)
        {
            _score = 65535;
        }
        Update::get()->set(_json_label, _score);
    }
    ImGui::SetCursorPos(ImVec2(_x, _y + 25));
    if (ImGui::ArrowButton(("##" + _label + "downButton").c_str(), ImGuiDir_Down)) 
    { 
        if(_score > 0)
        {
            _score--;
            Update::get()->set(_json_label, _score);
        }
    }
}

unsigned int ScoreInput::getScore()
{
    return _score;
}

std::string ScoreInput::getLabel()
{
    return _label;
}