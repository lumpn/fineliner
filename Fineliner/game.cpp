#include "game.hpp"
#include "snake.hpp"
#include "snakecontroller.hpp"
#include "powerup.hpp"
#include "powerupfactory.hpp"
#include "texture.hpp"
#include "effect.hpp"
#include "eraser.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>

Game::Game(HDC hDC) {

    srand(reinterpret_cast<unsigned int>(hDC));

    snakes = new SnakePtr[2];
    snakes[0] = new Snake(int2(canvasWidth / 3 - 10, 10), dir2::Up());
    snakes[1] = new Snake(int2(10, 10), dir2::Up());

    controllers = new ControllerPtr[2];
    controllers[0] = new SnakeController(snakes[0]);
    controllers[1] = new SnakeController(snakes[1]);

    powerUpFactory = new PowerUpFactory();

    powerUps = new PowerUpPtr[10];
    for (int i = 0; i < 10; i++) {
        powerUps[i] = powerUpFactory->CreateRandomPowerUp(GetRandomPosition());
    }

    buffer = new Texture(hDC, screenWidth, screenHeight);
    background = new Texture(hDC, backgroundWidth, backgroundHeight);
    canvas = new Texture(hDC, canvasWidth, canvasHeight);

    brushes = new HBRUSH[5];
    brushes[0] = CreateSolidBrush(RGB(0, 0, 255));
    brushes[1] = CreateSolidBrush(RGB(223, 0, 0));
    brushes[2] = CreateSolidBrush(RGB(0, 191, 0));
    brushes[3] = CreateSolidBrush(RGB(0, 0, 0));
    brushes[4] = CreateSolidBrush(RGB(255, 255, 255));

}

Game::~Game() {
    DeleteObject(brushes[4]);
    DeleteObject(brushes[3]);
    DeleteObject(brushes[2]);
    DeleteObject(brushes[1]);
    DeleteObject(brushes[0]);
    delete[] brushes;

    delete canvas;
    delete background;
    delete buffer;

    delete powerUpFactory;

    // TODO delete each object
    delete[] powerUps;
    delete[] controllers;
    delete[] snakes;
}

void Game::Initialize() {
    InitializeBackground();
    Restart();
}

void Game::Restart() {
    InitializeCanvas();
    InitializeSnakes();
    InitializePowerUps();
}

void Game::InitializeBackground() {
    HDC hDC = background->GetDC();
    for (int y = 0; y < backgroundHeight; y++) {
        for (int x = 0; x < backgroundWidth; x++) {
            int c = 255 - rand() % 13;
            SetPixel(hDC, x, y, RGB(c, c, c));
        }
    }
}

void Game::InitializeCanvas() {
    HDC hDC = canvas->GetDC();
    RECT rect;
    SetRect(&rect, 0, 0, canvasWidth, canvasHeight);
    FillRect(hDC, &rect, brushes[4]);

    // TODO obstacles (load bitmap)
}

void Game::InitializeSnakes() {
    snakes[0]->SetPosition(int2(canvasWidth / 3 - 10, 10));
    snakes[0]->SetDirection(dir2::Up());
    snakes[1]->SetPosition(int2(10, 10));
    snakes[1]->SetDirection(dir2::Up());
}

void Game::InitializePowerUps() {
    for (int i = 0; i < 10; i++) {
        powerUps[i]->SetPosition(GetRandomPosition());
    }
}

static int random(int min, int max) {
    int range = max - min;
    int value = rand() % range;
    return value + min;
}

int2 Game::GetRandomPosition() const {
    int x = random(10, canvasWidth / 3 - 10);
    int y = random(10, canvasHeight / 3 - 10);
    return int2(x, y);
}

