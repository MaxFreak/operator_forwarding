#include <iostream>
#include <vector>
#include <cassert>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

//#include <string>
//#include <ostream>
//#include <memory>


using namespace std;

using std::string;
using std::ostream;
using std::endl;
using std::move;
using std::make_shared;
using std::shared_ptr;
using std::vector;

template<typename T>
void draw(const T &x, ostream &out, size_t position)
{
    out << string(position, ' ') << x << endl;
}

class object_t
{
public:
    template<typename T>
    object_t(T x) : m_Self(make_shared<model < T>>(move(x))), tag(boost::uuids::random_generator()())
    { }

    friend void draw(const object_t &x, ostream &out, size_t position)
    {
        out << to_string(x.GetTag()) << ": ";
        x.m_Self->internal_draw(out, position);
    }

    const boost::uuids::uuid &GetTag() const
    {
        return tag;
    }

private:
    struct concept_t
    {
        virtual ~concept_t() = default;

        virtual void internal_draw(ostream &, size_t) const = 0;
    };

    template<typename T>
    struct model : concept_t
    {
        model(T x) : m_Data(move(x)) { }

        void internal_draw(ostream &out, size_t position) const
        {
            draw(m_Data, out, position);
        }

        T m_Data;
    };

    shared_ptr<const concept_t> m_Self;
    boost::uuids::uuid tag;
};

//typedef vector<object_t> DocumentVector;
//using DocumentVector = vector<string>;
using DocumentVector = vector<object_t>;

class document_t
{
public:
//    typedef DocumentVector::const_iterator const_iterator;
    using const_iterator = DocumentVector::const_iterator;

    template <class... Args>
    void emplace_back(Args&&... args)
    {
        m_Childs.emplace_back(std::forward<Args>(args)...);
    }

    template <class... Args>
    typename DocumentVector::reference
    operator[](Args&&... args)
    {
        return m_Childs.operator[](std::forward<Args>(args)...);
    }

    template <class... Args>
    typename DocumentVector::reference
    operator[](Args&&... args) const
    {
        return m_Childs.operator[](std::forward<Args>(args)...);
    }

    DocumentVector::size_type size()
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

    DocumentVector m_Childs;

    document_t() : m_Childs() {cout << "document_t(): " << std::hex << this << endl; }

    virtual ~document_t() {cout << "~document_t(): " << std::hex << this << endl;}
};

//using document_t = vector<object_t>;

void draw(const document_t &doc, ostream &out, size_t position)
{
    out << string(position, ' ') << "<document>" << endl;
    for (auto &e : doc)
    {
        out << to_string(e.GetTag()) << ": ";
        draw(e, out, position + 2);
    }
    out << string(position, ' ') << "</document>" << endl;
}

using history_t = vector<document_t>;

void commit(history_t &x)
{
    assert(x.size());
    x.push_back(x.back());
}

void undo(history_t &x)
{
    assert(x.size());
    x.pop_back();
}

document_t &current(history_t &x)
{
    assert(x.size());
    return x.back();
}

void draw(const history_t &hist, ostream &out)
{
    for (auto &e : hist)
    {
        draw(e, out, 0);
        cout << "--------------------------" << endl;
    }
}

int main()
{
    cout << "Hello, World!" << endl;

    int i = 0;
    document_t doc;

    history_t h(1);

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
