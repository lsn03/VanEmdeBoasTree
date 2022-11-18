
#include <iostream>
#include <vector>
#include <fstream>
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
        if ( _minValue == x && _maxValue != 0 || _maxValue == x ) return true;
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
        if ( !Find( x ) ) return;
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
    int Next(ULL x)
    {

        /*if ( x <= _minValue )
        {
            return _minValue;
        }
        if ( Empty() || x >= _maxValue )
        {
            return _none;
        }
        if ( _k == 1 )
        {
            return _maxValue == x ? x : _none;
        }
        ULL x_High = High( x );
        ULL x_Low = Low( x );

        if ( children[x_High] != NULL && x_Low <= children[x_High]->_maxValue )
        {
            return Merge( x_High, children[x_High]->Next( x_Low ) );
        }
        else if ( aux != NULL )
        {
            ULL nextHigh = aux->Next( x_High + 1 );
            if ( nextHigh != _none )
            {
                return Merge( nextHigh, children[nextHigh]->_minValue );
            }
        }
        return _none;*/
        /*
        if ( Empty() || x >= _maxValue )
        {
            return _none;
        }
        if ( x < _minValue )
        {
            return _minValue;
        }
        if ( x == _minValue )
        {
            if ( aux->Empty() )
            {
                return _maxValue;
            }
            return Merge( aux->_minValue, children[aux->_minValue]->_maxValue );
        }
        int a = children[High( x )]->Next( Low( x ) );
        if ( a != _none )
        {
            return Merge( High( x ), a );
        }
        int b = aux->Next( High( x ) );
        if ( b == _none )
        {
            return _maxValue;
        }
        return Merge( b, children[b]->_minValue );
        */
        /*
        if ( Empty() || x >= _maxValue )
        {
            return _none;
        }
        if ( x < _minValue )
        {
            return _minValue;

        }
        if ( aux->Empty() )
        {
            return _maxValue;
        }
        if ( !(children[High( x )]->Empty()) && Low( x ) < children[High( x )]->_maxValue )
        {
            return Merge( High( x ), children[High( x )]->Next( Low( x ) ) );
        }
        else
        {
            int next_high = aux->Next( High( x ) );
            if ( next_high != _none )
                return Merge( next_high, children[next_high]->_minValue );
            else
            {
                return _maxValue;
            }
           // return _none;
        }*/

        /*if ( Empty() || x > _maxValue )
        {
            return _none;
        }
        if ( x <= _minValue )
        {
            return _minValue;

        }
        if ( _k == 1 )
        {
            if ( _maxValue == x )
            {
                return _maxValue;
            }
            else
            {
                return _none;
            }
        }
        if ( !(children[High( x )]->Empty()) && Low( x ) <= children[High( x )]->_maxValue)
        {
            return Merge( High( x ), children[High( x )]->Next( Low( x ) ));
        }
        else
        {
            int next_high = aux->Next( High( x ) + 1 );
            if ( next_high != _none )
                return Merge( next_high, children[next_high]->_minValue );
            return _none;
        }*/


    }
    int Prev()
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
    void Swap( ULL& a, ULL& b )
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
    ifstream fin( "1.in" );
    fin.close();

    VEBTree T( 4 );
    T.Insert( 0 );
    T.Insert( 1 );
    T.Insert( 2 );
    T.Insert( 3 );
    T.Insert( 5 );
    T.Insert( 14 );
    T.Insert( 15 );

   
   /* VEBTree T2( 4 );
    T2.Insert( 15 );
    T2.Insert( 14 );
    T2.Insert( 5 );
    T2.Insert( 3 );
    T2.Insert( 2 );
    T2.Insert( 1 );
    T2.Insert( 0 );


    T2.Remove( 15 );
    T2.Remove( 14 );
    T2.Remove( 5 );
    T2.Remove( 3 );
    T2.Remove( 2 );
    T2.Remove( 1 );
    T2.Remove( 0 );
    T2;
    T;*/
   /* T.Remove( 0 );
    bool f = T.Find( 0 );
    T.Remove( 1 );
    bool f1 = T.Find( 1);
    */

   /* T.Remove( 0 );
    T.Find( 0 );
    T.Remove( 1 );
    T.Find( 1 );
    T.Remove( 2 );
    T.Find( 2 );
    T.Remove( 3 );
    T.Find( 3 );
    T.Remove( 5 );
    T.Find( 5 );

    T.Remove( 14 );
    T.Find( 14 );
    T.Remove( 15 );
    T.Find( 15 );*/
   
   // bool b = T.Find( 1 );
    vector <bool> v;
    for ( int i = 0; i < 16; i++ )
    {
        T.Remove( i );
        cout  << "\t"<<T.Find(i) << endl;
      /*  T2.Remove( i );
        v.push_back( T2.Find(i) );*/
    }

}

