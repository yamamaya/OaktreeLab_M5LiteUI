#include "UIButtonGuide.h"
#include "UIBase.h"

using namespace OaktreeLab::M5LiteUI;

constexpr const char* const OaktreeLab::M5LiteUI::UIButtonGuide::default_guides[];
constexpr const char* const OaktreeLab::M5LiteUI::UIButtonGuide::guides_without_focus[];

OaktreeLab::M5LiteUI::UIButtonGuide::UIButtonGuide() {
  guides = default_guides;
  setForegroundColor( TFT_WHITE );
  setBackgroundColor( TFT_BLACK );
  updated = true;
}

int OaktreeLab::M5LiteUI::UIButtonGuide::getHeight() {
  return 22;
}

void OaktreeLab::M5LiteUI::UIButtonGuide::setForegroundColor( int color ) {
  fgColor = color;
  updated = true;
}

void OaktreeLab::M5LiteUI::UIButtonGuide::setBackgroundColor( int color ) {
  bgColor = color;
  updated = true;
}


void OaktreeLab::M5LiteUI::UIButtonGuide::setButtonGuide( const char* const *guides ) {
  if ( guides == NULL ) {
    guides = default_guides;
  }
  for ( int i = 0 ; i < 3 ; i ++ ) {
    if ( strcmp( this->guides[i], guides[i] ) != 0 ) {
      updated = true;
      break;
    }
  }
  if ( updated ) {
    this->guides = guides;
  }
}

void OaktreeLab::M5LiteUI::UIButtonGuide::draw( DrawingMode dmode ) {
  M5GFX *display = base->getDisplay();
  if ( dmode == DrawingMode::TotalRedraw ) {
    display->fillRect( 0, display->height()-getHeight(), display->height(), getHeight(), bgColor );
  }
  int y = display->height() - 16;
  display->setFont( &fonts::Font2 );
  display->setTextColor( bgColor );
  display->setTextDatum( textdatum_t::top_center );
  int screen_width = display->width();
  int item_dist = screen_width * 7 / 25;
  int item_width = item_dist - 15;
  for ( int i = 0 ; i < 3 ; i ++ ) {
    int x = screen_width / 2 + item_dist * ( i - 1 );
    display->fillRect( x - item_width / 2, y, item_width, 18, fgColor );
    if ( strcmp( guides[i], buttonCommonUp ) == 0 ) { 
      display->fillTriangle( x, y + 2, x - 7, y + 13, x + 7, y + 13, bgColor );
    } else if ( strcmp( guides[i], buttonCommonDown ) == 0 ) { 
      display->fillTriangle( x, y + 13, x - 7, y + 2, x + 7, y + 2, bgColor );
    } else if ( strcmp( guides[i], buttonCommonPush ) == 0 ) { 
      display->fillTriangle( x, y + 10, x - 7, y + 2, x + 7, y + 2, bgColor );
      display->fillRect( x - 7, y + 12, 15, 2, bgColor );
    } else {
      display->drawString( guides[i], x, y );
    }
  }
}