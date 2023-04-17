#ifndef __SCREEN_H__
#define __SCREEN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_2(_a,_b) ((_a)>(_b) ? (_a) : (_b))
#define MAX_3(_a,_b,_c) MAX_2(MAX_2((_a), (_b)), (_c))
#define MIN_2(_a,_b) ((_a)<(_b) ? (_a) : (_b))
#define MIN_3(_a,_b,_c) MIN_2(MIN_2((_a), (_b)), (_c))
#define INT_ABS(_x) ((_x)>0 ? (_x) : -(_x))
#define INT_SIGN(_x) ((_x)>=0 ? 1 : -1)
#define PI 3.14159265358979323846

struct Screen {
    uint8_t * aPixels;
    int iWidth;
    int iHeight;
};

/* Helper functions */
#define UNSAFE_PUT_PIXEL(_scr,_x,_y,_color) do{ \
        uint32_t iBase = 4 * (_y * _scr->iWidth + _x); \
        _scr->aPixels[iBase] = (_color)->r; \
        _scr->aPixels[iBase+1] = (_color)->g; \
        _scr->aPixels[iBase+2] = (_color)->b; \
        _scr->aPixels[iBase+3] = 0xFF; \
    } while (0)

#define SAFE_PUT_PIXEL(_scr,_x,_y,_color) do{ \
        if ((_x) >= 0 && \
            (_x) < _scr->iWidth && \
            (_y) >= 0 && \
            (_y) < _scr->iHeight) \
        { UNSAFE_PUT_PIXEL(_scr, _x, _y, _color); } \
    } while (0)

void screenClear (struct Screen * _pScreen);

#ifdef __cplusplus
}
#endif

#endif
