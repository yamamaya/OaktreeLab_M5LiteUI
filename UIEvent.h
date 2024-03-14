#ifndef __M5UIEvent_H__
#define __M5UIEvent_H__

namespace OaktreeLab {
  namespace M5LiteUI {
    enum class UIEvent {
      ButtonPress,
      ButtonRepeat,
      ButtonRelease,
      ButtonLongPress
    };

    enum class UIEventSource {
      NA = 0,
      System,
      ButtonA,
      ButtonB,
      ButtonC
    };

    struct UIEventArg {
      UIEventArg( UIEvent event, UIEventSource source, uint32_t param ) {
        this->event = event;
        this->source = source;
        this->param = param;
      }
      UIEvent event;
      UIEventSource source;
      uint32_t param;
    };
  }
}

#endif