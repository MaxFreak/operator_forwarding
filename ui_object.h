//
// Created by Bernd Lappas on 22.11.15.
//

#ifndef OPERATOR_FORWARDING_OBJECT_H
#define OPERATOR_FORWARDING_OBJECT_H

#include <iostream>
#include <vector>
#include <cassert>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <ostream>

using std::ostream;
using std::move;
using std::make_shared;
using std::shared_ptr;

template<typename T> void print_to(const T &x, ostream &out, size_t position);
template<typename T> void draw(const T &x, ostream &out, size_t position);

class ui_object
{
public:
    template<typename T>
    ui_object(T x) : m_Self(make_shared<model < T>>(move(x))), tag(boost::uuids::random_generator()())
    { }

    friend void print_to(const ui_object &x, ostream &out, size_t position)
    {
        x.m_Self->internal_print_to(out, position);
        out << ": " << to_string(x.GetTag()) << "\n";
    }

    friend void draw(const ui_object &x, ostream &out, size_t position)
    {
        x.m_Self->internal_draw(out, position);
    }

    const boost::uuids::uuid &GetTag() const
    {
        return tag;
    }

private:
    struct object_concept
    {
        virtual ~object_concept() = default;

        virtual void internal_print_to(ostream &, size_t) const = 0;
        virtual void internal_draw(ostream &, size_t) const = 0;
    };

    template<typename T>
    struct model : object_concept
    {
        model(T x) : m_Data(move(x)) { }

        void internal_print_to(ostream &out, size_t position) const
        {
            print_to(m_Data, out, position);
        }

        void internal_draw(ostream &out, size_t position) const
        {
            draw(m_Data, out, position);
        }

        T m_Data;
    };

    shared_ptr<const object_concept> m_Self;
    boost::uuids::uuid tag;
};

#endif //OPERATOR_FORWARDING_OBJECT_H
