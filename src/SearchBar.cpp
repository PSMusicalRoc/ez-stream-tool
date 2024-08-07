#include "SearchBar.h"

#include "imgui.h"
#include <iostream>
#include "misc/cpp/imgui_stdlib.h"

#include "Update.h"
#include <regex>

#include "Search.h"


SearchBar::SearchBar(int x, int y, int width, const std::string& label)
    :Widget(x, y, width, 0)
{
    this->label = label;
    this->text = "";
    //this->jsonLabel = jsonLabel;

    //Update::get()->set(jsonLabel, "");
}


void SearchBar::render()
{
    //static std::string input = "";
    
    ImGui::SetCursorPos(ImVec2(_x, _y));
    ImGui::SetNextItemWidth(_width);
    // const char* l = label.c_str();
    //std::string searchResult = Search::get() -> getSearch();
    if (ImGui::InputTextWithHint(("##" + label).c_str(), label.c_str(),  &(text)))
    {
        Search::get()->set(this->text);
        //text = "";
    }
    text = Search::get() -> getSearch();
}