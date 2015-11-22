//
// Created by Bernd Lappas on 22.11.15.
//

#ifndef OPERATOR_FORWARDING_HISTORY_H
#define OPERATOR_FORWARDING_HISTORY_H

#include <iostream>
#include <vector>
#include <cassert>

#include "ui_object_container.h"

using std::ostream;
using std::vector;

using ui_history = vector<ui_object_container>;

void commit(ui_history &x)
{
    assert(x.size());
    x.push_back(x.back());
}

void undo(ui_history &x)
{
    assert(x.size());
    x.pop_back();
}

ui_object_container &current(ui_history &x)
{
    assert(x.size());
    return x.back();
}

void print_to(const ui_history &hist, ostream &out)
{
    for (auto &e : hist)
    {
        print_to(e, out, 0);
        cout << "--------------------------\n";
    }
}

#endif //OPERATOR_FORWARDING_HISTORY_H
