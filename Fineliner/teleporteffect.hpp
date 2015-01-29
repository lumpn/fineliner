#ifndef TELEPORT_EFFECT_HPP_
#define TELEPORT_EFFECT_HPP_

#include "int2.hpp"
#include "effect.hpp"

class TeleportEffect: public Effect {

    public:
        explicit TeleportEffect(int2 pos1, int2 pos2);
        virtual ~TeleportEffect();

        virtual void Render(Texture* target, const Game& game) const;

    private:
        int2 pos1, pos2;

    private:
        static const int duration = 10; // [frames]
};

#endif /* TELEPORT_EFFECT_HPP_ */
