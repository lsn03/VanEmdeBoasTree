
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
#define ll  long long

ll const _none = -1;
int const TIME_LIMIT = 100000;
class VEBTree
{
public:
	VEBTree( ll U )
	{
		_u = U;
	   
		_minValue = _none;
		_maxValue = _none;
		if ( _u <= 2 )
		{
			aux = NULL;
			children = vector<VEBTree*>( 0 );
			
		}
		else
		{
			int size = ceil( sqrt( _u ) );
			children = vector<VEBTree*>( size );
			aux = new VEBTree( size );

			for ( int i = 0; i < size; i++ )
			{
				children[i] = new VEBTree( size );
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

		if ( x >= _u ) return false;
		if ( _minValue == x || _maxValue == x ) return true;
		return children[High(x)]->Find(Low(x));
		
	}
	void Insert( ll x )
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

			if ( _u > 2 )
			{
				if ( children[High( x )]->Empty() )
				{
					aux->Insert( High( x ) );
					children[High( x )]->_minValue = Low( x );
					children[High( x )]->_maxValue = Low( x );
				}
				else
				{
					children[High( x )]->Insert( Low( x ) );
				}



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
	ll Next( ll x )
	{

		if ( _u == 2 )
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
			ll maxHigh = children[High( x )]->_maxValue;
			if ( maxHigh != _none && Low( x ) < maxHigh )
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


	}
	ll Prev(ll x)
	{

		if ( _u == 2 )
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
		ll mod = ceil( sqrt( _u ) );
		return key % mod;
		
	}
	ll High(ll key)
	{
		ll div = ceil( sqrt( _u ) );
		return key / div;
	
	}
	ll Merge(ll high,ll low)
	{
		ll ru = ceil( sqrt( _u ) );
		return high * ru + low;
		
	}
	void Swap( ll& a, ll& b )
	{
		ll temp = a;
		a = b;
		b = temp;
	}
	ll _u;
	ll _minValue, _maxValue;
	VEBTree* aux;
	vector<VEBTree*> children;
};


void StartTest( int startCnt, int endCnt )
{
	int k;
	int cnt;

	int cntTest;
	int _cntTest = 0;
	string command;
	ll value;
	bool flag = false;
	unsigned long long timeFor = 0;
	int startTime;
	int endTime;
	int delta = 0;
	

	bool n = false;
	for ( int i = startCnt; i <= endCnt; i++ )
	{
		int maxdelta = -1;
		flag = false;
		ifstream fin( to_string(i)+".in" );
		ofstream fout( to_string( i ) + ".out" );
		ofstream ftime( to_string( i ) + ".time" );
		
		fin >> k >> cnt;
		VEBTree T( k );
		ftime << "cnt: " << "\t" << k<<endl;
		for ( int j = 0; j < cnt; j++ )
		{
			fin >> value;
			startTime = clock();
			T.Insert( value );
			endTime = clock();
			delta = endTime - startTime;
			maxdelta = max( delta, maxdelta );
			if ( delta >= TIME_LIMIT )
			{
				flag = true;
				cout << i << " Time Limit: " << delta << " ms" << endl;
				break;
			}
		}
		
		flag = false;

		fin >> cntTest;
		
		
		for ( int j = 0; j < cntTest; j++ )
		{
			
			auto start = std::chrono::steady_clock::now();
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
			else if ( command == "ins" )
			{
				
				T.Insert( value );
				
			}
			else if ( command == "gmin" )
			{
				_cntTest++;
				fout << T.GetMin() << endl;
			}
			else if ( command == "gmax" )
			{
				_cntTest++;
				fout << T.GetMax() << endl;
			}
			
			auto end = std::chrono::steady_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			
			
			ftime << command << "\t"<< elapsed.count()<<"\t" << value << endl;
			delta = elapsed.count();
			//cout << j << " time: " << delta << endl;
			/*if ( command == "ins"  )
			{
				timeFor += delta;
				
			}
			else
			{
				if ( !n )
				{
					n = true;
					ofstream ftime( to_string( i ) + ".time" );
					ftime << "insert: \n cnt: " << j << "\n time: " << timeFor;
					cout  << "insert: \n cnt: " << j << "\n time: " << timeFor <<endl;
					ftime.close();
				}
				
			}*/
			
			maxdelta = max( delta, maxdelta );
			if ( delta >= TIME_LIMIT )
			{
				flag = true;
				cout << "Time Limit on: "<< command  << " value: "<< value << endl;
				//break;
			}
		}
		
		if ( flag )
		{
			cout << i << " Time Limit: " << delta << " microsecond" << endl;
			//break;
		}
		fin.close();
		fout.close();

		ifstream fin1( to_string( i ) + ".out" );
		ifstream finans( to_string( i ) + ".ans" );
		string res;
		string currentRes;


		for ( int j = 0; j < _cntTest; j++ )
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
			cout << i << " OK \t MaxTimeExe: " << maxdelta <<  endl;
		}
		else
		{
			cout <<  i << " WA \t MaxTimeExe:"<< maxdelta << endl;
		}
		
		fin1.close();
		finans.close();
		T.~VEBTree();
	}
	

}
int main()
{
	int cntStart = 1,cntEnd = 9;
	StartTest( cntStart, cntEnd );
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
	//for ( int i = 0; i <16; i++ )
	{
		//cout << i << '\t' << T.Find( i ) << endl;

		/*T.Remove( i );
		cout << i  << "\t"<<T.Find(i) << endl;*/
		 //cout << i << "\t" << T.Next( i ) << endl;
	   // cout << i << "\t" << T.Prev( i ) << endl;
	}
	
}