void Game::Render(HDC hDC) const {
    RECT rect;

    // erasers
    for (EraserVector::const_iterator it = erasers.begin(); it != erasers.end(); ++it) {
        (*it)->Render(canvas, *this);
    }

    // render to canvas
    for (int i = 0; i < 2; i++) {
        int2 pos = Cell2Canvas(snakes[i]->GetPosition());
        SetRect(&rect, pos.x - 1, pos.y - 1, pos.x + 2, pos.y + 2);
        FillRect(canvas->GetDC(), &rect, brushes[i]);
    }

    // render to buffer
    BitBlt(buffer->GetDC(), backgroundLeft, backgroundTop, backgroundWidth, backgroundHeight, background->GetDC(), 0, 0, SRCCOPY);
    BitBlt(buffer->GetDC(), canvasLeft, canvasTop, canvasWidth, canvasWidth, canvas->GetDC(), 0, 0, SRCAND);

    // power ups
    for (int i = 0; i < 10; i++) {
        powerUps[i]->Render(buffer, *this);
    }

    // effects
    for (EffectVector::const_iterator it = effects.begin(); it != effects.end(); ++it) {
        (*it)->Render(buffer, *this);
    }

    // energy bars
    int px[] = { screenWidth - 9, 1 };
    for (int i = 0; i < 2; i++) {
        int energy = snakes[i]->GetEnergy();
        SetRect(&rect, px[i], canvasHeight - energy, px[i] + 8, canvasHeight);
        FillRect(buffer->GetDC(), &rect, brushes[i]);
    }

    // deaths
    char text[32];
    int num;
    num = snprintf(text, 32, "%d", snakes[0]->GetNumDeaths());
    TextOut(buffer->GetDC(), canvasWidth, 5, text, num);
    num = snprintf(text, 32, "%d", snakes[1]->GetNumDeaths());
    TextOut(buffer->GetDC(), 10, 5, text, num);

    // render buffer
    BitBlt(hDC, 0, 0, screenWidth, screenHeight, buffer->GetDC(), 0, 0, SRCCOPY);
}

void Game::Update() {
    snakes[0]->Update(this);
    snakes[1]->Update(this);
    controllers[0]->Update();
    controllers[1]->Update();

    // check power ups
    for (int k = 0; k < 2; k++) {
        Snake* snake = snakes[k];
        Snake* other = snakes[(k + 1) % 2];
        for (int i = 0; i < 10; i++) {
            PowerUpPtr powerUp = powerUps[i];
            int ds = int2::distanceSqr(snake->GetPosition(), powerUp->GetPosition());
            if (ds < 10) {
                powerUp->OnTrigger(snake, other, this);
                delete powerUp;
                powerUps[i] = powerUpFactory->CreateRandomPowerUp(GetRandomPosition());
            }
        }
    }

    // update effects
    {
        EffectVector::iterator it = effects.begin();
        while (it != effects.end()) {
            EffectPtr effect = *it;
            if (effect->IsActive()) {
                effect->Update();
                ++it;
            } else {
                delete effect;
                it = effects.erase(it);
            }
        }
    }

    // update erasers
    {
        EraserVector::iterator it = erasers.begin();
        while (it != erasers.end()) {
            EraserPtr eraser = *it;
            if (eraser->IsActive()) {
                eraser->Update();
                ++it;
            } else {
                delete eraser;
                it = erasers.erase(it);
            }
        }
    }
}

void Game::Steer(int player, dir2 direction) {
    controllers[player]->Steer(direction);
}

void Game::Jump(int player) {
    controllers[player]->Jump();
}

void Game::Stop(int player) {
    snakes[player]->SetDirection(dir2::None());
}

bool Game::IsCellFree(int2 cell) const {
    int2 pixel = Cell2Canvas(cell);
    COLORREF color = GetPixel(canvas->GetDC(), pixel.x, pixel.y);
    return (color == RGB(255, 255, 255));
}

int2 Game::Cell2Canvas(int2 cell) const {
    int2 pixel = cell * 3;
    pixel.y = canvasHeight - pixel.y;
    return pixel;
}

int2 Game::Cell2Screen(int2 position) const {
    int2 pos = Cell2Canvas(position);
    pos.x += canvasLeft;
    pos.y += canvasTop;
    return pos;
}

void Game::AddEffect(Effect* effect) {
    effects.push_back(effect);
}

void Game::AddEraser(Eraser* eraser) {
    erasers.push_back(eraser);
}
