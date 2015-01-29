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
    HDC hDC = target->GetDC();
    HBRUSH brush = CreateSolidBrush(RGB(0, 191, 0));
    SelectObject(hDC, brush);
    SelectObject(hDC, GetStockObject(NULL_PEN));
    Ellipse(hDC, pos.x - 8, pos.y - 8, pos.x + 9, pos.y + 9);
    DeleteObject(brush);
}
