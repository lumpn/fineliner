#ifndef INT2_HPP_
#define INT2_HPP_

struct int2 {
    public:
        int x, y;

    public:
        int2();
        explicit int2(int x, int y);
        int2(const int2& other);
        ~int2();

        void operator=(const int2& other);
        void operator+=(const int2& other);
        void operator*=(int scale);
        int2 operator*(int scale) const;

        static int distanceSqr(const int2& a, const int2& b);
};

#endif /* INT2_HPP_ */
