#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../GUI/Div.h"
#include "../GUI/Font.h"

namespace o2 {

extern gui::Font* minecraftFont;
extern std::vector<gui::Div*> globalDivs;

void removeGlobalDiv(gui::Div* div);

}