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
    if ( arg.event == UIEvent::ButtonPress ) {
      repeatCount = 0;
    } else if ( arg.event == UIEvent::ButtonRepeat ) {
      repeatCount ++;
    }
    int32_t value = getValue();
    int32_t prevValue = value;
    int32_t step_acc;
    if ( repeatCount < 5 ) {
      step_acc = step;
    } else if ( repeatCount < 20 ) {
      step_acc = step * 5;
    } else if ( repeatCount < 30 ) {
      step_acc = step * 10;
    } else {
      step_acc = step * 50;
    }
    if ( arg.source == UIEventSource::ButtonB ) {
      value -= step_acc;
      if ( value < minValue ) {
        value = minValue;
      }
    } else if ( arg.source == UIEventSource::ButtonC ) {
      value += step_acc;
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