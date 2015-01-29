#ifndef ERASER_HPP_
#define ERASER_HPP_

#include "int2.hpp"
#include "eraser.hpp"

class Game;
class Texture;

class Eraser {

    public:
        Eraser(int2 position, int radius);
        ~Eraser();

        void Update();
        bool IsActive() const;

        void Render(Texture* canvas, Texture* overlay, const Game& game) const;

    private:
        int2 position;
        int radius, maxRadius;
};

#endif /* ERASER_HPP_ */
