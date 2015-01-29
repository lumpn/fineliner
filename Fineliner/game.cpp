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

const int Game::screenWidth = 680;
const int Game::screenHeight = 520;
const int Game::backgroundWidth = 680;
const int Game::backgroundHeight = 520;
const int Game::backgroundLeft = 0;
const int Game::backgroundTop = 0;
const int Game::canvasWidth = 640;
const int Game::canvasHeight = 480;
const int Game::canvasLeft = 20;
const int Game::canvasTop = 20;
const int Game::gridSize = 32;
const char* Game::canvasBitmapPath = "canvas.bmp";

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
    overlay = new Texture(hDC, canvasWidth, canvasHeight);

    brushes = new HBRUSH[2];
    brushes[0] = CreateSolidBrush(RGB(0, 0, 255));
    brushes[1] = CreateSolidBrush(RGB(223, 0, 0));

    active = false;
}

Game::~Game() {
    DeleteObject(brushes[1]);
    DeleteObject(brushes[0]);
    delete[] brushes;

    delete overlay;
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
    InitializeOverlay();
    InitializeSnakes();
    InitializePowerUps();
    active = true;
}

void Game::Pause() {
    active = !active;
}

void Game::InitializeBackground() {

    HDC hDC = background->GetDC();

    // paper background
    for (int y = 0; y < backgroundHeight; y++) {
        for (int x = 0; x < backgroundWidth; x++) {
            int c = 255 - rand() % 13;
            SetPixel(hDC, x, y, RGB(c, c, c));
        }
    }

    int canvasRight = canvasLeft + canvasWidth;
    int canvasBottom = canvasTop + canvasHeight;

    // math grid
    HPEN gridPen = CreatePen(PS_SOLID, 1, RGB(191, 191, 191));
    SelectObject(hDC, gridPen);
    for (int y = canvasTop; y < canvasBottom; y += gridSize) {
        MoveToEx(hDC, canvasLeft, y, NULL);
        LineTo(hDC, canvasRight, y);
    }
    for (int x = canvasLeft; x < canvasRight; x += gridSize) {
        MoveToEx(hDC, x, canvasTop, NULL);
        LineTo(hDC, x, canvasBottom);
    }

    // canvas frame
    HPEN framePen = CreatePen(PS_SOLID, 3, RGB(191, 191, 191));
    SelectObject(hDC, GetStockObject(NULL_BRUSH));
    SelectObject(hDC, framePen);
    Rectangle(hDC, canvasLeft, canvasTop, canvasRight, canvasBottom);
    DeleteObject(framePen);
}

void Game::InitializeCanvas() {

    HDC hDC = canvas->GetDC();
    RECT rect;
    SetRect(&rect, 0, 0, canvasWidth, canvasHeight);
    FillRect(hDC, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));

    // obstacles bitmap
    HBITMAP hBitmap = (HBITMAP) LoadImage(NULL, "canvas.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap) {

        // get bitmap size
        BITMAP bm;
        GetObject(hBitmap, sizeof(bm), &bm);
        int bmLeft = (canvasWidth - bm.bmWidth) / 2;
        int bmTop = (canvasHeight - bm.bmHeight) / 2;

        // render to center
        HDC hBitmapDC = CreateCompatibleDC(hDC);
        SelectObject(hBitmapDC, hBitmap);
        BitBlt(hDC, bmLeft, bmTop, bm.bmWidth, bm.bmHeight, hBitmapDC, 0, 0, SRCCOPY);
        DeleteDC(hBitmapDC);
    }
}

void Game::InitializeOverlay() const {
    HDC hDC = overlay->GetDC();
    RECT rect;
    SetRect(&rect, 0, 0, canvasWidth, canvasHeight);
    FillRect(hDC, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));
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

    // clear overlay
    InitializeOverlay();

    // erasers
    for (EraserVector::const_iterator it = erasers.begin(); it != erasers.end(); ++it) {
        (*it)->Render(canvas, overlay, *this);
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
    BitBlt(buffer->GetDC(), canvasLeft, canvasTop, canvasWidth, canvasWidth, overlay->GetDC(), 0, 0, SRCAND);

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
    TextOut(buffer->GetDC(), screenWidth - 10, 5, text, num);
    num = snprintf(text, 32, "%d", snakes[1]->GetNumDeaths());
    TextOut(buffer->GetDC(), 10, 5, text, num);

    // render buffer
    BitBlt(hDC, 0, 0, screenWidth, screenHeight, buffer->GetDC(), 0, 0, SRCCOPY);
}

void Game::Update() {
    if (!active) {
        return;
    }

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

    // check canvas
    int2 pixel = Cell2Canvas(cell);
    COLORREF color = GetPixel(canvas->GetDC(), pixel.x, pixel.y);
    if (color != RGB(255, 255, 255))
        return false;

    // check overlay
    color = GetPixel(overlay->GetDC(), pixel.x, pixel.y);
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
