
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "VEB.h";
using namespace std;
#define ll  long long
int const TIME_LIMIT = 100000;

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
		ifstream fin("tests/"+ to_string(i) + ".in");
		ofstream fout( "tests/" + to_string( i ) + ".out" );
		ofstream ftime( "tests/" + to_string( i ) + ".time" );
		
		fin >> k >> cnt;
		VEBTree T( k );
		ftime << "max_cnt: " << "\t" << k<<endl;
		for ( int j = 0; j < cnt; j++ )
		{
			fin >> value;
			T.Insert( value );
		}
		
		flag = false;

		fin >> cntTest;
		
		
		for ( int j = 0; j < cntTest; j++ )
		{


			fin >> command >> value;
			auto start = std::chrono::steady_clock::now();
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


			ftime << command << "\t" << elapsed.count() << "\t" << value << endl;
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
				cout << "Time Limit on: " << command << " value: " << value << endl;
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

		ifstream fin1( "tests/" + to_string( i ) + ".out" );
		ifstream finans( "tests/" + to_string( i ) + ".ans" );
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
void Foo()
{
	
}
void WriteTest()
{
	ll u[7] = { 2097152,4194304,8388608,16777216,33554432,67108864,1048576 };
	for ( int i = 13; i <= 19; i++ )
	{
		ll currentU = u[i % 7];

		ofstream fin( "tests/" + to_string( i ) + ".in" );
		ofstream fans( "tests/" + to_string( i ) + ".ans" );
		fin << currentU << "\n" << currentU << "\n";
		for ( int i = 0; i < currentU; i++ )
		{
			fin << i << endl;
		}
		fin << currentU << "\n";
		fans << currentU << endl;
		for ( int i = 0; i < currentU; i++ )
		{
			fin << "next " << i << endl;
			if (i!=currentU-1 )
				fans << i + 1 << endl ;
			else if(i==currentU+1){
				fans << -1;
			}
		}
		
		fans.close();
		fin.close();
	}
	for ( int i = 27; i <= 33; i++ )
	{
		ll currentU = u[i % 7];
		
		ofstream fin( "tests/" + to_string( i ) + ".in" );
		ofstream fans( "tests/" + to_string( i ) + ".ans" );
		fin << currentU<<"\n"<<0<<"\n";
		//for ( int i = 0; i < currentU; i++ )
		{
			//fin << i << endl;
		}
		fin << currentU << "\n";
		for ( int i = 0; i < currentU; i++ )
		{
			fin << "ins " << i << endl;
		}
		fans << 1;
		fans.close();
		fin.close();
	}
	for ( int i =34; i <= 40; i++ )
	{
		ll currentU = u[i % 7];

		ofstream fin( "tests/" + to_string( i ) + ".in" );
		ofstream fans( "tests/" + to_string( i ) + ".ans" );
		fin << currentU << "\n" << currentU << "\n";
		for ( int i = 0; i < currentU; i++ )
		{
			fin << i << endl;
		}
		fin << currentU << "\n";
		for ( int i = 0; i < currentU; i++ )
		{
			fin << "del " << i << endl;
		}
		fans << 1;
		fans.close();
		fin.close();
	}
	for ( int i = 41; i <= 47; i++ )
	{
		ll currentU = u[i % 7];

		ofstream fin( "tests/" + to_string( i ) + ".in" );
		ofstream fans( "tests/" + to_string( i ) + ".ans" );
		fin << currentU << "\n" << currentU << "\n";
		for ( int i = 0; i < currentU; i++ )
		{
			fin << i << endl;
		}
		fin << currentU << "\n";
		fans << currentU << endl;
		for ( int i = currentU-1; i >= 0; i-- )
		{
			fin << "prev " << i << endl;

			if ( i != currentU - 1 )
				fans << i - 1 << endl;
			else if ( i == 0 )
			{
				fans << -1;
			}
		}
		
		fans.close();
		fin.close();
	}
}
/*
20 - 20
21 - 21
22 - 23
23 - 23
24 - 24
25 - 25
26 - 26

27 - 20
28 - 21
29 - 22
30 - 23
31 - 24
32 - 25
33 - 26

34 - 20
35 - 21
36 - 22
37 - 23
38 - 24
39 - 25
40 - 26
*/

void InsertMethod( vector<ll> v ) {}
void RemoveMethod( vector<ll> v ) {}
void FindMethod( VEBTree& T, vector<ll> v, int i )
{
	ifstream finans( "tests/" + to_string( i ) + ".ans" );
	ofstream ftime( "tests/" + to_string( i ) + ".time" );
	ofstream fout( "tests/" + to_string( i ) + ".out" );

	string res;
	string currentRes;
	finans >> res;


	auto start = std::chrono::steady_clock::now();

	for ( int i = 0; i < v.size(); i++ )
	{
		fout << T.Find( v[i] ) << endl;
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	
	fout.close();
	bool flag = false;
	ifstream foutCheck( "tests/" + to_string( i ) + ".out" );
	for ( int i = 0; i < v.size(); i++ )
	{
		foutCheck >> currentRes;
		if ( currentRes == res )
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
		cout << i << " OK \t Perfomance" << endl;
	}
	else
	{
		cout << i << " WA \t Perfomance" << endl;
	}

	ftime << "find of" << "\t"<< v.size() << "\n time:\t" << elapsed.count() << endl;

}
void NextMethod( vector<ll> v ) {}
void PrevMethod( vector<ll> v ) {}

void LogicTest()
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
	for ( int i = 1; i < 12; i++ )
	{
		int maxdelta = -1;
		flag = false;
		ifstream fin( "tests/" + to_string( i ) + ".in" );
		ofstream fout( "tests/" + to_string( i ) + ".out" );
		ofstream ftime( "tests/" + to_string( i ) + ".time" );

		fin >> k >> cnt;
		VEBTree T( k );
		ftime << "max_cnt: " << "\t" << k << endl;
		for ( int j = 0; j < cnt; j++ )
		{
			fin >> value;
			T.Insert( value );
		}

		flag = false;

		fin >> cntTest;


		for ( int j = 0; j < cntTest; j++ )
		{


			fin >> command >> value;
			auto start = std::chrono::steady_clock::now();
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


			ftime << command << "\t" << elapsed.count() << "\t" << value << endl;
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
				cout << "Time Limit on: " << command << " value: " << value << endl;
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

		ifstream fin1( "tests/" + to_string( i ) + ".out" );
		ifstream finans( "tests/" + to_string( i ) + ".ans" );
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
			cout << i << " OK \t MaxTimeExe: " << maxdelta << endl;
		}
		else
		{
			cout << i << " WA \t MaxTimeExe:" << maxdelta << endl;
		}

		fin1.close();
		finans.close();
		T.~VEBTree();
	}

	
}
void PerfomanceTest()
{
	int universarySize;
	int countOfDigitsToFillTree;

	int cntTest;
	int _cntTest = 0;
	string command;
	ll value;
	bool flag = false;
	unsigned long long timeFor = 0;
	int startTime;
	int endTime;
	int delta = 0;

	vector <ll > v;
	for ( int i = 20; i <=26; i++ )
	{
		int maxdelta = -1;
		flag = false;
		ifstream fin( "tests/" + to_string( i ) + ".in" );
		
		

		fin >> universarySize >> countOfDigitsToFillTree;
		VEBTree T( universarySize );
		
		for ( int j = 0; j < countOfDigitsToFillTree; j++ )
		{
			fin >> value;
			T.Insert( value );
		}

		fin >> cntTest;
		
		v.resize( cntTest );

		fin >> command >> value;
		
		string method = command;
		
		v[0] = value;
		for ( int j = 1; j < cntTest; j++ )
		{
			fin >> command >> value;
			v[j] =  value;
		}
		if ( method == "ins" )
		{
			InsertMethod( v );
		}
		else if ( method == "del" )
		{
			RemoveMethod( v );
		}
		else if ( method == "find" )
		{
			FindMethod(T, v,i );
		}
		else if ( method == "next" )
		{
			NextMethod( v );
		}
		else if ( method == "prev" )
		{
			PrevMethod( v );
		}
		v.clear();
		v.resize( 0 );
		T.~VEBTree();
	}
}

int main()
{
	string digits = "0123456789";
	string temp = "123456789";
	int lenght = 500;
	srand( time(0) );
	string ans = to_string( temp[rand() % temp.size()] );
	for ( int i = 0; i < lenght; i++ )
	{
		ans += digits[rand() % digits.size()];
	}
	cout << ans;
	
	//WriteTest();
	//VEBTree T( 67108864 );
	//PerfomanceTest();
	//int cntStart = 20,cntEnd = 20;
	//StartTest( cntStart, cntEnd );
	
}

