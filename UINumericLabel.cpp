#include "UINumericLabel.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UINumericLabel::UINumericLabel( UIElement *parent, const Rectangle &rect, bool useBackBuffer ) : UILabel( parent, rect, useBackBuffer ) {
  this->value = 0;
  this->format = "%d";
  updateText();
}

void OaktreeLab::M5LiteUI::UINumericLabel::setValue( int32_t value ) {
  this->value = value;
  updateText();
}

int32_t OaktreeLab::M5LiteUI::UINumericLabel::getValue() {
  return this->value;
}

void OaktreeLab::M5LiteUI::UINumericLabel::setFormat( const char *format ) {
  this->format = format;
  updateText();
}

const char *OaktreeLab::M5LiteUI::UINumericLabel::getFormat() {
  return this->format.c_str();
}

void OaktreeLab::M5LiteUI::UINumericLabel::updateText() {
  char buff[20];
  snprintf( buff, sizeof( buff ), this->format.c_str(), this->value );
  UILabel::setText( buff );
}