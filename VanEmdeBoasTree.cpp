
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
#define ll  long long

ll const _none = -1;
class VEBTree
{
public:
    VEBTree( int K )
    {
        _k = K;
       
        _minValue = _none;
        _maxValue = _none;
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
    bool Find(ll x )
    {
        if ( Empty() )
        {
            return false;
            
        }

        if ( x >= (1<<_k) ) return false;
        if ( _minValue == x && _maxValue != 0 || _maxValue == x ) return true;
        return children[High(x)]->Find(Low(x));
        
    }
    void Insert( ll x)
    {
        

        if ( Empty() )
        {
            _minValue = x;
            _maxValue = x;
            
        }
        else
        {
            
            if ( x < _minValue )
            {
                Swap( x, _minValue );
            }
           
            if ( _k != 1 )
            {
                if ( children[High( x )]->Empty() )
                {
                    aux->Insert( High( x ) );
                }
                    children[High( x )]->Insert( Low( x ) );
                    

            }
            if ( x > _maxValue )
            {
                _maxValue = x;
            }
            
        }
    }
    void Remove(ll x)
    {
        if ( !Find( x ) ) return;
        if ( _minValue == x && _maxValue == x )
        {
            _minValue = _none;
            _maxValue = _none;
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
    ll Next(ll x)
    {
        
        if ( _k == 1 )
        {

            if ( x == 0 && _maxValue == 1 )
            {
                return 1;
            }
            else
            {
                return _none;
            }
        }
        else if ( _minValue != _none && x < _minValue )
        {
            return _minValue;
        }
        else
        {
            ll maxlow = children[High( x )]->_maxValue;
            if ( maxlow != _none && Low( x ) < maxlow )
            {
                ll offset = children[High( x )]->Next( Low( x ) );
                return Merge( High( x ), offset );
            }
            else
            {
                int next = aux->Next( High( x ) );
                if ( next == _none )
                {
                    return _none;
                }
                else
                {
                    return Merge( next, children[next]->_minValue );
                }
            }
        }


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
    ll Prev(ll x)
    {

        if ( _k == 1 )
        {

            if ( x == 1 && _minValue == 0 )
            {
                return 0;
            }
            else
            {
                return _none;
            }
        }
        else if ( _maxValue != _none && x > _maxValue)
        {
            return _maxValue;
        }
        else
        {
            ll miHigh = children[High( x )]->_minValue;
            if ( miHigh != _none && Low( x ) > miHigh )
            {
                ll offset = children[High( x )]->Prev( Low( x ) );
                return Merge( High( x ), offset );
            }
            else
            {
                ll pred = aux->Prev( High( x ) );
                if ( pred == _none )
                {
                    if ( _minValue != _none && x > _minValue )
                        return _minValue;
                    return _none;
                }
                else
                {
                    return Merge( pred, children[pred]->_maxValue );
                }
            }
        }
    }
    ll GetMin()
    {
        return _minValue;
    }
    ll GetMax()
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
    ll Low( ll key )
    {
        return (key & ((1 << (_k / 2)) - 1));
    }
    ll High(ll key)
    {
        return (key >> (_k / 2));
    }
    ll Merge(ll high,ll low)
    {
        return (high << (_k / 2) )+low;
    }
    void Swap( ll& a, ll& b )
    {
        ll temp = a;
        a = b;
        b = temp;
    }
    int _k;
    ll _minValue, _maxValue;
    VEBTree* aux;
    vector<VEBTree*> children;
};


void StartTest()
{
    int k;
    int cnt;

    int cntTest;
    int _cntTest = 0;
    string command;
    ll value;
    bool flag = false;
    int commonTests = 2;
    for ( int i = 1; i <= commonTests; i++ )
    {
        ifstream fin( to_string(i)+".in" );
        ofstream fout( to_string( i ) + ".out" );

        fin >> k >> cnt;
        VEBTree T( k );
        for ( int i = 0; i < cnt; i++ )
        {
            fin >> value;
            T.Insert( value );
        }

        fin >> cntTest;

        for ( int i = 0; i < cntTest; i++ )
        {
            fin >> command >> value;
            if ( command == "del" )
            {
                T.Remove( value );
            }
            else if ( command == "find" )
            {
                _cntTest++;
                fout << bool( T.Find( value ) ) << endl;

            }
            else if ( command == "next" )
            {
                _cntTest++;
                fout << T.Next( value ) << endl;
            }
            else if ( command == "prev" )
            {
                _cntTest++;
                fout << T.Prev( value ) << endl;
            }
        }
        fin.close();
        fout.close();

        ifstream fin1( to_string( i ) + ".out" );
        ifstream finans( to_string( i ) + ".ans" );
        string res;
        string currentRes;


        for ( int i = 0; i < _cntTest; i++ )
        {
            fin1 >> res;
            finans >> currentRes;

            if ( res == currentRes )
            {
                flag = true;
            }
            else
            {
                flag = false;
                break;
            }

        }
        if ( flag )
        {
            cout << "Test # " << i << " OK" << endl;
        }
        else
        {
            cout << "Test # " << i << " WA" << endl;
        }
        fin1.close();
        finans.close();
        T.~VEBTree();
    }
    

}
int main()
{

    StartTest();
    /*
4
7

0 1 2 3 5 14 15

3
del 5
find 5
next 5

    */
    

   //7 4       0 1 2 3 5 14 15
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
    //vector <bool> v;
    for ( int i = 0; i <16; i++ )
    {
        //cout << i << '\t' << T.Find( i ) << endl;

        /*T.Remove( i );
        cout << i  << "\t"<<T.Find(i) << endl;*/
         //cout << i << "\t" << T.Next( i ) << endl;
       // cout << i << "\t" << T.Prev( i ) << endl;
    }
    
}

