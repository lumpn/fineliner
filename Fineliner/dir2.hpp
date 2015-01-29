#ifndef DIRECTION_HPP_
#define DIRECTION_HPP_

#include "int2.hpp"

struct dir2 {
    public:
        enum dir {
            DIR_NONE, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT
        };

    public:
        dir value;

    public:
        dir2();
        explicit dir2(dir value);
        dir2(const dir2& other);
        ~dir2();

        bool operator==(const dir2& other) const;
        void operator=(const dir2& other);

        int2 ToInt2() const;
        dir2 Opposite() const;

    public:
        static dir2 None();
        static dir2 Up();
        static dir2 Down();
        static dir2 Left();
        static dir2 Right();
};

#endif /* DIRECTION_HPP_ */
