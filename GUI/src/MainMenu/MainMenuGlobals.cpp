#include "MainMenuGlobals.h"
#include <algorithm>

namespace o2 {

gui::Font* minecraftFont = nullptr;
std::vector<gui::Div*> globalDivs;

void removeGlobalDiv(gui::Div* div) {
	auto it = std::find(globalDivs.begin(), globalDivs.end(), div);
	if (it != globalDivs.end()) {
		globalDivs.erase(it);
	}
}

}