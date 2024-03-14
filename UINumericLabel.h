#ifndef __M5UINumericLabel_h__
#define __M5UINumericLabel_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIElement.h"
#include "UILabel.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UINumericLabel : public UILabel {
      public:
        UINumericLabel( UIElement *parent, const Rectangle &rect, bool useBackBuffer = false );

        void setValue( int32_t value );
        int32_t getValue();
        void setFormat( const char *format );
        const char *getFormat();

      private:
        void updateText();
        int32_t value;
        std::string format;
    };
  }
}


#endif