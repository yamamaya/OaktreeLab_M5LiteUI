#ifndef __M5UIButtonGuide_H__
#define __M5UIButtonGuide_H__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIUtils.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UIBase;

    class UIButtonGuide {
      friend class UIBase;

      public:
        UIButtonGuide();

        virtual int getHeight();
        void setForegroundColor( int color );
        void setBackgroundColor( int color );
        void setButtonGuide( const char* const *guides );

        static constexpr const char *buttonCommonSelect = "SELECT";
        static constexpr const char *buttonCommonUp = "<UP>";
        static constexpr const char *buttonCommonDown = "<DOWN>";
        static constexpr const char *buttonCommonPush = "<PUSH>";

      protected:
        virtual void draw( DrawingMode dmode );

        int fgColor;
        int bgColor;
        bool updated;
        const char* const *guides;
        
        static constexpr const char* const default_guides[3] = { buttonCommonSelect, buttonCommonDown, buttonCommonUp };
        static constexpr const char* const guides_without_focus[3] = { buttonCommonSelect, "", "" };
    };
  }
}

#endif