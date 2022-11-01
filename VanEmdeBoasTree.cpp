
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
    bool Find(ULL x )
    {
        if ( Empty() )
        {
            return false;
            
        }
        if ( (*this)._minValue == x || (*this)._maxValue == x ) return true;
        //return Find( *(this).children[High( x )], Low( x ) );
        
    }
    void Insert( ULL x)
    {
        if ( Empty() )
        {
            _minValue = _maxValue = x;
            
        }
        else
        {
            if ( _minValue == _maxValue )
            {
                _minValue = min( _minValue, x );
                _maxValue = max( _maxValue, x );
            }
            else
            {
                if ( x < _minValue )
                {
                    Swap( x, _minValue );
                }
                if ( x > _maxValue )
                {
                    Swap( x, _maxValue );
                }
                if ( _k != 2 )
                {
                    if ( children[High( x )]->Empty() )
                    {
                        aux->Insert( High( x ) );
                    }

                }
                children[High( x )]->Insert( Low( x ) );
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
    bool Empty()
    {
        if ( (*this)._minValue == _none )
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
    T.Insert( 0 );
    T.Insert( 1 );
    T.Insert( 2 );
    T.Insert( 3 );
    T.Insert( 5 );
    T.Insert( 14 );
    T.Insert( 15 );

}

