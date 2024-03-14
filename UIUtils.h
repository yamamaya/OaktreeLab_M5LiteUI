#ifndef __M5UIUtils_H__
#define __M5UIUtils_H__

#include <M5Unified.h>
#include "UITypes.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class Utils {
      public:
        static int blendColor( int color1, int color2 );
        static M5Canvas *createM5Canvas( int width, int height, int color_depth );
    };
  }
}

#endif