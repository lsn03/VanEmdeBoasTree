
#include <iostream>
using namespace std;
#define ULL unsigned long long

class VEBTree
{
public:
    VEBTree( int K )
    {
        _k = K;
        _none = (1 << _k);
        _minValue = _none;

        
    }
   
    ~VEBTree()
    {

    }
    bool Find(VEBTree t,ULL x )
    {
        if ( Empty(t) )
        {
            return false;
        }
        if ( t._minValue == x || t._maxValue == x ) return true;
        
    }
    void Insert()
    {

    }
    void Remove()
    {

    }
    ULL Min()
    {
        return _minValue;
    }
    ULL Max()
    {
        return _maxValue;
    }
    void Next()
    {

    }
    void Prev()
    {

    }
    bool Empty(VEBTree t)
    {
        if ( t._minValue == _none )
            return true;
        else 
            return false;
    }
private:
    ULL Low(ULL key)
    {
        return (key & (_k / 2));
    }
    ULL High(ULL key)
    {
        return (key >> (_k / 2));
    }
    int _k;
    ULL _minValue, _maxValue, _none;
    
};

int main()
{

}

