#include "enemyturbopowerup.hpp"
#include "snake.hpp"
#include "game.hpp"
#include "texture.hpp"
#include "teleporteffect.hpp"
#include "eraser.hpp"

EnemyTurboPowerUp::EnemyTurboPowerUp(int2 position)
        : PowerUp(position) {
}

EnemyTurboPowerUp::~EnemyTurboPowerUp() {
}

void EnemyTurboPowerUp::OnTrigger(Snake* snake, Snake* other, Game* game) {
    other->SetStepSize(3, 30);
}

void EnemyTurboPowerUp::Render(Texture* target, const Game& game) const {
    // assume we can just blit an icon here
    int2 pos = game.Cell2Screen(GetPosition());
    HDC hDC = target->GetDC();
    HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
    SelectObject(hDC, brush);
    SelectObject(hDC, GetStockObject(NULL_PEN));
    Ellipse(hDC, pos.x - 8, pos.y - 8, pos.x + 9, pos.y + 9);
    DeleteObject(brush);
}
