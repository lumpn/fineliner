#ifndef GAME_HPP_
#define GAME_HPP_

#include <windows.h>
#include "dir2.hpp"
#include "int2.hpp"
#include <vector>

class Snake;
class SnakeController;
class PowerUp;
class PowerUpFactory;
class Texture;
class Effect;
class Eraser;

class Game {
    public:
        explicit Game(HDC hDC);
        ~Game();

        void Initialize();
        void Restart();
        void Pause();

        void Render(HDC hDC) const;
        void Update();

        void Steer(int player, dir2 direction);
        void Jump(int player);
        void Stop(int player);

        bool IsCellFree(int2 cell) const;
        int2 GetRandomPosition() const;

        int2 Cell2Canvas(int2 position) const;
        int2 Cell2Screen(int2 position) const;

        void AddEffect(Effect* effect);
        void AddEraser(Eraser* eraser);

    private:
        typedef Snake* SnakePtr;
        typedef SnakeController* ControllerPtr;
        typedef PowerUp* PowerUpPtr;
        typedef Effect* EffectPtr;
        typedef Eraser* EraserPtr;
        typedef std::vector<EffectPtr> EffectVector;
        typedef std::vector<EraserPtr> EraserVector;

    private:
        void InitializeBackground();
        void InitializeCanvas();
        void InitializeOverlay() const;
        void InitializeSnakes();
        void InitializePowerUps();

    private:
        SnakePtr* snakes;
        ControllerPtr* controllers;
        PowerUpPtr* powerUps;
        PowerUpFactory* powerUpFactory;
        Texture* buffer;
        Texture* background;
        Texture* canvas;
        Texture* overlay;
        HBRUSH* brushes;
        EffectVector effects;
        EraserVector erasers;
        bool active;

    private:
        static const int screenWidth;
        static const int screenHeight;
        static const int backgroundWidth;
        static const int backgroundHeight;
        static const int backgroundLeft;
        static const int backgroundTop;
        static const int canvasWidth;
        static const int canvasHeight;
        static const int canvasLeft;
        static const int canvasTop;
        static const int gridSize;
        static const char* canvasBitmapPath;
};

#endif /* GAME_HPP_ */
