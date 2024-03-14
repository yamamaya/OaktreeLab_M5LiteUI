#ifndef __M5UILabel_h__
#define __M5UILabel_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIElement.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UILabel : public UIElement {
      public:
        UILabel( UIElement *parent, const Rectangle &rect, bool useBackBuffer = false );
        UILabel( UIElement *parent, const Rectangle &rect, const char *text, bool useBackBuffer = false );

        void setText( const char *text );
        const char *getText();
        void setTextAlignment( TextAlignment align );

      protected:
        virtual void draw( DrawingMode dmode ) override;
        TextAlignment textAlignment;
        std::string text;
    };
  }
}

#endif