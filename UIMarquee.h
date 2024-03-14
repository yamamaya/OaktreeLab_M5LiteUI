#ifndef __M5UIMarquee_h__
#define __M5UIMarquee_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIElement.h"
#include "UILabel.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    enum class MarqueeType {
      Static,
      Blink,
      Scroll
    };

    class UIMarquee : public UILabel {
      public:
        UIMarquee( UIElement *parent, const Rectangle &rect, MarqueeType type, bool useBackBuffer = false );
        UIMarquee( UIElement *parent, const Rectangle &rect, const char *text, MarqueeType type, bool useBackBuffer = false );

        void setType( MarqueeType type );
        void setSpeed( uint32_t speed );

      protected:
        virtual void loop() override;
        virtual void draw( DrawingMode dmode ) override;

      private:
        void resetState();

        MarqueeType type;
        uint32_t speed;
        uint32_t start_time;
        uint32_t state;
        bool first;
    };
  }
}


#endif