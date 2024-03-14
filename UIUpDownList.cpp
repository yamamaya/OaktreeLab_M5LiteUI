#include "UIUpDownList.h"

using namespace OaktreeLab::M5LiteUI;

OaktreeLab::M5LiteUI::UIUpDownList::UIUpDownList( UIElement *parent, const Rectangle &rect, bool useBackBuffer ) : UILabel( parent, rect, useBackBuffer ) {
  this->showBorder( true );  
  this->canFocus = true;
  setIndex( -1 );
}

OaktreeLab::M5LiteUI::UIUpDownList::UIUpDownList( UIElement *parent, const Rectangle &rect, std::vector<const char*> const &list, bool useBackBuffer ) : UIUpDownList( parent, rect, useBackBuffer ) {
  this->list = list;
}

void OaktreeLab::M5LiteUI::UIUpDownList::setList( std::vector<const char*> const &list ) {
  this->list = list;
  if ( list.size() > 0 ) {
    if ( index >= list.size() ) {
      index = list.size() - 1;
    }
    setText( list[index] );
  } else {
    index = -1;
    setText( "" );
  }
}

int OaktreeLab::M5LiteUI::UIUpDownList::getIndex() {
  return index;
}

void OaktreeLab::M5LiteUI::UIUpDownList::setIndex( int index ) {
  int prevIndex = this->index;
  if ( index >= 0 && index < list.size() ) {
    this->index = index;
  } else {
    this->index = -1;
  }
  if ( this->index != prevIndex ) {
    if ( this->index >= 0 ) {
      setText( list[index] );
    } else {
      setText( "" );
    }
  }
}

void OaktreeLab::M5LiteUI::UIUpDownList::onUIEvent( const UIEventArg &arg ) {
  if ( arg.event == UIEvent::ButtonPress || arg.event == UIEvent::ButtonRepeat ) {
    int newIndex;
    if ( arg.source == UIEventSource::ButtonB ) {
      newIndex = index - 1;
    } else if ( arg.source == UIEventSource::ButtonC ) {
      if ( index < 0 ) {
        newIndex = 0;
      } else {
        newIndex = index + 1;
      }
    } else {
      newIndex = index;
    }
    if ( list.size() == 0 ) {
      newIndex = -1;
    } else if ( newIndex < 0 ) {
      newIndex = list.size() - 1;
    } else if ( newIndex >= list.size() ) {
      newIndex = 0;
    }
    if ( newIndex != index ) {
      setIndex( newIndex );
      invokeEventCallback( ElementEvent::ValueChanged, (uint32_t)index );
    }
  }
}