#include "UINumericUpDown.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UINumericUpDown::UINumericUpDown( UIElement *parent, const Rectangle &rect, bool useBackBuffer ) : UINumericLabel( parent, rect, useBackBuffer ) {
  this->showBorder( true );  
  this->canFocus = true;
}

void OaktreeLab::M5LiteUI::UINumericUpDown::setValueRange( int min, int max ) {
  this->maxValue = max;
  this->minValue = min;
}

void OaktreeLab::M5LiteUI::UINumericUpDown::setValueStep( int step ) {
  this->step = step;
}

void OaktreeLab::M5LiteUI::UINumericUpDown::onUIEvent( const UIEventArg &arg ) {
  if ( arg.event == UIEvent::ButtonPress || arg.event == UIEvent::ButtonRepeat ) {
    int32_t value = getValue();
    int32_t prevValue = value;
    if ( arg.source == UIEventSource::ButtonB ) {
      value -= step;
      if ( value < minValue ) {
        value = minValue;
      }
    } else if ( arg.source == UIEventSource::ButtonC ) {
      value += step;
      if ( value > maxValue ) {
        value = maxValue;
      }
    }
    if ( value != prevValue ) {
      setValue( value );
      invokeEventCallback( ElementEvent::ValueChanged, (uint32_t)value );
    }
  }
}