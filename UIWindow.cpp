#include "UIWindow.h"
#include "UIBase.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIWindow::UIWindow( const Rectangle &rect ) : UIElement() {
  this->focusedElement = NULL;
  this->rectElement.top = rect.top;
  this->rectElement.left = rect.left;
  this->rectElement.width = rect.width;
  this->rectElement.height = rect.height;
}

OaktreeLab::M5LiteUI::UIWindow::~UIWindow() {
}

void OaktreeLab::M5LiteUI::UIWindow::focusNextElement() {
  UIElement *element = getNextElement( getFocusedElement(), true );
  this->focusedElement = element;
  setFocus( this->focusedElement );
}

void OaktreeLab::M5LiteUI::UIWindow::clearFocus() {
  setFocus( NULL );
}

void OaktreeLab::M5LiteUI::UIWindow::setFocus( UIElement *element ) {
  this->focusedElement = element;
  setFocus_inner( this, element );
  base->handleFocusChange();
}

void OaktreeLab::M5LiteUI::UIWindow::setFocus_inner( UIElement *element, UIElement *target ) {
  if ( element == target && element->canFocus && element->enabled ) {
    element->giveFocus();
  } else {
    if ( element->hasFocus ) {
      element->takeFocus();
    }
  }
  for ( int i = 0 ; i < element->children.size() ; i ++ ) {
    UIElement *e = element->children[i];
    setFocus_inner( e, target );
  }
}

UIElement *OaktreeLab::M5LiteUI::UIWindow::getFocusedElement() {
  if ( focusedElement != NULL && focusedElement->hasFocus ) {
    return focusedElement;
  }
  return NULL;
}

void OaktreeLab::M5LiteUI::UIWindow::draw( DrawingMode dmode ) {
  DrawingContext dc = beginDraw();
  if ( dmode == DrawingMode::TotalRedraw ) {
    dc.canvas->fillScreen( bgColor );
  }
  endDraw();
}
