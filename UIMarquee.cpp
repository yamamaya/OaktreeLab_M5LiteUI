#include "UIMarquee.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIMarquee::UIMarquee( UIElement *parent, const Rectangle &rect, MarqueeType type, bool useBackBuffer ) : UIMarquee( parent, rect, "", type, useBackBuffer ) {
}

OaktreeLab::M5LiteUI::UIMarquee::UIMarquee( UIElement *parent, const Rectangle &rect, const char *text, MarqueeType type, bool useBackBuffer ) : UILabel( parent, rect, text, useBackBuffer ) {
  this->type = type;
  this->speed = 3;
  resetState();
}

void OaktreeLab::M5LiteUI::UIMarquee::setType( MarqueeType type ) {
  if ( this->type != type ) {
    this->type = type;
    resetState();
    setUpdate( true );
  }
}

void OaktreeLab::M5LiteUI::UIMarquee::resetState() {
  start_time = millis();
  state = 0;
  first = true;
}

void OaktreeLab::M5LiteUI::UIMarquee::setSpeed( uint32_t speed ) {
  this->speed = speed;
}

void OaktreeLab::M5LiteUI::UIMarquee::loop() {
  uint32_t newState = state;
  uint32_t t = (uint32_t)millis() - start_time;
  if ( type == MarqueeType::Static ) {
  } else if ( type == MarqueeType::Blink ) {
    newState = ~( t >> ( speed + 5 ) ) & 1;
  } else if ( type == MarqueeType::Scroll ) {
    newState = ( t >> ( speed + 1 ) );
  }
  if ( newState != state || first ) {
    state = newState;
    first = false;
    setUpdate();
  }
}

#define BORDER_MARGIN  4

void OaktreeLab::M5LiteUI::UIMarquee::draw( DrawingMode dmode ) {
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
  const char *str = text.c_str();
  if ( type == MarqueeType::Static ) {
    dc.canvas->drawString( str, x, y );
  } else if ( type == MarqueeType::Blink ) {
    if ( state != 0 ) {
      dc.canvas->drawString( str, x, y );
    }
  } else if ( type == MarqueeType::Scroll ) {
    int wt = dc.canvas->textWidth( str );
    int wc = getClientRectangle().width;
    int offset = -(int)state % ( wt + wc );
    if ( offset < -wt ) {
      offset = offset + wt + wc;
    }
    dc.canvas->drawString( str, x + offset, y );
  }
  endDraw();
}
