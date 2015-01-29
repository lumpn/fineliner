#ifndef ERASER_POWERUP_HPP_
#define ERASER_POWERUP_HPP_

#include "powerup.hpp"

class Snake;
class Game;
class Texture;

class EraserPowerUp: public PowerUp {

    public:
        explicit EraserPowerUp(int2 position);
        virtual ~EraserPowerUp();

        virtual void Render(Texture* target, const Game& game) const;
        virtual void OnTrigger(Snake* snake, Snake* other, Game* game);

    private:
        static const int radius = 50;
};

#endif /* ERASER_POWERUP_HPP_ */
