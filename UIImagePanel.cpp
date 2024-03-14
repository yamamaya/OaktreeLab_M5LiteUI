#include "UIImagePanel.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIImagePanel::UIImagePanel( UIElement *parent, const Rectangle &rect, M5Canvas *image ) : UIElement( parent, rect, false ) {
  this->image = image;
  this->alignment = ImageAlignment::TopLeft;
}

void OaktreeLab::M5LiteUI::UIImagePanel::setImage( M5Canvas *image ) {
  this->image = image;
  setUpdate( true );
}

M5Canvas *OaktreeLab::M5LiteUI::UIImagePanel::getImage() {
  return this->image;
}

void OaktreeLab::M5LiteUI::UIImagePanel::setImageAlignment( ImageAlignment alignment ) {
  this->alignment = alignment;
  setUpdate( true );
}

void OaktreeLab::M5LiteUI::UIImagePanel::draw( DrawingMode dmode ) {
  DrawingContext dc = beginDraw();
  Rectangle rect = getClientRectangle();
  if ( dmode == DrawingMode::TotalRedraw ) {
    dc.canvas->fillRect( rect.left, rect.top, rect.width, rect.height, bgColor );
  }
  if ( image != NULL ) {
    int x, y;
    int imgw = image->width();
    int imgh = image->height();
    if ( alignment == ImageAlignment::Center ) {
      x = rect.left + rect.width / 2 - imgw / 2;
      y = rect.top + rect.height / 2 - imgh / 2;
    } else {
      x = rect.left;
      y = rect.top;
    }
    if ( alignment == ImageAlignment::Stretch ) {
      float xs = (float)rect.width / imgw;
      float ys = (float)rect.height / imgh;
      image->setPivot( -0.5f, -0.5f );
      image->pushRotateZoom( x-0.5f, y-0.5f, 0, xs, ys );
    } else {
      image->pushSprite( x, y );
    }
  }
  endDraw();
}