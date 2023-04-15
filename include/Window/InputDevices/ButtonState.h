#ifndef IO_BUTTON_STATE_H
#define IO_BUTTON_STATE_H

struct ButtonState {
    bool pressed = false;
    bool pressEvent = false;
    bool unPressEvent = false;
    void clearEvents() {
        pressEvent = false;
        unPressEvent = false;
    }
};

#endif // !IO_BUTTON_STATE_H
