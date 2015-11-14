#include <iostream>
#include <vector>

using namespace std;

//typedef vector<object_t> DocumentVector;
using DocumentVector = vector<string>;

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
};

//using document_t = vector<object_t>;


int main()
{
    cout << "Hello, World!" << endl;

    document_t doc;

    doc.emplace_back("Hello");
    doc.emplace_back("World");

    int i = 0;
    for (auto &e : doc)
    {
        cout << "document: "<< e.npos << " " << e << endl;
        i++;
    }

    for (i = 0; i < doc.size(); i++)
    {
        cout << "document: "<< i << " " << doc[i] << endl;
    }

    doc[1] = "Jupiter";

    for (i = 0; i < doc.size(); i++)
    {
        cout << "document: "<< i << " " << doc[i] << endl;
    }

    return 0;
}
