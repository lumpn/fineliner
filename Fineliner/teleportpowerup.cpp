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
    RECT rect;
    HBRUSH brush = CreateSolidBrush(RGB(255, 223, 0));
    SetRect(&rect, pos.x - 6, pos.y - 6, pos.x + 7, pos.y + 7);
    FillRect(target->GetDC(), &rect, brush);
    DeleteObject(brush);
}
