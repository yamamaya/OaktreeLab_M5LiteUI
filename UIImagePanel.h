#ifndef __M5UIImagePanel_h__
#define __M5UIImagePanel_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIElement.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UIImagePanel : public UIElement {
      public:
        UIImagePanel( UIElement *parent, const Rectangle &rect, M5Canvas *image = NULL );

        void setImage( M5Canvas *image );
        M5Canvas *getImage();
        void setImageAlignment( ImageAlignment alignment );

      protected:
        virtual void draw( DrawingMode dmode ) override;

      private:
        M5Canvas *image;
        ImageAlignment alignment;
    };
  }
}

#endif