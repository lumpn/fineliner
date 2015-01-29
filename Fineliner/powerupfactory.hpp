#ifndef POWERUP_FACTORY_HPP_
#define POWERUP_FACTORY_HPP_

#include "int2.hpp"

class PowerUp;

class PowerUpFactory {

    public:
        PowerUpFactory();
        ~PowerUpFactory();

        PowerUp* CreateRandomPowerUp(int2 position);
};

#endif /* POWERUP_FACTORY_HPP_ */
