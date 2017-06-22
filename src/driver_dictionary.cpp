/**
 * @file driver_dictionary.cpp
 * @authors Gabriel Araújo de Souza
 * @date 22 Junho 2017
 * @brief File for DAL and DSAL classes tests .
 */

#include <iostream>
#include <cassert>
#include "dictionary.h"

/**
 * @brief      Class for my key comparator.
 */
class MyKeyComparator 
{
	
public:
	bool operator ()( const int & lhs, const int & rhs ) const
	{
		return lhs < rhs ;
	}

};

int main ()
{
	/* all keys are diferents */
	{
		DAL<int, std::string, MyKeyComparator> test;
		assert( test.capacity() == 50 );

		DAL<int, std::string, MyKeyComparator> test2(100);
		assert( test2.capacity() == 100 );

		DAL<int, std::string, MyKeyComparator> one(1);
		assert( one.capacity() == 1 );

		//<! testing the insert
		assert(test.insert( 2015003129 , "Jack" ));
		assert(test.insert ( 2014065190 , "John" ));

		//<! testing operator <<
		std::cout << test;

		//<! testing insert in full list
		assert( one.insert( 2014065190 , "John" ) );
		assert( one.insert( 2015003129, "Jack" ) == false );

		//<! testing the search
		std::string nome;
		//<! search in the start
		assert( test.search( 2015003129, nome));
		assert( nome == "Jack" );

		//<! search in the end
		assert( test.search( 2014065190, nome));
		assert( nome == "John" );

		//<! testing search in empty list
		assert ( test2.search(2014065190, nome) == false );

		//<! testing search for an element non-existing
		assert( test.search( 122, nome) == false);

		//<! more inserts
		assert(test.insert( 2017000111, "Joseph"));
		assert(test.insert( 2016042088, "Gabriel"));
		assert(test.insert( 2005119812, "Suplente"));

		//<! testing the min
		assert( test.min() == 2005119812 );
		//<! test2.min(); std::out_of_range
		
		//<! testing the max
		assert( test.max() == 2017000111 );
		//<! test2.max(); std::out_of_range
		
		//<! testing the remove
		//<! remove in the middle
		assert( test.remove( 2017000111, nome ));
		assert( nome == "Joseph");
		assert( test.search( 2017000111, nome ) == false );

		//<! remove in the start
		assert( test.remove( 2015003129, nome ));
		assert( nome == "Jack");
		assert( test.search( 2015003129, nome ) == false );

		//<! remove in the end
		assert( test.remove( 2005119812, nome ));
		assert( nome == "Suplente");
		assert( test.search( 2005119812, nome ) == false );

		//<! testing remove in empty list
		assert( test2.remove(2014065190, nome ) == false );

		//<! testing remove for an element non-existing
		assert( test.remove( 12, nome) == false );

		//<! testing remove for the last element in a full list 
		DAL<int, std::string, MyKeyComparator> two(2);
		assert(two.insert( 2017000111, "Joseph"));
		assert(two.insert( 2016042088, "Gabriel"));
		assert(two.remove( 2016042088, nome));
		assert( nome == "Gabriel");		

		//<! testing sucessor.
		assert( test.insert( 2016042090, "Gustavo"));
		assert( test.insert( 2016042100, "Maria"));
		assert( test.insert( 2016042101, "Joao"));

		//<! successor in the middle.
		int succ;
		assert( test.sucessor(2016042088, succ));
		assert( succ == 2016042090 );

		//<! The smallest's successor
		auto aux = test.min();
		assert( test.sucessor(aux, succ) );
		assert( succ == 2016042088 );

		//<! The Largest's successor
		aux = test.max();
		assert( test.sucessor(aux, succ) == false );

		//<! Successor in empty list
		assert( test2.sucessor(aux, succ) == false );

		//<! Successor in list with single element
		assert( one.sucessor(2014065190, succ) == false );

		//<! The successor to a non-existing key
		assert( test.sucessor( 12, succ ) == false );

		std::cout << "Testar o predecessor: \n";
		std::cout <<test;

		// //<! testing predecessor
		int pred;
		assert( test.predecessor(2016042088, pred));
		assert( pred == 2014065190 );

		//<! The smallest's predecessor
		auto aux2 = test.min();
		assert( test.predecessor(aux2, pred) == false);
		
		// //<! The Largest's predecessor
		aux2 = test.max();
		assert( test.predecessor(aux2, pred));
		assert( pred == 2016042100 );

		// //<! Predecessor in empty list
		assert( test2.predecessor(aux2, pred) == false );

		//<! Predecessor in list with single element
		assert( one.predecessor(2014065190, pred) == false );

		// //<! The predecessor to a non-existing key
		assert( test.sucessor( 12,  pred) == false );
	}

	//<! Testes DSLA
	{
		DSAL<int, std::string, MyKeyComparator> test;
		// assert( test.capacity() == 50 );

		DSAL<int, std::string, MyKeyComparator> test2(100);
		// assert( test2.capacity() == 100 );

		DSAL<int, std::string, MyKeyComparator> one(1);
		// assert( one.capacity() == 1 );

		//<! testing the insert
		assert(test.insert( 2015003129 , "Jack" ));
		assert(test.insert ( 2014065190 , "John" ));

		//<! testing operator <<
		std::cout << "TEST\n";
		std::cout << test;

		//<! testing insert in full list
		assert( one.insert( 2014065190 , "John" ) );
		std::cout << one;
		assert( one.insert( 2015003129, "Jack" ) == false );
		std::cout << one;

		//<! testing the search
		std::string nome;
		//<! search in the end
		assert( test.search( 2015003129, nome));
		assert( nome == "Jack" );

		//<! search in the start
		assert( test.search( 2014065190, nome));
		assert( nome == "John" );

		//<! testing search in empty list
		assert ( test2.search(2014065190, nome) == false );

		//<! testing search for an element non-existing
		assert( test.search( 122, nome) == false);

		//<! more inserts
		assert(test.insert( 2017000111, "Joseph"));
		assert(test.insert( 2016042088, "Gabriel"));
		assert(test.insert( 2005119812, "Suplente"));

		//<! testing the min
		assert( test.min() == 2005119812 );
		//<! test2.min(); std::out_of_range
		
		//<! testing the max
		assert( test.max() == 2017000111 );
		//<! test2.max(); std::out_of_range
		
		//<! search in the end
		assert( test.search( 2017000111, nome ));
		assert( nome == "Joseph" );

		std::cout << ">>DSLA	<<\n";
		
		//<! testing the remove
		//<! remove in the end
		assert( test.remove( 2017000111, nome ));
		assert( nome == "Joseph");
		assert( test.search( 2017000111, nome ) == false );

		//<! remove in the middle
		assert( test.remove( 2015003129, nome ));
		assert( nome == "Jack");
		assert( test.search( 2015003129, nome ) == false );

		//<! remove in the start
		assert( test.remove( 2005119812, nome ));
		assert( nome == "Suplente");
		assert( test.search( 2005119812, nome ) == false );

		//<! testing remove in empty list
		assert( test2.remove(2014065190, nome ) == false );

		//<! testing remove for an element non-existing
		assert( test.remove( 12, nome) == false );

		//<! testing remove for the last element in a full list 
		DSAL<int, std::string, MyKeyComparator> two(2);
		assert(two.insert( 2017000111, "Joseph"));
		std::cout << "inseriu no two\n";
		assert(two.insert( 2016042088, "Gabriel"));
		assert(two.remove( 2016042088, nome));
		assert( nome == "Gabriel");		

		//<! testing sucessor.
		assert( test.insert( 2016042090, "Gustavo"));
		assert( test.insert( 2016042100, "Maria"));
		assert( test.insert( 2016042101, "Joao"));
;
		//<! successor in the middle.
		int succ;
		assert( test.sucessor(2016042088, succ));
		assert( succ == 2016042090 );

		//<! The smallest's successor
		auto aux = test.min();
		assert( test.sucessor(aux, succ) );
		assert( succ == 2016042088 );

		//<! The Largest's successor
		aux = test.max();	
		assert( test.sucessor(aux, succ) == false );

		//<! Successor in empty list
		assert( test2.sucessor(aux, succ) == false );

		//<! Successor in list with single element
		assert( one.sucessor(2014065190, succ) == false );

		//<! The successor to a non-existing key
		assert( test2.sucessor( 12, succ ) == false );

		// //<! testing predecessor
		int pred;
		assert( test.predecessor(2016042088, pred));
		assert( pred == 2014065190 );

		//<! The smallest's predecessor
		auto aux2 = test.min();
		assert( test.predecessor(aux2, pred) == false);
		
		//<! The Largest's predecessor
		aux2 = test.max();
		assert( test.predecessor(aux2, pred));
		assert( pred == 2016042100 );

		// //<! Predecessor in empty list
		assert( test2.predecessor(aux2, pred) == false );

		//<! Predecessor in list with single element
		assert( one.predecessor(2014065190, pred) == false );

		// //<! The predecessor to a non-existing key
		assert( test.sucessor( 12, pred ) == false );
	}
	
	std::cout << "\n>>> Passou em todos os teste\n";
	return 0;
}