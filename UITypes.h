#ifndef __M5UITypes_H__
#define __M5UITypes_H__

namespace OaktreeLab {
  namespace M5LiteUI {
    enum class DrawingMode {
      TotalRedraw,
      PartialRedraw
    };

    enum class TextAlignment {
      TopLeft = (int)textdatum_t::top_left,
      TopCenter = (int)textdatum_t::top_center,
      TopRight = (int)textdatum_t::top_right,
      MiddleLeft = (int)textdatum_t::middle_left,
      MiddleCenter = (int)textdatum_t::middle_center,
      MiddleRight = (int)textdatum_t::middle_right,
      BottomLeft = (int)textdatum_t::bottom_left,
      BottomCenter = (int)textdatum_t::bottom_center,
      BottomRight = (int)textdatum_t::bottom_right
    };

    enum class ImageAlignment {
      TopLeft,
      Center,
      Stretch
    };

    enum class ElementEvent {
      Clicked,
      ValueChanged
    };

    struct Rectangle {
        Rectangle() {
          this->left = 0;
          this->top = 0;
          this->width = 0;
          this->height = 0;
        }
        Rectangle( int left, int top, int width, int height ) {
          this->left = left;
          this->top = top;
          this->width = width;
          this->height = height;
        }
        int left;
        int top;
        int width;
        int height;
    };

    struct DrawingContext {
      lgfx::v1::LGFXBase *canvas;
      Rectangle rect;
    };

    enum class BackBufferType {
        None = 0,
        Palette1bit = 1,
        Palette2bit = 2,
        Palette4bit = 4,
        RGB16bit = 16
    };
  }
}

#endif