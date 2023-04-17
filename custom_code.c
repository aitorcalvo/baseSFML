#include "custom_code.h"
#include "screen.h"
#include "color.h"

/*
 * \brief Draw something beautiful into the screen
 */
int gInt = 0;
void customDraw (struct Screen * _pScreen) {
    screenClear (_pScreen);

    gInt ++;

    for (int x = 0; x < _pScreen->iWidth; x ++) {
        for (int y = 0; y < _pScreen->iHeight; y ++) {
            struct Color eColor = {(uint8_t) ((x + gInt) % 256), (uint8_t) ((y + gInt) % 256), 0};
            UNSAFE_PUT_PIXEL (_pScreen, x, y, &eColor);
        }
    }
}