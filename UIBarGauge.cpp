#include "UIBarGauge.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIBarGauge::UIBarGauge( UIElement *parent, const Rectangle &rect, BarGaugeType type ) : UIElement( parent, rect, false ) {
  this->type = type;
  this->barColor = TFT_NAVY;
  this->scale = false;
  this->scaleCount = 10;
  this->scaleSize = 4;
}

void OaktreeLab::M5LiteUI::UIBarGauge::setBarColor( int color ) {
  barColor = color;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIBarGauge::showScale( bool scale ) {
  this->scale = scale;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIBarGauge::setScaleCount( int count ) {
  scaleCount = count;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIBarGauge::setScaleSize( int size ) {
  scaleSize = size;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIBarGauge::setValueRange( int min, int max ) {
  minValue = min;
  maxValue = max;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIBarGauge::setValue( int value ) {
  this->value = value;
  setUpdate();
}

void OaktreeLab::M5LiteUI::UIBarGauge::draw( DrawingMode dmode ) {
  DrawingContext dc = beginDraw();
  Rectangle rect = getClientRectangle();
  int size;
  if ( type == BarGaugeType::Horizontal ) {
    size = rect.width;
  } else {
    size = rect.height;
  }
  int t = (int)round( (float)( value - minValue ) / ( maxValue - minValue ) * size );
  if ( t < 0 ) {
    t = 0;
  }
  if ( t > size ) {
    t = size;
  }
  if ( type == BarGaugeType::Horizontal ) {
    if ( !scale ) {
      dc.canvas->fillRect( dc.rect.left, dc.rect.top, t, dc.rect.height, barColor );
      dc.canvas->fillRect( dc.rect.left + t, dc.rect.top, dc.rect.width - t, dc.rect.height, bgColor );
    } else {
      int x = rect.left + t - 1;
      for ( int i = 0 ; i < scaleCount ; i ++ ) {
        int sx1 = rect.left + rect.width * i / scaleCount;
        int sx2 = rect.left + rect.width * ( i + 1 ) / scaleCount;
        int scale_bar_color;
        if ( x < sx1 ) {
          dc.canvas->fillRect( sx1, dc.rect.top, sx2 - sx1 - 1, dc.rect.height, bgColor );
          scale_bar_color = bgColor;
        } else if ( x < sx2 - 1 ) {
          dc.canvas->fillRect( sx1, dc.rect.top, x - sx1 + 1, dc.rect.height, barColor );
          dc.canvas->fillRect( x + 1, dc.rect.top, sx2 - 1 - x - 1, dc.rect.height, bgColor );
          scale_bar_color = bgColor;
        } else {
          dc.canvas->fillRect( sx1, dc.rect.top, sx2 - sx1 - 1, dc.rect.height, barColor );
          scale_bar_color = barColor;
        }
        if ( i < scaleCount - 1 ) {
          int sy = dc.rect.top + dc.rect.height - scaleSize;
          dc.canvas->drawLine( sx2 - 1, dc.rect.top, sx2 - 1, sy - 1, scale_bar_color );
          dc.canvas->drawLine( sx2 - 1, sy, sx2 - 1, dc.rect.top + dc.rect.height, fgColor );
        } else {
          dc.canvas->drawLine( sx2 - 1, dc.rect.top, sx2 - 1, dc.rect.top + dc.rect.height, scale_bar_color );
        }
      }
    }
  } else if ( type == BarGaugeType::Vertical ) {
    if ( !scale ) {
      dc.canvas->fillRect( dc.rect.left, dc.rect.top + dc.rect.height - t, dc.rect.width, t, barColor );
      dc.canvas->fillRect( dc.rect.left, dc.rect.top, dc.rect.width, dc.rect.height - t, bgColor );
    } else {
      int y = rect.top + rect.height - t;
      for ( int i = 0 ; i < scaleCount ; i ++ ) {
        int sy1 = rect.top + rect.height - rect.height * i / scaleCount - 1;
        int sy2 = rect.top + rect.height - rect.height * ( i + 1 ) / scaleCount - 1;
        int scale_bar_color;
        if ( y > sy1 ) {
          dc.canvas->fillRect( dc.rect.left, sy2 + 2, dc.rect.width, sy1 - sy2 - 1, bgColor );
          scale_bar_color = bgColor;
        } else if ( y > sy2 + 1 ) {
          dc.canvas->fillRect( dc.rect.left, y, dc.rect.width, sy1 - y + 1, barColor );
          dc.canvas->fillRect( dc.rect.left, sy2 + 2, dc.rect.width, y - sy2 - 2, bgColor );
          scale_bar_color = bgColor;
        } else {
          dc.canvas->fillRect( dc.rect.left, sy2 + 2, dc.rect.width, sy1 - sy2 - 1, barColor );
          scale_bar_color = barColor;
        }
        if ( i < scaleCount - 1 ) {
          int sx = dc.rect.left + scaleSize;
          dc.canvas->drawLine( sx + 1, sy2 + 1, dc.rect.left + dc.rect.width, sy2 + 1, scale_bar_color );
          dc.canvas->drawLine( dc.rect.left, sy2 + 1, sx, sy2 + 1, fgColor );
        } else {
          dc.canvas->drawLine( dc.rect.left, sy2 + 1, dc.rect.left + dc.rect.width, sy2 + 1, scale_bar_color );
        }
      }
    }
  }
  endDraw();
}