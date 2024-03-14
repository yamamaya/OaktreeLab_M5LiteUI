#ifndef __M5UIBase_H__
#define __M5UIBase_H__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIUtils.h"
#include "M5ButtonHelper.h"
#include "UIButtonGuide.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UIElement;
    class UIWindow;
    class UIScreen;

    enum class UIBaseStatus {
      None,
      Setup,
      Loop
    };

    class UIBase {
      friend class UIElement;
      friend class UIWindow;
      friend class Utils;
      public:
        UIBase( M5GFX *display );
        UIBase( M5GFX *display, UIButtonGuide *button_guide );
        ~UIBase();

        void setScreen( UIScreen *screen );
        void loop();

        M5GFX *getDisplay();
        Rectangle getScreenRectangle();
        UIBaseStatus getUIBaseStatus();
        bool getCursorBlinkState();
        void handleFocusChange();

      private:
        void draw( DrawingMode dmode );
        void updateButtonGuide();
        UIScreen *screen = NULL;
        UIButtonGuide *guide = NULL;
        M5GFX *display;
        UIBaseStatus state;
        M5ButtonHelper buttonA;
        M5ButtonHelper buttonB;
        M5ButtonHelper buttonC;
        unsigned long CursorBlinkTimer = 0;
        bool CurrentCursorState = false;
        bool CursorStateUpdated = false;
    };

    extern class UIBase *base;
  }
}

#endif