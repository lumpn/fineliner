#ifndef ENERGY_POWERUP_HPP_
#define ENERGY_POWERUP_HPP_

#include "int2.hpp"
#include "powerup.hpp"

class Snake;
class Game;
class Texture;

class EnergyPowerUp: public PowerUp {

    public:
        explicit EnergyPowerUp(int2 position);
        virtual ~EnergyPowerUp();

        virtual void Render(Texture* target, const Game& game) const;
        virtual void OnTrigger(Snake* snake, Snake* other, Game* game);

    private:
        static const int energy = 50;
};

#endif /* ENERGY_POWERUP_HPP_ */
