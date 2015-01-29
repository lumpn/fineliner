#include "powerupfactory.hpp"
#include "energypowerup.hpp"
#include "teleportpowerup.hpp"
#include "eraserpowerup.hpp"
#include <cstdlib>

PowerUpFactory::PowerUpFactory() {
}

PowerUpFactory::~PowerUpFactory() {
}

PowerUp* PowerUpFactory::CreateRandomPowerUp(int2 position) {
    switch (rand() % 3) {
        case 0:
            return new EnergyPowerUp(position);
        case 1:
            return new TeleportPowerUp(position);
        case 2:
            return new EraserPowerUp(position);
    }
    return 0;
}
