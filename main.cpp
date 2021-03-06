#include "ui_object.h"
#include "ui_object_container.h"
#include "ui_history.h"

#include "common_helpers.h"

template<typename T>
void print_to(const T &X, ostream &Out, size_t Position)
{
    Out << string(Position, ' ') << X;
}

template<typename T>
void draw(const T &X, ostream &Out, geo::IntRect Position)
{
    Position.print_to(Out, 2);
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

void draw(const my_class_t&, std::ostream& Out, geo::IntRect Position)
{
}

int main()
{
    cout << "Hello, World!\n" ;

    print_all(cout, "Hello", " World", '!', 0 ,'\n');

    ui_history h(1);

    current(h).emplace_back("Hello");
    current(h).emplace_back("World");
    current(h).emplace_back("1");
    current(h).emplace_back("2");
    current(h).emplace_back("3");
    current(h).emplace_back("4");
    current(h).emplace_back("5");
    current(h).emplace_back("6");
    current(h).emplace_back("7");
    current(h).emplace_back("8");
    current(h).emplace_back("9");
    current(h).emplace_back("10");
    current(h).emplace_back(my_class_t());

    current(h).operator[](1).test();
    current(h)[1].test();
    ui_object uio = current(h)[1];
    uio.test();
    auto &uior = current(h)[1];
    uior.test();
??    boost::uuids::uuid ot = uior.get_tag();

//    boost::uuids::uuid ot = current(h).m_Childs[0].GetTag();

//    commit(h);
//    current(h).emplace_back(current(h));
//    commit(h);
//    current(h).emplace_back(current(h));

    print_to(h, cout);
    draw(h, cout);
    cout.flush();
    return 0;
}
