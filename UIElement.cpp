#include <vector>
#include "UIElement.h"
#include "UIBase.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIElement::UIElement() {
  this->display = base->display;
  this->backBuffer = NULL;
  this->parent = NULL;
  this->updated = false;
  this->fgColorOrg = TFT_WHITE;
  this->bgColorOrg = TFT_BLACK;
  this->fgColor = TFT_WHITE;
  this->bgColor = TFT_BLACK;
  this->border = false;
  this->font = &Font0;
  this->canFocus = false;
  this->hasFocus = false;
  this->enabled = true;
  this->isSetupDone = false;
  this->needsTotalRedraw = true;
  this->eventCallback = NULL;
}

OaktreeLab::M5LiteUI::UIElement::UIElement( UIElement *parent ) : UIElement() {
  display = parent->display;
  this->parent = parent;
  this->fgColor = parent->fgColor;
  this->bgColor = parent->bgColor;
  this->font = parent->font;
}

OaktreeLab::M5LiteUI::UIElement::UIElement( UIElement *parent, const Rectangle &rect, bool useBackBuffer ) : UIElement( parent ) {
  this->rectElement = rect;
  if ( useBackBuffer ) {
    int depth = getRequiredBackBufferColorDepth();
    backBuffer = createBackBuffer( rect.width, rect.height, depth );
    if ( depth == 1 ) {
      this->bgColor = 0;
      this->fgColor = 1;
    } else if ( depth == 2 ) {
      this->bgColor = 0;
      this->fgColor = 3;
    }
  } else {
    backBuffer = NULL;
  }
}

OaktreeLab::M5LiteUI::UIElement::~UIElement() {
  for ( int i = 0 ; i < children.size() ; i ++ ) {
    delete children[ i ];
  }
  if ( backBuffer != NULL ) {
    delete backBuffer;
  }
}

int OaktreeLab::M5LiteUI::UIElement::getRequiredBackBufferColorDepth() {
  return 1;  
}

int OaktreeLab::M5LiteUI::UIElement::getBackBufferColorDepth() {
  if ( backBuffer == NULL ) {
    return 16;
  } else {
    return backBuffer->getColorDepth() & lgfx::v1::color_depth_t::bit_mask;
  }
}

