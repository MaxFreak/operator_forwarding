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
using std::cout;

template<typename T> void print_to(const T &x, ostream &out, size_t position);
template<typename T> void draw(const T &x, ostream &out, size_t position);

class ui_object
{
public:
    template<typename T>
    ui_object(T x) : m_Self(make_shared<model < T>>(move(x)))
    {
//        cout << "ui_object(): " << std::hex << this << "\n";
    }

    virtual ~ui_object()
    {
//        cout << "~ui_object(): " << std::hex << this << "\n";
    }

//    ui_object(const ui_object &obj) : m_Self(obj.m_Self)
//    {
//        cout << "ui_object() copy: " << std::hex << this << "\n";
//    }
//
//    ui_object(const ui_object &&obj) : m_Self(obj.m_Self)
//    {
//        cout << "ui_object() move: " << std::hex << this << "\n";
//    }

    friend void print_to(const ui_object &x, ostream &out, size_t position)
    {
        x.m_Self->internal_print_to(out, position);
    }

    friend void draw(const ui_object &x, ostream &out, size_t position)
    {
        x.m_Self->internal_draw(out, position);
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
        model(T x) : m_Data(move(x)), tag(boost::uuids::random_generator()())
        {
            cout << "model(): " << std::hex << this << " tag: " << tag << "\n";
        }

        virtual ~model()
        {
            cout << "~model(): " << std::hex << this << " tag: " << tag << "\n";
        }

        model(const model &obj) : m_Data(obj.m_Data), tag(obj.tag)
        {
            cout << "model() copy: " << std::hex << this << " tag: " << tag << "\n";
        }

        model(const model &&obj) : m_Data(move(obj.m_Data)), tag(obj.tag)
        {
            cout << "model() move: " << std::hex << this << " tag: " << tag << "\n";
        }

        void internal_print_to(ostream &out, size_t position) const
        {
            print_to(m_Data, out, position);
            out << " Tag: " << to_string(tag) << "\n";
        }

        void internal_draw(ostream &out, size_t position) const
        {
            draw(m_Data, out, position);
        }

        T m_Data;
        boost::uuids::uuid tag;
    };

    shared_ptr<const object_concept> m_Self;
};

#endif //OPERATOR_FORWARDING_OBJECT_H
