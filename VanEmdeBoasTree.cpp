﻿
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
        if ( _k <= 1 )
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

        if ( x >= _none ) return false;
        if ( _minValue == x || _maxValue == x ) return true;
        return children[High(x)]->Find(Low(x));
        
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
                if ( _k != 1 )
                {
                    if ( children[High( x )]->Empty() )
                    {
                        aux->Insert( High( x ) );
                    }
                    children[High( x )]->Insert( Low( x ) );
                }   
            }
        }
    }
    void Remove(ULL x)
    {
        if ( _minValue == x && _maxValue == x )
        {
            _minValue = _none;
            _maxValue = 0;
            return;
        }
        if ( _minValue == x )
        {
            if ( aux->Empty() )
            {
                _minValue = _maxValue;
                return;
            }
            x = Merge( aux->_minValue, children[aux->_minValue]->_minValue );
            _minValue = x;
        }
        if ( _maxValue == x )
        {
            if ( aux->Empty() )
            {
                _maxValue = _minValue;
                return;
            }
            
        }
        else
        {
            if ( aux->Empty() )
            {
                return;
            }

            x = Merge( aux->_maxValue, children[aux->_maxValue]->_maxValue );
            _maxValue = x;
        }
        
        if ( aux->Empty() )
            return;
        children[High( x )]->Remove( Low( x ) );
        if ( children[High( x )]->Empty() )
        {
            aux->Remove( High( x ) );
        }
        
    }
    void Next()
    {

    }
    void Prev()
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
    bool Empty()
    {
        if (this == NULL ||  _minValue == _none )
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
    ULL Merge(ULL high,ULL low)
    {
        return (high << (_k / 2) )+low;
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

   
   /* T.Remove( 0 );
    bool f = T.Find( 0 );
    T.Remove( 1 );
    bool f1 = T.Find( 1);*/
    
   
    bool b = T.Find( 1 );
   vector <bool> v;
    for ( int i = 0; i < 16; i++ )
    {
        T.Remove( i );
        v.push_back( T.Find(i) );
    }

}

