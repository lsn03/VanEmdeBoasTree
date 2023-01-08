
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
	int cntStart = 1,cntEnd = 3;
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

