
#include <iostream>
#include <vector>
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
        if ( _k <= 2 )
        {
            aux = NULL;
            children = vector<VEBTree*>( 0 );
            
        }
        else
        {
            int size = 1 << (_k >> 1);
            children = vector<VEBTree*>( size );
            aux = new VEBTree( _k>>1 );

            for ( int i = 0; i < size; i++ )
            {
                children[i] = new VEBTree( _k >> 1 );
            }
        }
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
        return Find( *t.children[High( x )], Low( x ) );
        
    }
    void Insert(VEBTree& t, ULL x)
    {
        if ( Empty( t ) )
        {
            t._minValue = x;
            t._maxValue = x;
        }
        else
        {
            if ( t._minValue == t._maxValue )
            {
                if ( t._minValue < x )
                {
                    t._minValue = x;
                }
                else
                {
                    t._maxValue = x;
                }
            }
            else
            {
                if ( t._minValue > x )
                {
                    Swap( t._minValue, x );
                }
                if ( t._maxValue < x )
                {
                    Swap( t._maxValue, x );
                }
                if ( t._k != 1 )
                {
                    if ( Empty( *t.children[High( x )] ) )
                    {
                        Insert( *t.aux, High( x ) );
                    }
                    Insert( *t.children[High( x )], Low( x ) );
                }
            }
        }
    }
    void Remove()
    {

    }
    ULL GetMin()
    {
        return _minValue;
    }
    ULL GetMax()
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
    ULL Low( ULL key )
    {
        return (key & ((1 << (_k / 2)) - 1));
    }
    ULL High(ULL key)
    {
        return (key >> (_k / 2));
    }
    void Swap( ULL a, ULL b )
    {
        ULL temp = a;
        a = b;
        b = temp;
    }
    int _k;
    ULL _minValue, _maxValue, _none;
    VEBTree* aux;
    vector<VEBTree*> children;
};

int main()
{
    VEBTree T( 4 );
    T.Insert( T, 0 );
    T.Insert( T, 1 );
    T.Insert( T, 2 );
    T.Insert( T, 3 );
    T.Insert( T, 5 );
    T.Insert( T, 14 );
    T.Insert( T, 15);

}

