#include "teleporteffect.hpp"
#include "game.hpp"
#include "texture.hpp"
#include <windows.h>

TeleportEffect::TeleportEffect(int2 pos1_, int2 pos2_)
        : Effect(duration), pos1(pos1_), pos2(pos2_) {
}

TeleportEffect::~TeleportEffect() {
}

void TeleportEffect::Render(Texture* target, const Game& game) const {
    int2 p1 = game.Cell2Screen(pos1);
    int2 p2 = game.Cell2Screen(pos2);
    MoveToEx(target->GetDC(), p1.x, p1.y, NULL);
    LineTo(target->GetDC(), p2.x, p2.y);
}
