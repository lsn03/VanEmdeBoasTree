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
	VEBTree( ll U );

	~VEBTree();
	bool Find( ll x );
	void Insert( ll x );
	void Remove( ll x );
	ll Next( ll x );
	ll Prev( ll x );
	ll GetMin();
	ll GetMax();
	bool Empty();
	void Foo();
private:
	ll Low( ll key )
	{
		ll mod = ceil( sqrt( _u ) );
		return key % mod;

	}
	ll High( ll key )
	{
		ll div = ceil( sqrt( _u ) );
		return key / div;

	}
	ll Merge( ll high, ll low )
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

VEBTree::VEBTree( ll U )
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
bool VEBTree::Find( ll x )
{
	return this == NULL || _minValue == _none? 0:_minValue == x || _maxValue == x?1 : children[High( x )]->Find( Low( x ) );
	/*
	if ( Empty() )
	{
		return false;
	}
	if ( _minValue == x || _maxValue == x ) return true;
	return children[High( x )]->Find( Low( x ) );
	*/
}
void VEBTree::Insert( ll x )
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
void VEBTree::Remove( ll x ){
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
ll VEBTree::Next( ll x ){
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
ll VEBTree::Prev( ll x ){
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
	else if ( _maxValue != _none && x > _maxValue )
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
bool VEBTree::Empty()
{
	return this == NULL || _minValue == _none;
}
ll VEBTree::GetMin()
{
	return _minValue;
}
ll VEBTree::GetMax()
{
	return _maxValue;
}
VEBTree::~VEBTree()
{
	//Foo();
}
void VEBTree::Foo()
{
	if ( _u > 2 )
	{
		delete aux;
		int size = ceil( sqrt( _u ) );
		for ( int i = 0; i < size; i++ )
		{
			children.~vector();
		}
		
	}
	delete this;
}