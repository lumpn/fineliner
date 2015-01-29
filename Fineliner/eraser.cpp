#include "eraser.hpp"
#include "game.hpp"
#include "texture.hpp"

Eraser::Eraser(int2 position_, int radius_)
        : position(position_), radius(5), maxRadius(radius_) {
}

Eraser::~Eraser() {
}

void Eraser::Update() {
    radius += 5;
}

bool Eraser::IsActive() const {
    return radius < maxRadius;
}

void Eraser::Render(Texture* canvas, Texture* overlay, const Game& game) const {
    int2 pos = game.Cell2Canvas(position);

// erase canvas
    HDC hDC = canvas->GetDC();
    SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    SelectObject(hDC, GetStockObject(NULL_PEN));
    Ellipse(hDC, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);

    // ring
    hDC = overlay->GetDC();
    HPEN pen = CreatePen(PS_SOLID, 6, RGB(128, 128, 128));
    SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    SelectObject(hDC, pen);
    Ellipse(hDC, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
    DeleteObject(pen);
}
