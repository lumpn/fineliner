#include "texture.hpp"

Texture::Texture(HDC hBaseDC, int width_, int height_)
        : width(width_), height(height_) {
    hBitmap = CreateCompatibleBitmap(hBaseDC, width, height);
    hDC = CreateCompatibleDC(hBaseDC);
    SelectObject(hDC, hBitmap);
}

Texture::~Texture() {
    DeleteDC(hDC);
    DeleteObject(hBitmap);
}

int Texture::GetWidth() const {
    return width;
}

int Texture::GetHeight() const {
    return height;
}

HDC Texture::GetDC() const {
    return hDC;
}
