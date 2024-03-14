#include "M5ButtonHelper.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::M5ButtonHelper::M5ButtonHelper() {
}

OaktreeLab::M5LiteUI::M5ButtonHelper::M5ButtonHelper( m5::Button_Class *button ) {
  this->button = button;
}

ButtonStatus OaktreeLab::M5LiteUI::M5ButtonHelper::getCurrentStatus() {
  ButtonStatus st;
  uint32_t t = millis();
  st.click = button->wasClicked();
  st.longpress = button->wasHold();
  st.press = button->wasPressed();
  st.pressed = button->isPressed();
  bool holding = button->isHolding();
  st.release = button->wasReleased();
  st.repeat = false;
  if ( !prevHolding && holding ) {
    timeHolding = t;
  }
  prevHolding = holding;
  if ( holding ) {
    bool repeat = false;
    if ( t == timeHolding || t >= prevRepeat + 200 ) {
      repeat = true;
    }
    if ( repeat ) {
      st.repeat = true;
      prevRepeat = t;
    }
  }
  return st;
}