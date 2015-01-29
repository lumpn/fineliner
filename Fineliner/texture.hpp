#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <windows.h>

class Texture {
    public:
        Texture(HDC hBaseDC, int width, int height);
        ~Texture();

        int GetWidth() const;
        int GetHeight() const;
        HDC GetDC() const;

    private:
        int width, height;
        HDC hDC;
        HBITMAP hBitmap;
};

#endif /* TEXTURE_HPP_ */
