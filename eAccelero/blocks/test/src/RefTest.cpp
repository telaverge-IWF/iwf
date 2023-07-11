#include "Ref.h"
#include <list>
#include <iostream>

using namespace eAccelero;


class Obj: public RefObj<>
{
 public:
    typedef Reference<Obj> ObjRef;

    Obj(int id = 0)
        : m_objId(id)
    {
    }
    ~Obj()
    {
        std::cout << "Objref " << m_objId << " destroyed" << std::endl;
    }
    const int Val() const
    {
        return m_objId;
    }
    int Val()
    {
        return m_objId;
    }
 protected:
    int m_objId;
};

class NObj
{
 public:
    typedef SmartPtr<NObj> NObjRef;

    NObj(int id = 0)
        : m_objId(id)
    {
    }
    ~NObj()
    {
        std::cout << "NObjref " << m_objId << " destroyed" << std::endl;
    }
    const int Val() const
    {
        return m_objId;
    }
    int Val()
    {
        return m_objId;
    }
 protected:
    int m_objId;
};


typedef std::list<Obj::ObjRef> RefList;
typedef std::list<NObj::NObjRef> NRefList;

int main()
{
    {
        std::cout << "------- Reference test --------\n";
        RefList l;
        l.push_back(new Obj(1));
        l.push_back(new Obj(2));
        l.push_back(new Obj(3));

        Obj::ObjRef ref1 = l.front();

        std::cout << ref1->Val() << std::endl;
        l.pop_front();
        std::cout << "popped\n";

        ref1 = l.front();
        std::cout << ref1->Val() << std::endl;
        l.pop_front();
        std::cout << "------------------------------\n";
    }

    {
        std::cout << "------- Smartptr test --------\n";
        NRefList l;
        l.push_back(new NObj(1));
        l.push_back(new NObj(2));
        l.push_back(new NObj(3));

        NObj::NObjRef ref1 = l.front();

        std::cout << ref1->Val() << std::endl;
        l.pop_front();
        std::cout << "popped\n";

        ref1 = l.front();
        std::cout << ref1->Val() << std::endl;
        l.pop_front();
        std::cout << "------------------------------\n";
    }

    return 0;
}