void OaktreeLab::M5LiteUI::UIElement::setFont( const lgfx::IFont &font ) {
  this->font = &font;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIElement::setFont( const lgfx::IFont *font ) {
  this->font = font;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIElement::setForegroundColor( int color ) {
  this->fgColorOrg = color;
  updateForegroundColor( color );
}

void OaktreeLab::M5LiteUI::UIElement::setBackgroundColor( int color ) {
  this->bgColorOrg = color;
  updateBackgroundColor( color );
}

void OaktreeLab::M5LiteUI::UIElement::updateForegroundColor( int color ) {
  int depth = getBackBufferColorDepth();
  if ( backBuffer != NULL && depth == 1 ) {
    backBuffer->setPaletteColor( 1, color );
  } else if ( backBuffer != NULL && depth == 2 ) {
    backBuffer->setPaletteColor( 3, color );
  } else {
    this->fgColor = color;
  }
  setUpdate( true );
}

void OaktreeLab::M5LiteUI::UIElement::updateBackgroundColor( int color ) {
  int depth = getBackBufferColorDepth();
  if ( backBuffer != NULL && ( depth == 1 || depth == 2 ) ) {
    backBuffer->setPaletteColor( 0, color );
  } else {
    this->bgColor = color;
  }
  setUpdate( true );
}

int OaktreeLab::M5LiteUI::UIElement::getParentBackgroundColor() {
  int color = 0;
  if ( this->parent != NULL ) {
    color = this->parent->bgColorOrg;
  }
  return color;
}

Rectangle OaktreeLab::M5LiteUI::UIElement::getClientRectangle() {
  Rectangle rect = rectElement;
  if ( border ) {
    rect.left += 1;
    rect.top += 1;
    rect.width -= 2;
    rect.height -= 2;
  }
  return rect;
}

void OaktreeLab::M5LiteUI::UIElement::showBorder( bool show ) {
  this->border = show;
  this->needsTotalRedraw = true;
  setUpdate( true );
}

void OaktreeLab::M5LiteUI::UIElement::setEnable( bool enable ) {
  if ( enable && !this->enabled ) {
    updateForegroundColor( this->fgColorOrg );
    updateBackgroundColor( this->bgColorOrg );
  } else if ( !enable && this->enabled ) {
    int parentbg = getParentBackgroundColor();
    updateForegroundColor( Utils::blendColor( this->fgColorOrg, parentbg ) );
    updateBackgroundColor( Utils::blendColor( this->bgColorOrg, parentbg ) );
    this->hasFocus = false;
  }
  this->enabled = enable;
}

void OaktreeLab::M5LiteUI::UIElement::enable() {
  setEnable( true );
}

void OaktreeLab::M5LiteUI::UIElement::disable() {
  setEnable( false );
}

bool OaktreeLab::M5LiteUI::UIElement::isEnabled() {
  return enabled;
}

void OaktreeLab::M5LiteUI::UIElement::addChild( UIElement *child ) {
  children.push_back( child );
  if ( base->getUIBaseStatus() == UIBaseStatus::Loop ) {
    child->dispatchSetup();
    child->dispatchDraw( DrawingMode::TotalRedraw );
  }
}

const char* const *OaktreeLab::M5LiteUI::UIElement::getButtonGuide() {
  return NULL;
}

UIElement *OaktreeLab::M5LiteUI::UIElement::getNextElement( UIElement *target, bool focusableOnly ) {
  bool found = false;
  int count = 1;
  UIElement *element = getNextElement_inner( target, focusableOnly, &count, &found );
  if ( element == NULL ) {
    element = getNextElement_inner( target, focusableOnly, &count, &found );
  }
  return element;
}

UIElement *OaktreeLab::M5LiteUI::UIElement::getNextElement_inner( UIElement *target, bool focusableOnly, int *count, bool *found ) {
  if ( !*found ) {
    if ( this == target || target == NULL ) {
      *found = true;
      if ( target == NULL ) {
        *count = 0;
      }
    }
  }
  if ( *found ) {
    if ( !focusableOnly || ( this->canFocus && this->enabled ) ) {
      if ( *count == 0 ) {
        return this;
      }
      (*count) --;
    }
  }
  for ( int i = 0 ; i < this->children.size() ; i ++ ) {
    UIElement *res = this->children[i]->getNextElement_inner( target, focusableOnly, count, found );
    if ( res != NULL ) {
      return res;
    }
  }
  return NULL;
}

void OaktreeLab::M5LiteUI::UIElement::giveFocus() {
  if ( canFocus && !hasFocus ) {
    hasFocus = true;
    setUpdate();
  }
}

void OaktreeLab::M5LiteUI::UIElement::takeFocus() {
  if ( hasFocus ) {
    hasFocus = false;
    setUpdate();
  }
}

void OaktreeLab::M5LiteUI::UIElement::setUpdate( bool total_redraw ) {
  updated = true;
  needsTotalRedraw |= total_redraw;
  for ( int i = 0 ; i < children.size() ; i ++ ) {
    UIElement *child = children[i];
    child->setUpdate( total_redraw );
  }
}

void OaktreeLab::M5LiteUI::UIElement::setEventCallback( std::function<void(UIElement*,ElementEvent,uint32_t)> cb ) {
  eventCallback = cb;
}

void OaktreeLab::M5LiteUI::UIElement::invokeEventCallback( ElementEvent event, uint32_t arg ) {
  if ( eventCallback != NULL ) {
    eventCallback( this, event, arg );
  }
}

void OaktreeLab::M5LiteUI::UIElement::dispatchDraw( DrawingMode dmode ) {
  if ( needsTotalRedraw ) {
    dmode = DrawingMode::TotalRedraw;
    needsTotalRedraw = false;
  }
  bool needsRedrawForCursor = ( this->hasFocus && base->CursorStateUpdated );
  if ( dmode == DrawingMode::TotalRedraw || updated || needsRedrawForCursor ) {
    if ( border && dmode == DrawingMode::TotalRedraw ) {
      display->drawRect( rectElement.left, rectElement.top, rectElement.width, rectElement.height, fgColorOrg );
    }
    Rectangle rectClient = getClientRectangle();
    display->setClipRect( rectClient.left, rectClient.top, rectClient.width, rectClient.height );
    if ( dmode == DrawingMode::TotalRedraw || updated ) {
      draw( dmode );
    }
    drawOverlay();
    render();
    display->clearClipRect();
    updated = false;
    if ( needsRedrawForCursor ) {
      base->CursorStateUpdated = false;
    } 
  }
  for ( int i = 0 ; i < children.size() ; i ++ ) {
    UIElement *child = children[i];
    child->dispatchDraw( dmode );
  }
}

DrawingContext OaktreeLab::M5LiteUI::UIElement::beginDraw() {
  DrawingContext dc;
  dc.rect = this->rectElement;
  if ( backBuffer != NULL ) {
    dc.canvas = backBuffer;
    dc.rect.left = 0;
    dc.rect.top = 0;
    if ( border ) {
      dc.rect.width -= 2;
      dc.rect.height -= 2;
    }
  } else {
    dc.canvas = display;
    if ( border ) {
      dc.rect.left += 1;
      dc.rect.top += 1;
      dc.rect.width -= 2;
      dc.rect.height -= 2;
    }
  }
  return dc;
}

void OaktreeLab::M5LiteUI::UIElement::endDraw() {
}

M5Canvas *OaktreeLab::M5LiteUI::UIElement::createBackBuffer( int width, int height, int colorDepth ) {
  M5Canvas *canvas = new M5Canvas( display );
  canvas->setColorDepth( colorDepth );
  canvas->createSprite( width, height );
  if ( colorDepth == 1 ) {
    canvas->setPaletteColor( 0, bgColor );
    canvas->setPaletteColor( 1, fgColor );
    canvas->setTextColor( 1 );
  } else if ( colorDepth == 2 ) {
    canvas->setPaletteColor( 0, bgColor );
    canvas->setPaletteColor( 1, 0  , 0  , 255 );
    canvas->setPaletteColor( 2, 0  , 255, 0   );
    canvas->setPaletteColor( 3, fgColor );
    canvas->setTextColor( 3 );
  } else if ( colorDepth == 4 ) {
    canvas->setPaletteColor( 0 , 0  , 0  , 0   );
    canvas->setPaletteColor( 1 , 0  , 0  , 128 );
    canvas->setPaletteColor( 2 , 0  , 128, 0   );
    canvas->setPaletteColor( 3 , 0  , 128, 128 );
    canvas->setPaletteColor( 4 , 128, 0  , 0   );
    canvas->setPaletteColor( 5 , 128, 0  , 128 );
    canvas->setPaletteColor( 6 , 128, 128, 0   );
    canvas->setPaletteColor( 7 , 128, 128, 128 );
    canvas->setPaletteColor( 8 , 192, 192, 192 );
    canvas->setPaletteColor( 9 , 0  , 0  , 255 );
    canvas->setPaletteColor( 10, 0  , 255, 0   );
    canvas->setPaletteColor( 11, 0  , 255, 255 );
    canvas->setPaletteColor( 12, 255, 0  , 0   );
    canvas->setPaletteColor( 13, 255, 0  , 255 );
    canvas->setPaletteColor( 14, 255, 255, 0   );
    canvas->setPaletteColor( 15, 255, 255, 255 );
    canvas->setTextColor( 15 );
  }
  return canvas;
}

void OaktreeLab::M5LiteUI::UIElement::dispatchSetup() {
  if ( !isSetupDone ) {
    setup();
    isSetupDone = true;
  }
  for ( int i = 0 ; i < children.size() ; i ++ ) {
    UIElement *child = children[i];
    child->dispatchSetup();
  }
}

void OaktreeLab::M5LiteUI::UIElement::setup() {
}

void OaktreeLab::M5LiteUI::UIElement::dispatchLoop() {
  loop();
  for ( int i = 0 ; i < children.size() ; i ++ ) {
    UIElement *child = children[i];
    child->dispatchLoop();
  }
}

void OaktreeLab::M5LiteUI::UIElement::loop() {
}

void OaktreeLab::M5LiteUI::UIElement::onUIEvent( const UIEventArg &arg ) {
}

void OaktreeLab::M5LiteUI::UIElement::draw( DrawingMode dmode ) {
  DrawingContext dc = beginDraw();
  dc.canvas->fillRect( dc.rect.left, dc.rect.top, dc.rect.width, dc.rect.height, bgColor );
  endDraw();
}

void OaktreeLab::M5LiteUI::UIElement::drawOverlay() {
  if ( hasFocus && canFocus ) {
    DrawingContext dc = beginDraw();
    int c = base->getCursorBlinkState() ? fgColor : bgColor;
    Rectangle rectClient = getClientRectangle();
    Rectangle rect = Rectangle( rectClient.left, rectClient.top, 4, rectClient.height );
    dc.canvas->fillRect( rect.left, rect.top, rect.width, rect.height, c );
    endDraw();
  }
}

void OaktreeLab::M5LiteUI::UIElement::render() {
  if ( backBuffer != NULL ) {
    Rectangle rectClient = getClientRectangle();
    backBuffer->pushSprite( rectClient.left, rectClient.top );
  }
}
