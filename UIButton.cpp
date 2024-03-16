#include "UIButton.h"
#include "UIBase.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIButton::UIButton( UIElement *parent, const Rectangle &rect, const char *text ) : UILabel( parent, rect, text, false ) {
  this->border = false;
  this->canFocus = true;
  this->ButtonCount = 0;
  this->ButtonState = false;
  this->IsFirstTotalRedraw = true;
}

const char* const *OaktreeLab::M5LiteUI::UIButton::getButtonGuide() {
  static const char* const button_guides[3] = { UIButtonGuide::buttonCommonSelect, UIButtonGuide::buttonCommonPush, UIButtonGuide::buttonCommonPush };
  return button_guides;
}

#define BORDER_MARGIN  5
#define CORNER_RADIUS  8

void OaktreeLab::M5LiteUI::UIButton::draw( DrawingMode dmode ) {
  DrawingContext dc = beginDraw();
  Rectangle rectClient = dc.rect;
  rectClient.left += BORDER_MARGIN;
  rectClient.top += BORDER_MARGIN;
  rectClient.width -= BORDER_MARGIN*2;
  rectClient.height -= BORDER_MARGIN*2;
  int x;
  if ( this->textAlignment == TextAlignment::TopLeft || this->textAlignment == TextAlignment::MiddleLeft || this->textAlignment == TextAlignment::BottomLeft ) {
    x = rectClient.left;
  } else if ( this->textAlignment == TextAlignment::TopCenter || this->textAlignment == TextAlignment::MiddleCenter || this->textAlignment == TextAlignment::BottomCenter ) {
    x = rectClient.left + rectClient.width / 2;
  } else {
    x = rectClient.left + rectClient.width;
  }
  int y;
  if ( this->textAlignment == TextAlignment::TopLeft || this->textAlignment == TextAlignment::TopCenter || this->textAlignment == TextAlignment::TopRight ) {
    y = rectClient.top;
  } else if ( this->textAlignment == TextAlignment::MiddleLeft || this->textAlignment == TextAlignment::MiddleCenter || this->textAlignment == TextAlignment::MiddleRight ) {
    y = rectClient.top + rectClient.height / 2;
  } else {
    y = rectClient.top + rectClient.height;
  }
  if ( dmode == DrawingMode::TotalRedraw && IsFirstTotalRedraw ) {
    // Suppresses total redraw to prevent unsightly flickering. As a side effect of it, this button will have problems redrawing when changing the color and so on.
    dc.canvas->fillRoundRect( dc.rect.left, dc.rect.top, dc.rect.width, dc.rect.height, CORNER_RADIUS, borderColor );
    IsFirstTotalRedraw = false;
  }
  dc.canvas->fillRoundRect( dc.rect.left+1, dc.rect.top+1, dc.rect.width-2, dc.rect.height-2, CORNER_RADIUS, bgColor );
  dc.canvas->setTextDatum( (textdatum_t)(int)this->textAlignment );
  dc.canvas->setFont( font );
  dc.canvas->setTextColor( fgColor );
  dc.canvas->drawString( text.c_str(), x, y );
  endDraw();
}

void OaktreeLab::M5LiteUI::UIButton::drawOverlay() {
  if ( hasFocus && canFocus ) {
    DrawingContext dc = beginDraw();
    int c = ( base->getCursorBlinkState() || ButtonState ) ? fgColor : bgColor;
    dc.canvas->drawRoundRect( dc.rect.left+1, dc.rect.top+1, dc.rect.width-2, dc.rect.height-2, CORNER_RADIUS, c );
    dc.canvas->drawRoundRect( dc.rect.left+2, dc.rect.top+2, dc.rect.width-4, dc.rect.height-4, CORNER_RADIUS-1, c );
    endDraw();
  }
}

void OaktreeLab::M5LiteUI::UIButton::onUIEvent( const UIEventArg &arg ) {
  if ( arg.event == UIEvent::ButtonPress ) {
    ButtonCount++;
    if ( ButtonCount == 1 ) {
      ButtonState = true;
      updateButtonStatus();
      invokeEventCallback( ElementEvent::Clicked, 0 );
    }
  } else if ( arg.event == UIEvent::ButtonRelease ) {
    ButtonCount--;
    if ( ButtonCount == 0 ) {
      ButtonState = false;
      updateButtonStatus();
    }
  }
}

void OaktreeLab::M5LiteUI::UIButton::updateButtonStatus() {
  if ( !ButtonState ) {
    updateBackgroundColor( bgColorOrg );
  } else {
    updateBackgroundColor( Utils::blendColor( bgColorOrg, fgColorOrg ) );
  }
}