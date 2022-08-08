#include "Image.h"

#ifndef BUTTONIMAGE_H
#define BUTTONIMAGE_H

class ButtonImage : public Image {

public:
    virtual Image* clone() const override;
    virtual void render(Graphics& _graphics) override;
};

#endif // !BUTTONIMAGE_H
