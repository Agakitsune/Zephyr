
#include <iostream>

#include <X11/Xlib.h>
#include "input/Keyboard.hpp"

namespace zephyr::input {

    namespace underground {

        Display *display = nullptr;

    }

    bool isKeyPressed(const Key key) {
        KeyCode x11KeyCode = XKeysymToKeycode(underground::display, (KeySym)key);
        char keys[32] = { 0 };
        XQueryKeymap(underground::display, keys);
        // >> 3 -> / 8
        // & 7 -> % 8
        return (keys[x11KeyCode >> 3] & (1 << (x11KeyCode & 7)));
    }

    bool isKeyReleased(const Key key) {
        return !isKeyPressed(key);
    }

}
