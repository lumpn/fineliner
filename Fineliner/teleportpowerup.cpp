#include "teleportpowerup.hpp"
#include "snake.hpp"
#include "game.hpp"
#include "texture.hpp"
#include "teleporteffect.hpp"
#include "eraser.hpp"

TeleportPowerUp::TeleportPowerUp(int2 position)
        : PowerUp(position) {
}

TeleportPowerUp::~TeleportPowerUp() {
}

void TeleportPowerUp::OnTrigger(Snake* snake, Snake* other, Game* game) {
    int2 source = snake->GetPosition();
    int2 target = game->GetRandomPosition();
    snake->SetPosition(target);
    game->AddEffect(new TeleportEffect(source, target));
    game->AddEraser(new Eraser(target, eraserRadius));
}

void TeleportPowerUp::Render(Texture* target, const Game& game) const {
    // assume we can just blit an icon here
    int2 pos = game.Cell2Screen(GetPosition());
    HDC hDC = target->GetDC();
    HBRUSH brush = CreateSolidBrush(RGB(255, 223, 0));
    SelectObject(hDC, brush);
    SelectObject(hDC, GetStockObject(NULL_PEN));
    Ellipse(hDC, pos.x - 8, pos.y - 8, pos.x + 9, pos.y + 9);
    DeleteObject(brush);
}
