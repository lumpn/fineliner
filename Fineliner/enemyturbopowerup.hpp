#ifndef ENEMY_TURBO_POWERUP_HPP_
#define ENEMY_TURBO_POWERUP_HPP_

#include "powerup.hpp"

class Snake;
class Game;
class Texture;

class EnemyTurboPowerUp : public PowerUp {

    public:
        explicit EnemyTurboPowerUp(int2 position);
        virtual ~EnemyTurboPowerUp();

        virtual void Render(Texture* target, const Game& game) const;
        virtual void OnTrigger(Snake* snake, Snake* other, Game* game);
};

#endif /* ENEMY_TURBO_POWERUP_HPP_ */
