#include "energypowerup.hpp"
#include "snake.hpp"
#include "game.hpp"
#include "texture.hpp"

EnergyPowerUp::EnergyPowerUp(int2 position)
        : PowerUp(position) {
}

EnergyPowerUp::~EnergyPowerUp() {
}

void EnergyPowerUp::OnTrigger(Snake* snake, Snake* other, Game* game) {
    snake->IncEnergy(energy);
}

void EnergyPowerUp::Render(Texture* target, const Game& game) const {
    // assume we can just blit an icon here
    int2 pos = game.Cell2Screen(GetPosition());
    RECT rect;
    HBRUSH brush = CreateSolidBrush(RGB(0, 191, 0));
    SetRect(&rect, pos.x - 6, pos.y - 6, pos.x + 7, pos.y + 7);
    FillRect(target->GetDC(), &rect, brush);
    DeleteObject(brush);
}
