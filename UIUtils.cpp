#include "UIUtils.h"
#include "UIBase.h"

using namespace OaktreeLab::M5LiteUI;

int OaktreeLab::M5LiteUI::Utils::blendColor( int color1, int color2 ) {
  uint32_t c1 = lgfx::v1::LGFXBase::color16to24( color1 );
  uint8_t r1 = (uint8_t)( c1 >> 16 );
  uint8_t g1 = (uint8_t)( c1 >> 8 );
  uint8_t b1 = (uint8_t)c1;
  uint32_t c2 = lgfx::v1::LGFXBase::color16to24( color2 );
  uint8_t r2 = (uint8_t)( c2 >> 16 );
  uint8_t g2 = (uint8_t)( c2 >> 8 );
  uint8_t b2 = (uint8_t)c2;
  uint8_t r = (uint8_t)( ( (uint16_t)r1 + (uint16_t)r2 ) / 2 );
  uint8_t g = (uint8_t)( ( (uint16_t)g1 + (uint16_t)g2 ) / 2 );
  uint8_t b = (uint8_t)( ( (uint16_t)b1 + (uint16_t)b2 ) / 2 );
  return lgfx::v1::LGFXBase::color565( r, g, b );
}

M5Canvas *OaktreeLab::M5LiteUI::Utils::createM5Canvas( int width, int height, int color_depth ) {
  M5Canvas *canvas = new M5Canvas( base->display );
  canvas->setColorDepth( color_depth );
  canvas->createSprite( width, height );
  return canvas;
}
