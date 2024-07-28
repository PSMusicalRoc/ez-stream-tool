#include "PlayerCharacterSelect.h"

#include "imgui.h"
#include <iostream>
#include "misc/cpp/imgui_stdlib.h"
#include <SDL.h>

#include "Update.h"
#include "MainWindow.h"

#include "WindowState.h"


PlayerCharacterSelect::PlayerCharacterSelect(int x, int y, int width, const std::string& label, const std::string& jsonLabel)
    :Widget(x, y, width, 0)
{
    this->label = label;
    this->jsonLabel = jsonLabel;
    this->name = "default";

    //SDL_Window* selectWindow = SDL_CreateWindow( "Player Select Screen",
      //  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        //1000, 500, SDL_WINDOW_SHOWN
    //);
     bool r = false;

    Update::get()->set(jsonLabel, "default");
}

void PlayerCharacterSelect::render()
{
    
    ImGui::SetCursorPos(ImVec2(_x, _y));
    ImGui::SetNextItemWidth(_width);
    
   
    

    if (ImGui::Button("Change!", ImVec2(_width, _height)))
    {
        //Update::get()->set("SelectScreenOpen", "true");
        WindowState::get() -> WindowState::set(1);

        
    }

    
}

std::string PlayerCharacterSelect::getLabel()
{
    return label;
}
std::string PlayerCharacterSelect::getName()
{
    return name;
}