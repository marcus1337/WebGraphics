#include "Text.h"

int Text::estimateWidth() {
    int charWidth = (pixelHeight / 2);
    return charWidth * text.length() - text.length();
}