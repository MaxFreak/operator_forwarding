//
// Created by Bernd Lappas on 22.11.15.
//

#ifndef OPERATOR_FORWARDING_GP_POINT_H
#define OPERATOR_FORWARDING_GP_POINT_H

#include <ostream>
#include <string>

namespace gp
{
    using std::ostream;
    using std::string;

    template<typename T>
    class gp_point
    {
    public:

        gp_point();

        gp_point(T X, T Y);

        template<typename U>
        explicit gp_point(const gp_point<U> &Point);

        void print_to(ostream &Out, size_t Position) const
        {
            Out << string(Position, ' ') << "(" << m_X << "/" << m_Y << ")";
        }

        T m_X; /// X coordinate of the point
        T m_Y; /// Y coordinate of the point
    };

    template<typename T>
    gp_point<T> operator-(const gp_point<T> &Right);

    template<typename T>
    gp_point<T> &operator+=(gp_point<T> &Left, const gp_point<T> &Right);

    template<typename T>
    gp_point<T> &operator-=(gp_point<T> &Left, const gp_point<T> &Right);

    template<typename T>
    gp_point<T> operator+(const gp_point<T> &Left, const gp_point<T> &Right);

    template<typename T>
    gp_point<T> operator-(const gp_point<T> &Left, const gp_point<T> &Right);

    template<typename T>
    gp_point<T> operator*(const gp_point<T> &Left, T Right);

    template<typename T>
    gp_point<T> operator*(T Left, const gp_point<T> &Right);

    template<typename T>
    gp_point<T> &operator*=(gp_point<T> &Left, T Right);

    template<typename T>
    gp_point<T> operator/(const gp_point<T> &Left, T Right);

    template<typename T>
    gp_point<T> &operator/=(gp_point<T> &Left, T Right);

    template<typename T>
    bool operator==(const gp_point<T> &Left, const gp_point<T> &Right);

    template<typename T>
    bool operator!=(const gp_point<T> &Left, const gp_point<T> &Right);


    template<typename T>
    inline gp_point<T>::gp_point() : m_X(0), m_Y(0)
    {

    }

    template<typename T>
    inline gp_point<T>::gp_point(T X, T Y) : m_X(X), m_Y(Y)
    {

    }

    template<typename T>
    template<typename U>
    inline gp_point<T>::gp_point(const gp_point<U> &Point) : m_X(static_cast<T>(Point.m_X)),
                                                             m_Y(static_cast<T>(Point.m_Y))
    {
    }

    template<typename T>
    inline gp_point<T> operator-(const gp_point<T> &Right)
    {
        return gp_point<T>(-Right.m_X, -Right.m_Y);
    }

    template<typename T>
    inline gp_point<T> &operator+=(gp_point<T> &Left, const gp_point<T> &Right)
    {
        Left.m_X += Right.m_X;
        Left.m_Y += Right.m_Y;

        return Left;
    }

    template<typename T>
    inline gp_point<T> &operator-=(gp_point<T> &Left, const gp_point<T> &Right)
    {
        Left.m_X -= Right.m_X;
        Left.m_Y -= Right.m_Y;

        return Left;
    }

    template<typename T>
    inline gp_point<T> operator+(const gp_point<T> &Left, const gp_point<T> &Right)
    {
        return gp_point<T>(Left.m_X + Right.m_X, Left.m_Y + Right.m_Y);
    }


    template<typename T>
    inline gp_point<T> operator-(const gp_point<T> &Left, const gp_point<T> &Right)
    {
        return gp_point<T>(Left.m_X - Right.m_X, Left.m_Y - Right.m_Y);
    }

    template<typename T>
    inline gp_point<T> operator*(const gp_point<T> &Left, T Right)
    {
        return gp_point<T>(Left.m_X * Right, Left.m_Y * Right);
    }

    template<typename T>
    inline gp_point<T> operator*(T Left, const gp_point<T> &Right)
    {
        return gp_point<T>(Right.m_X * Left, Right.m_Y * Left);
    }

    template<typename T>
    inline gp_point<T> &operator*=(gp_point<T> &Left, T Right)
    {
        Left.m_X *= Right;
        Left.m_Y *= Right;

        return Left;
    }

    template<typename T>
    inline gp_point<T> operator/(const gp_point<T> &Left, T Right)
    {
        return gp_point<T>(Left.m_X / Right, Left.m_Y / Right);
    }

    template<typename T>
    inline gp_point<T> &operator/=(gp_point<T> &Left, T Right)
    {
        Left.m_X /= Right;
        Left.m_Y /= Right;

        return Left;
    }

    template<typename T>
    inline bool operator==(const gp_point<T> &Left, const gp_point<T> &Right)
    {
        return (Left.m_X == Right.m_X) && (Left.m_Y == Right.m_Y);
    }

    template<typename T>
    inline bool operator!=(const gp_point<T> &Left, const gp_point<T> &Right)
    {
        return (Left.m_X != Right.m_X) || (Left.m_Y != Right.m_Y);
    }

    typedef gp_point<int> IntPoint;
    typedef gp_point<unsigned int> UIntPoint;
    typedef gp_point<float> FloatPoint;

} // namespace gp

#endif //OPERATOR_FORWARDING_GP_POINT_H
