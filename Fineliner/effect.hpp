#ifndef EFFECT_HPP_
#define EFFECT_HPP_

class Game;
class Texture;

class Effect {
    public:
        explicit Effect(int duration);
        virtual ~Effect() = 0;

        virtual void Update();
        virtual bool IsActive() const;

        virtual void Render(Texture* target, const Game& game) const = 0;

    private:
        int duration; // [frames]
};

#endif /* EFFECT_HPP_ */
