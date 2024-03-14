#include "UIBase.h"
#include "UIWindow.h"
#include "UIScreen.h"

using namespace OaktreeLab::M5LiteUI;

UIBase *OaktreeLab::M5LiteUI::base;

OaktreeLab::M5LiteUI::UIBase::UIBase( M5GFX *display ) : UIBase( display, new UIButtonGuide() ) {
}

OaktreeLab::M5LiteUI::UIBase::UIBase( M5GFX *display, UIButtonGuide *button_guide ) {
  base = this;
  this->display = display;
  this->guide = button_guide;
  this->state = UIBaseStatus::None;
  display->fillScreen( TFT_BLACK );
  buttonA = M5ButtonHelper( &M5.BtnA );
  buttonB = M5ButtonHelper( &M5.BtnB );
  buttonC = M5ButtonHelper( &M5.BtnC );
}

OaktreeLab::M5LiteUI::UIBase::~UIBase() {
  if ( guide != NULL ) {
    delete guide;
  }
}

M5GFX *OaktreeLab::M5LiteUI::UIBase::getDisplay() {
  return display;
}

Rectangle OaktreeLab::M5LiteUI::UIBase::getScreenRectangle() {
  Rectangle rect = Rectangle( 0, 0, display->width(), display->height() );
  if ( guide != NULL ) {
    rect.height -= guide->getHeight();
  }
  return rect;
}

void OaktreeLab::M5LiteUI::UIBase::updateButtonGuide() {
  if ( screen != NULL ) {
    if ( guide != NULL ) {
      UIElement *focus = screen->getFocusedElement();
      if ( focus != NULL ) {
        guide->setButtonGuide( focus->getButtonGuide() );
      } else {
        guide->setButtonGuide( UIButtonGuide::guides_without_focus );
      }
    }
  }
}

void OaktreeLab::M5LiteUI::UIBase::setScreen( UIScreen *screen ) {
  this->screen = screen;
  this->state = UIBaseStatus::Setup;
  screen->dispatchSetup();
  updateButtonGuide();
  this->state = UIBaseStatus::Loop;
  draw( DrawingMode::TotalRedraw );
  if ( guide != NULL ) {
    guide->draw( DrawingMode::TotalRedraw );
  }
}

void OaktreeLab::M5LiteUI::UIBase::handleFocusChange() {
  updateButtonGuide();
}

void OaktreeLab::M5LiteUI::UIBase::loop() {
  ButtonStatus ButtonA = buttonA.getCurrentStatus();
  ButtonStatus ButtonB = buttonB.getCurrentStatus();
  ButtonStatus ButtonC = buttonC.getCurrentStatus();

  if ( screen != NULL ) {
    unsigned long t = millis();
    if ( ButtonA.click && !ButtonB.isButtonInteracted() && !ButtonC.isButtonInteracted() ) {
      CursorBlinkTimer = t;
      CurrentCursorState = true;
      CursorStateUpdated = true;
      screen->focusNextElement();
      updateButtonGuide();
    }
    UIElement *focus = screen->getFocusedElement();
    if ( focus != NULL ) {
      unsigned long dt = t - CursorBlinkTimer;
      bool cursor = ( ( dt >> 8 ) & 1 ) ? false : true;
      if ( cursor != CurrentCursorState ) {
        CurrentCursorState = cursor;
        CursorStateUpdated = true;
      }
      if ( ButtonB.press ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonPress, UIEventSource::ButtonB, 0 ) );
      }
      if ( ButtonB.longpress ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonLongPress, UIEventSource::ButtonB, 0 ) );
      }
      if ( ButtonB.repeat ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonRepeat, UIEventSource::ButtonB, 0 ) );
      }
      if ( ButtonB.release ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonRelease, UIEventSource::ButtonB, 0 ) );
      }
      if ( ButtonC.press ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonPress, UIEventSource::ButtonC, 0 ) );
      }
      if ( ButtonC.longpress ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonLongPress, UIEventSource::ButtonC, 0 ) );
      }
      if ( ButtonC.repeat ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonRepeat, UIEventSource::ButtonC, 0 ) );
      }
      if ( ButtonC.release ) {
        focus->onUIEvent( UIEventArg( UIEvent::ButtonRelease, UIEventSource::ButtonC, 0 ) );
      }
    }
    screen->dispatchLoop();
  }
  draw( DrawingMode::PartialRedraw );
}

void OaktreeLab::M5LiteUI::UIBase::draw( DrawingMode dmode ) {
  if ( screen != NULL ) {
    display->startWrite();
    screen->dispatchDraw( dmode );
    if ( guide != NULL ) {
      if ( guide->updated ) {
        int h = guide->getHeight();
        display->setClipRect( 0, display->height() - h, display->width(), h );
        guide->draw( DrawingMode::PartialRedraw );
        display->clearClipRect();
        guide->updated = false;
      }
    }
    display->endWrite();
  }
}

bool OaktreeLab::M5LiteUI::UIBase::getCursorBlinkState() {
  return CurrentCursorState;
}

UIBaseStatus OaktreeLab::M5LiteUI::UIBase::getUIBaseStatus() {
  return this->state;
}
