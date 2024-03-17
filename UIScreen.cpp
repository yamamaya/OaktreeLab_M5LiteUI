#include "UIScreen.h"
#include "UIBase.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIScreen::UIScreen() : UIWindow( base->getScreenRectangle() ) {
}
