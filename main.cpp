#include "ui_object.h"
#include "ui_object_container.h"
#include "ui_history.h"

template<typename T>
void draw(const T &x, ostream &out, size_t position)
{
    out << string(position, ' ') << x << "\n";
}

// class ui_object

// class ui_object_container

// class ui_history


// http://florianjw.de/en/variadic_templates.html

template<typename Fun, typename...Ts>
void sequential_foreach(Fun f, const Ts &... args)
{
    (void) std::initializer_list<int>{(f(args), 0)...};
}

template<typename...Ts>
void print_all(std::ostream &stream, const Ts &... args)
{
    sequential_foreach([&](const auto &arg) { stream << arg; }, args...);
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
    boost::uuids::uuid ot = current(h).m_Childs[0].GetTag();

    commit(h);

    current(h).emplace_back(current(h));

    commit(h);
    current(h).emplace_back(current(h));

    draw(h, cout);

    return 0;
}
