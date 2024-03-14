#include "UIScreen.h"
#include "UIBase.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIScreen::UIScreen() : UIWindow( base->getScreenRectangle() ) {
  Rectangle rect = getClientRectangle();
  char buff[100];
  sprintf( buff, "UIScreen( %d, %d, %d, %d )", rect.left, rect.top, rect.width, rect.height );
  Serial.println( buff );
}
