#include "turbopowerup.hpp"
#include "snake.hpp"
#include "game.hpp"
#include "texture.hpp"
#include "teleporteffect.hpp"
#include "eraser.hpp"

TurboPowerUp::TurboPowerUp(int2 position)
        : PowerUp(position) {
}

TurboPowerUp::~TurboPowerUp() {
}

void TurboPowerUp::OnTrigger(Snake* snake, Snake* other, Game* game) {
    snake->SetStepSize(3, 30);
}

void TurboPowerUp::Render(Texture* target, const Game& game) const {
    // assume we can just blit an icon here
    int2 pos = game.Cell2Screen(GetPosition());
    HDC hDC = target->GetDC();
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hDC, brush);
    SelectObject(hDC, GetStockObject(NULL_PEN));
    Ellipse(hDC, pos.x - 8, pos.y - 8, pos.x + 9, pos.y + 9);
    DeleteObject(brush);
}
