#include "ui_object.h"
#include "ui_object_container.h"
#include "ui_history.h"

#include "common_helpers.h"

template<typename T>
void print_to(const T &x, ostream &out, size_t position)
{
    out << string(position, ' ') << x;
}

template<typename T>
void draw(const T &x, ostream &out, size_t position)
{
}

// class ui_object

// class ui_object_container

// class ui_history

class my_class_t
{
/* ... */
};

void print_to(const my_class_t&, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "my_class_t";
}

void draw(const my_class_t&, std::ostream& out, size_t position)
{
}

int main()
{
    cout << "Hello, World!" << endl;

    print_all(cout, "Hello", " World", '!', 0 ,'\n');

    int i = 0;
    ui_object_container doc;

    ui_history h(1);

    current(h).emplace_back("Hello");
    current(h).emplace_back("World");
    current(h).emplace_back(my_class_t());
    boost::uuids::uuid ot = current(h).m_Childs[0].GetTag();

    commit(h);

    current(h).emplace_back(current(h));

    commit(h);
    current(h).emplace_back(current(h));

    print_to(h, cout);

    return 0;
}
