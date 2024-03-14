#ifndef __M5UIWindow_H__
#define __M5UIWindow_H__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIBase.h"
#include "UIElement.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UIWindow : public UIElement {
      public:
        UIWindow( const Rectangle &rect );
        virtual ~UIWindow();

        void setFocus( UIElement *element );
        void clearFocus();
        void focusNextElement();
        UIElement *getFocusedElement();

      protected:
        virtual void draw( DrawingMode dmode ) override;

      private:
        void setFocus_inner( UIElement *element, UIElement *target );
        UIElement *getFocusedElement_inner( UIElement *element );

        UIElement *focusedElement;
    };
  }
}

#endif