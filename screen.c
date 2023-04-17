#include <string.h>
#include <math.h>

#include "screen.h"
#include "vector.h"
#include "color.h"

/*
 * \brief Draw a triangle given its corners 
 */
void drawTriangle (struct Screen * _pScreen, const struct Vector2D _aPoints[3], const struct Color * _pColor) {
    /* Determine the y-order of points */
    /* For 3 elements, there are 6 possible orderings, but 3 possible pairwise comparisons,
     * resulting in 8 combinations. 2 of them are logically impossible (ex. a>b AND b>c AND c>a).
     * Out of the pairwise comparisons we get at one shot the largest, middle and lowest
     * "y" axis, thanks to the lookup table */
    int iOrder =
        (_aPoints[0].y > _aPoints[1].y) * 4 + //a>b
        (_aPoints[0].y > _aPoints[2].y) * 2 + //a>c
        (_aPoints[1].y > _aPoints[2].y);      //b>c
        
    /* Index 0 for lowest, 1 for middle and 2 for highest */
    const int aOrderedIndex[8][3] = {
        {0, 1, 2},  // 000, a<b, a<c, b<c => a < b < c
        {0, 2, 1},  // 001, a<b, a<c, b>c => a < c < b
        {0, 0, 0},  // 010, Impossible
        {2, 0, 1},  // 011, a<b, a>c, b>c => c < a < b
        {1, 0, 2},  // 100, a>b, a<c, b<c => b < a < c
        {0, 0, 0},  // 101, Impossible
        {1, 2, 0},  // 110, a>b, a>c, b<c => b < c < a
        {2, 1, 0}   // 111, a>b, a>c, b>c => c < b < a
    };
    
    const struct Vector2D * low    = &(_aPoints[aOrderedIndex[iOrder][0]]);
    const struct Vector2D * middle = &(_aPoints[aOrderedIndex[iOrder][1]]);
    const struct Vector2D * high   = &(_aPoints[aOrderedIndex[iOrder][2]]);

    int yMin = MAX_2 (0, low->y);
    int yMiddle = MAX_2 (0, MIN_2 (_pScreen->iHeight, middle->y));
    int yMax = MIN_2 (_pScreen->iHeight, high->y);

    /* Linear interpolation in two steps: from min y until the triangle bend, and from
     * there on until max y */

    /* Precalculate constants */
    float fLH = ((float)high->x - low->x) / (high->y - low->y);
    float fLM = ((float)middle->x - low->x) / (middle->y - low->y);
    float fMH = ((float)high->x - middle->x) / (high->y - middle->y);

    for (int y = yMin; y < yMiddle; y ++) {
        /* Intersection of line with low-high */
        int x1 = low->x + roundf (fLH * (y - low->y));
        /* Intersection of line with low-middle */
        int x2 = low->x + roundf (fLM * (y - low->y));

        int xMin = MAX_2 (0, MIN_2(x1, x2));
        int xMax = MIN_2 (_pScreen->iWidth - 1, MAX_2(x1, x2));

        for (int x = xMin; x <= xMax; x ++) {
            UNSAFE_PUT_PIXEL(_pScreen, x, y, _pColor);
        }
    }

    for (int y = yMiddle; y < yMax; y ++) {
        /* Intersection of line with low-high */
        int x1 = low->x + roundf (fLH * (y - low->y));
        /* Intersection of line with middle-high */
        int x2 = middle->x + roundf (fMH * (y - middle->y));

        int xMin = MAX_2 (0, MIN_2(x1, x2));
        int xMax = MIN_2 (_pScreen->iWidth - 1, MAX_2(x1, x2));
        
        for (int x = xMin; x <= xMax; x ++) {
            UNSAFE_PUT_PIXEL(_pScreen, x, y, _pColor);
        }
    }
}

/*
 * \brief Draw a line following Bresenham's algorithm
 */
void drawLine (struct Screen * _pScreen, const struct Vector2D * _p1, const struct Vector2D * _p2, const struct Color * _pColor) {
    int dx = _p2->x - _p1->x;
    int dy = _p2->y - _p1->y;
    int iStepX = INT_ABS(dx);
    int iStepY = INT_ABS(dy);
    int incX = INT_SIGN (dx);
    int incY = INT_SIGN (dy);

    if (iStepX > iStepY) {
        int y = _p1->y;
        int iError = iStepX / 2 - iStepY;
        for (int x = _p1->x; x != _p2->x; x += incX) {
            iError += iStepY;
            if (iError >= iStepX) {
                y += incY;
                iError -= iStepX;
            }
            SAFE_PUT_PIXEL(_pScreen, x, y, _pColor);
        }
    } else {
        int x = _p1->x;
        int iError = iStepY / 2 - iStepX;
        for (int y = _p1->y; y != _p2->y; y += incY) {
            iError += iStepX;
            if (iError >= iStepY) {
                x += incX;
                iError -= iStepY;
            }
            SAFE_PUT_PIXEL(_pScreen, x, y, _pColor);
        }
    }
}

/*
 * \brief Set black background to start drawing
 */
void screenClear (struct Screen * _pScreen) {
    (void) memset (_pScreen->aPixels, 0, _pScreen->iWidth * _pScreen->iHeight * 4);
}
