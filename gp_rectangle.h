//
// Created by Bernd Lappas on 22.11.15.
//

#ifndef OPERATOR_FORWARDING_GP_RECTANGLE_H
#define OPERATOR_FORWARDING_GP_RECTANGLE_H

#include <algorithm>
#include "gp_point.h"

namespace gp
{
    template<typename T>
    class gp_rectangle
    {
    public:

        gp_rectangle();

        gp_rectangle(T Left, T Top, T Width, T Height);

        gp_rectangle(const gp_point<T> &Position, const gp_point<T> &Size);

        template<typename U>
        explicit gp_rectangle(const gp_rectangle<U> &Rectangle);

        bool contains(T X, T Y) const;

        bool contains(const gp_point<T> &Point) const;

        bool intersects(const gp_rectangle<T> &Rectangle) const;

        bool intersects(const gp_rectangle<T> &Rectangle, gp_rectangle<T> &Intersection) const;

        T m_Left;   /// Left coordinate of the Rectangle
        T m_Top;    /// Top coordinate of the Rectangle
        T m_Width;  /// Width of the Rectangle
        T m_Height; /// Height of the Rectangle
    };

    template<typename T>
    bool operator==(const gp_rectangle<T> &Left, const gp_rectangle<T> &Right);

    template<typename T>
    bool operator!=(const gp_rectangle<T> &Left, const gp_rectangle<T> &Right);

    template<typename T>
    gp_rectangle<T>::gp_rectangle() : m_Left(0), m_Top(0), m_Width(0), m_Height(0)
    {
    }

    template<typename T>
    gp_rectangle<T>::gp_rectangle(T Left, T Top, T Width, T Height) : m_Left(Left), m_Top(Top), m_Width(Width),
                                                                      m_Height(Height)
    {
    }

    template<typename T>
    gp_rectangle<T>::gp_rectangle(const gp_point<T> &Position, const gp_point<T> &Size) : m_Left(Position.m_X),
                                                                                          m_Top(Position.m_Y),
                                                                                          m_Width(Size.m_X),
                                                                                          m_Height(Size.m_Y)
    {
    }

    template<typename T>
    template<typename U>
    gp_rectangle<T>::gp_rectangle(const gp_rectangle<U> &Rectangle) : m_Left(static_cast<T>(Rectangle.m_Left)),
                                                                      m_Top(static_cast<T>(Rectangle.m_Top)),
                                                                      m_Width(static_cast<T>(Rectangle.m_Width)),
                                                                      m_Height(static_cast<T>(Rectangle.m_Height))
    {
    }

    template<typename T>
    bool gp_rectangle<T>::contains(T X, T Y) const
    {
        // Rectangles with negative dimensions are allowed, so we must handle them correctly

        // Compute the real min and max of the rectangle on both axes
        T minX = std::min(m_Left, static_cast<T>(m_Left + m_Width));
        T maxX = std::max(m_Left, static_cast<T>(m_Left + m_Width));
        T minY = std::min(m_Top, static_cast<T>(m_Top + m_Height));
        T maxY = std::max(m_Top, static_cast<T>(m_Top + m_Height));

        return (X >= minX) && (X < maxX) && (Y >= minY) && (Y < maxY);
    }

    template<typename T>
    bool gp_rectangle<T>::contains(const gp_point<T> &Point) const
    {
        return contains(Point.m_X, Point.m_Y);
    }

    template<typename T>
    bool gp_rectangle<T>::intersects(const gp_rectangle<T> &Rectangle) const
    {
        gp_rectangle<T> intersection;
        return intersects(Rectangle, intersection);
    }

    template<typename T>
    bool gp_rectangle<T>::intersects(const gp_rectangle<T> &Rectangle, gp_rectangle<T> &Intersection) const
    {
        // Rectangles with negative dimensions are allowed, so we must handle them correctly

        // Compute the min and max of the first rectangle on both axes
        T r1MinX = std::min(m_Left, static_cast<T>(m_Left + m_Width));
        T r1MaxX = std::max(m_Left, static_cast<T>(m_Left + m_Width));
        T r1MinY = std::min(m_Top, static_cast<T>(m_Top + m_Height));
        T r1MaxY = std::max(m_Top, static_cast<T>(m_Top + m_Height));

        // Compute the min and max of the second rectangle on both axes
        T r2MinX = std::min(Rectangle.m_Left, static_cast<T>(Rectangle.m_Left + Rectangle.m_Width));
        T r2MaxX = std::max(Rectangle.m_Left, static_cast<T>(Rectangle.m_Left + Rectangle.m_Width));
        T r2MinY = std::min(Rectangle.m_Top, static_cast<T>(Rectangle.m_Top + Rectangle.m_Height));
        T r2MaxY = std::max(Rectangle.m_Top, static_cast<T>(Rectangle.m_Top + Rectangle.m_Height));

        // Compute the intersection boundaries
        T interLeft = std::max(r1MinX, r2MinX);
        T interTop = std::max(r1MinY, r2MinY);
        T interRight = std::min(r1MaxX, r2MaxX);
        T interBottom = std::min(r1MaxY, r2MaxY);

        // If the intersection is valid (positive non zero area), then there is an intersection
        if ((interLeft < interRight) && (interTop < interBottom))
        {
            Intersection = gp_rectangle<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
            return true;
        }
        else
        {
            Intersection = gp_rectangle<T>(0, 0, 0, 0);
            return false;
        }
    }

    template<typename T>
    inline bool operator==(const gp_rectangle<T> &Left, const gp_rectangle<T> &Right)
    {
        return (Left.m_Left == Right.m_Left) && (Left.m_Width == Right.m_Width) && (Left.m_Top == Right.m_Top) &&
            (Left.m_Height == Right.m_Height);
    }

    template<typename T>
    inline bool operator!=(const gp_rectangle<T> &Left, const gp_rectangle<T> &Right)
    {
        return !(Left == Right);
    }

    typedef gp_rectangle<int> IntRect;
    typedef gp_rectangle<float> FloatRect;

} // namespace gp

#endif //OPERATOR_FORWARDING_GP_RECTANGLE_H
