#ifndef __M5UIUpDownList_h__
#define __M5UIUpDownList_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIEvent.h"
#include "UINumericLabel.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UIUpDownList : public UILabel {
      public:
        UIUpDownList( UIElement *parent, const Rectangle &rect, bool useBackBuffer = false );
        UIUpDownList( UIElement *parent, const Rectangle &rect, std::vector<const char*> const &list, bool useBackBuffer = false );

        void setList( std::vector<const char*> const &list );
        int getIndex();
        void setIndex( int index );

      protected:
        virtual void onUIEvent( const UIEventArg &arg ) override;

      private:
        std::vector<const char*> list;
        int index;
    };
  }
}

#endif