#include "powerupfactory.hpp"
#include "energypowerup.hpp"
#include "teleportpowerup.hpp"
#include "eraserpowerup.hpp"
#include "turbopowerup.hpp"
#include "enemyturbopowerup.hpp"
#include <cstdlib>

PowerUpFactory::PowerUpFactory() {
}

PowerUpFactory::~PowerUpFactory() {
}

PowerUp* PowerUpFactory::CreateRandomPowerUp(int2 position) {
    switch (rand() % 5) {
        case 0:
            return new EnergyPowerUp(position);
        case 1:
            return new TeleportPowerUp(position);
        case 2:
            return new EraserPowerUp(position);
        case 3:
            return new TurboPowerUp(position);
        case 4:
            return new EnemyTurboPowerUp(position);
    }
    return 0;
}
