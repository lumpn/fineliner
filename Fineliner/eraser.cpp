#include "eraser.hpp"
#include "game.hpp"
#include "texture.hpp"

Eraser::Eraser(int2 position_, int radius_)
        : position(position_), radius(0), maxRadius(radius_) {
}

Eraser::~Eraser() {
}

void Eraser::Update() {
    radius += 5;
}

bool Eraser::IsActive() const {
    return radius < maxRadius;
}

void Eraser::Render(Texture* target, const Game& game) const {
    int2 pos = game.Cell2Canvas(position);

    //Ellipse(target->GetDC(), pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);

    RECT rect;
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
    SetRect(&rect, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
    FillRect(target->GetDC(), &rect, brush);
    DeleteObject(brush);
}
