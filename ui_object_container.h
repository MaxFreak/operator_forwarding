//
// Created by Bernd Lappas on 22.11.15.
//

#ifndef OPERATOR_FORWARDING_UI_OBJECT_CONTAINER_H
#define OPERATOR_FORWARDING_UI_OBJECT_CONTAINER_H

//#include <iostream>
//#include <vector>
//#include <cassert>

//#include <boost/uuid/uuid.hpp>
//#include <boost/uuid/uuid_generators.hpp>
//#include <boost/uuid/uuid_io.hpp>

//#include <string>
#include <ostream>
//#include <memory>

#include "ui_object.h"

using std::cout;
using std::string;
using std::ostream;
using std::endl;
using std::move;
using std::make_shared;
using std::shared_ptr;
using std::vector;

//typedef vector<ui_object> used_container;
//using used_container = vector<string>;
using used_container = vector<ui_object>;

class ui_object_container
{
public:
//    typedef used_container::const_iterator const_iterator;
    using const_iterator = used_container::const_iterator;

    template <class... Args>
    void emplace_back(Args&&... args)
    {
        m_Childs.emplace_back(std::forward<Args>(args)...);
    }

    template <class... Args>
    typename used_container::reference
    operator[](Args&&... args)
    {
        return m_Childs.operator[](std::forward<Args>(args)...);
    }

    template <class... Args>
    typename used_container::reference
    operator[](Args&&... args) const
    {
        return m_Childs.operator[](std::forward<Args>(args)...);
    }

    used_container::size_type size()
    {
        return m_Childs.size();
    }

    const_iterator begin() const
    {
        return m_Childs.begin();
    }

    const_iterator end() const
    {
        return m_Childs.end();
    }
public:

    used_container m_Childs;

    ui_object_container() : m_Childs() { cout << "ui_object_container(): " << std::hex << this << "\n"; }

    virtual ~ui_object_container() { cout << "ui_documentt(): " << std::hex << this << "\n";}
};

void draw(const ui_object_container &doc, ostream &out, size_t position)
{
    out << string(position, ' ') << "<document>\n";
    for (auto &e : doc)
    {
        out << to_string(e.GetTag()) << ": ";
        draw(e, out, position + 2);
    }
    out << string(position, ' ') << "</document>\n";
}

#endif //OPERATOR_FORWARDING_UI_OBJECT_CONTAINER_H
