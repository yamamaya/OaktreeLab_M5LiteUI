#include "UILabel.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UILabel::UILabel( UIElement *parent, const Rectangle &rect, bool useBackBuffer ) : UIElement( parent, rect, useBackBuffer ) {
  this->border = false;
  this->text = "";
  this->textAlignment = TextAlignment::MiddleCenter;
}

OaktreeLab::M5LiteUI::UILabel::UILabel( UIElement *parent, const Rectangle &rect, const char *text, bool useBackBuffer ) : UILabel( parent, rect, useBackBuffer ) {
  this->text = text;
}

void OaktreeLab::M5LiteUI::UILabel::setText( const char *text ) {
  if ( this->text != text ) {
    this->text = text;
    setUpdate();
  }
}

const char *OaktreeLab::M5LiteUI::UILabel::getText() {
  return this->text.c_str();
}

void OaktreeLab::M5LiteUI::UILabel::setTextAlignment( TextAlignment align ) {
  this->textAlignment = align;
  setUpdate();
}

#define BORDER_MARGIN  4

void OaktreeLab::M5LiteUI::UILabel::draw( DrawingMode dmode ) {
  DrawingContext dc = beginDraw();
  Rectangle rectText = dc.rect;
  if ( this->border ) {
    rectText.left += BORDER_MARGIN;
    rectText.top += BORDER_MARGIN;
    rectText.width -= BORDER_MARGIN*2;
    rectText.height -= BORDER_MARGIN*2;
  }
  int x;
  if ( this->textAlignment == TextAlignment::TopLeft || this->textAlignment == TextAlignment::MiddleLeft || this->textAlignment == TextAlignment::BottomLeft ) {
    x = rectText.left;
  } else if ( this->textAlignment == TextAlignment::TopCenter || this->textAlignment == TextAlignment::MiddleCenter || this->textAlignment == TextAlignment::BottomCenter ) {
    x = rectText.left + rectText.width / 2;
  } else {
    x = rectText.left + rectText.width;
  }
  int y;
  if ( this->textAlignment == TextAlignment::TopLeft || this->textAlignment == TextAlignment::TopCenter || this->textAlignment == TextAlignment::TopRight ) {
    y = rectText.top;
  } else if ( this->textAlignment == TextAlignment::MiddleLeft || this->textAlignment == TextAlignment::MiddleCenter || this->textAlignment == TextAlignment::MiddleRight ) {
    y = rectText.top + rectText.height / 2;
  } else {
    y = rectText.top + rectText.height;
  }
  dc.canvas->fillRect( dc.rect.left, dc.rect.top, dc.rect.width, dc.rect.height, bgColor );
  dc.canvas->setTextDatum( (textdatum_t)(int)this->textAlignment );
  dc.canvas->setFont( font );
  dc.canvas->setTextColor( fgColor );
  dc.canvas->drawString( text.c_str(), x, y );
  endDraw();
}