#ifndef __M5ButtonHelper_H__
#define __M5ButtonHelper_H__

#include <M5Unified.h>
#include "UITypes.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    struct ButtonStatus {
      bool click;
      bool longpress;
      bool press;
      bool release;
      bool repeat;
      bool pressed;
      inline bool isButtonInteracted() {
        return press | release | pressed;
      }
    };

    class M5ButtonHelper {
      public:
        M5ButtonHelper();
        M5ButtonHelper( m5::Button_Class *button );
        ButtonStatus getCurrentStatus();

      private:
        m5::Button_Class *button;
        bool prevHolding;
        uint32_t timeHolding;
        uint32_t prevRepeat;
    };
  }
}


#endif