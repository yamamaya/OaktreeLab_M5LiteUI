#ifndef __M5UIButton_h__
#define __M5UIButton_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIEvent.h"
#include "UILabel.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UIButton : public UILabel {
      public:
        UIButton( UIElement *parent, const Rectangle &rect, const char *text );

        virtual const char* const *getButtonGuide() override;

      protected:
        virtual void draw( DrawingMode dmode ) override;
        virtual void drawOverlay() override;
        virtual void onUIEvent( const UIEventArg &arg ) override;

      private:
        void updateButtonStatus();
        int ButtonCount;
        bool ButtonState;
        bool IsFirstTotalRedraw;
    };
  }
}

#endif