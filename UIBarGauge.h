#ifndef __M5UIBarGauge_h__
#define __M5UIBarGauge_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIElement.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    enum class BarGaugeType {
      Horizontal,
      Vertical
    };

    class UIBarGauge : public UIElement {
      public:
        UIBarGauge( UIElement *parent, const Rectangle &rect, BarGaugeType type );

        void showScale( bool scale );
        void setScaleCount( int count );
        void setScaleSize( int size );
        void setValueRange( int min, int max );
        void setValue( int value );

      protected:
        virtual void draw( DrawingMode dmode ) override;

        BarGaugeType type;
        bool scale;
        int scaleCount;
        int scaleSize;
        int minValue;
        int maxValue;
        int value;
    };
  }
}

#endif