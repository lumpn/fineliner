#ifndef TURBO_POWERUP_HPP_
#define TURBO_POWERUP_HPP_

#include "powerup.hpp"

class Snake;
class Game;
class Texture;

class TurboPowerUp : public PowerUp {

    public:
        explicit TurboPowerUp(int2 position);
        virtual ~TurboPowerUp();

        virtual void Render(Texture* target, const Game& game) const;
        virtual void OnTrigger(Snake* snake, Snake* other, Game* game);
};

#endif /* TURBO_POWERUP_HPP_ */
