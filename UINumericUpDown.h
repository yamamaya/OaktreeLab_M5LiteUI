#ifndef __M5UINumericUpDown_h__
#define __M5UINumericUpDown_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIEvent.h"
#include "UINumericLabel.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UINumericUpDown : public UINumericLabel {
      public:
        UINumericUpDown( UIElement *parent, const Rectangle &rect, bool useBackBuffer = false );

        void setValueRange( int min, int max );
        void setValueStep( int step );

      protected:
        virtual void onUIEvent( const UIEventArg &arg ) override;

      private:
        int32_t minValue;
        int32_t maxValue;
        int32_t step;
    };
  }
}

#endif