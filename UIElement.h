#ifndef __M5UIElement_h__
#define __M5UIElement_h__

#include <M5Unified.h>
#include "UITypes.h"
#include "UIUtils.h"
#include "UIEvent.h"

namespace OaktreeLab {
  namespace M5LiteUI {
    class UIBase;
    class UIWindow;
    class UIElement {
      friend class UIBase;
      friend class UIWindow;
      public:
        UIElement( UIElement *parent );
        UIElement( UIElement *parent, const Rectangle &rect, bool useBackBuffer );
        UIElement( UIElement *parent, const Rectangle &rect, BackBufferType backbuffer = BackBufferType::None );
        virtual ~UIElement();

        void addChild( UIElement *child );
        void setFont( const lgfx::IFont &font );
        void setFont( const lgfx::IFont *font );
        void setForegroundColor( int color );
        void setBackgroundColor( int color );
        void setBorderColor( int color );
        void showBorder( bool show );
        void setEventCallback( std::function<void(UIElement*,ElementEvent,uint32_t)> cb );
        void setEnable( bool enable );
        void enable();
        void disable();
        bool isEnabled();
        void setUpdate( bool total_redraw = false );
        UIElement *getNextElement( UIElement *target, bool focusableOnly = false );
        virtual const char* const *getButtonGuide();

      protected:
        virtual void setup();
        virtual void loop();
        virtual void draw( DrawingMode dmode );
        virtual void drawOverlay();
        virtual void onUIEvent( const UIEventArg &arg );

        void giveFocus();
        void takeFocus();
        DrawingContext beginDraw();
        void endDraw();
        M5Canvas *createBackBuffer( int width, int height, int colorDepth );
        int getBackBufferColorDepth();
        int getParentBackgroundColor();
        Rectangle getClientRectangle();
        void updateForegroundColor( int color );
        void updateBackgroundColor( int color );
        void invokeEventCallback( ElementEvent event, uint32_t arg );

        M5GFX *display;
        UIElement *parent;
        std::vector<UIElement*> children;
        Rectangle rectElement;
        bool canFocus;
        bool hasFocus;
        bool enabled;
        bool updated;
        const lgfx::IFont *font;
        int fgColorOrg;
        int bgColorOrg;
        int fgColor;
        int bgColor;
        int borderColor;
        bool border;
        M5Canvas *backBuffer;
        std::function<void(UIElement*,ElementEvent,uint32_t)> eventCallback;

      private:
        UIElement();
        void dispatchSetup();
        void dispatchLoop();
        void dispatchDraw( DrawingMode dmode );
        void render();
        UIElement *getNextElement_inner( UIElement *target, bool focusableOnly, int *count, bool *found );

        bool isSetupDone;
        bool needsTotalRedraw;
    };
  }
}

#endif