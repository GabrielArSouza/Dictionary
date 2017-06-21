#ifndef _DIC_H_
#define _DIC_H_

#include <stdexcept>
#include <sstream>
#include <algorithm>


template <typename Key, typename Data, typename KeyComparator >
class DAL
{

protected:
	
	struct NodeAL { //<! Estrutura do nó representando o par chave-informação .
		Key id;     //<! A chave é um inteiro simples .
		Data info;  //<! A informação é uma cadeia de caracteres .
	};

	const static int SIZE = 50; //<! Tamanho default da lista .
	int m_length;      //<! Comprimento atual da lista .
	int m_capacity;    //<! Capacidade máxima de armazenamento .
	NodeAL * m_data; 	//<! Área de armazenamento : vetor alocado dinamicamente .
	
	/**
	 * @brief      Searches for the first match.
	 *
	 * @param[in]  _x    The key
	 *
	 * @return     Table index
	 */
	int _search ( const Key & _x ) const ; //<! Método de busca auxiliar .
	
public:

	/**
	 * @brief      Basic constructor
	 *
	 * @param[in]  _MaxSz  The maximum size
	 */
	DAL ( int _MaxSz = SIZE )
		: m_length(0)
		, m_capacity( _MaxSz )
		, m_data ( new NodeAL[ _MaxSz ] )
	{ /*empty*/ }

	/**
	 * @brief      Destroys the object.
	 */
	virtual ~DAL() { delete [] m_data; };

	/**
	 * @brief      Remove an element from the list
	 *
	 * @param[in]  _x    element key
	 * @param      _s    element data that was remove
	 *
	 * @return     True if remove successfully, False otherwise
	 */
	bool remove ( const Key & _x, Data & _s ); 

	/**
	 * @brief      Searches for the first match.
	 *
	 * @param[in]  _x    element key
	 * @param      _s    element data that was found
	 *
	 * @return     True if found, False otherwise
	 */
	bool search ( const Key & _x , Data & _s ) const ; 

	/**
	 * @brief      Inserts an new element in list
	 *
	 * @param[in]  _newKey   The new key
	 * @param[in]  _newInfo  The new information
	 *
	 * @return     True if inserted, false otherwise
	 */
	bool insert ( const Key & _newKey , const Data & _newInfo );

	/**
	 * @brief      Retrieves the smallest list key
	 *
	 * @return     The smallest key or a std::out_of_range if the list is empty
	 */
	Key min ( ) const ;

	/**
	 * @brief      Retrieves the largest list key
	 *
	 * @return     The largest key or a std::out_of_range if the list is empty
	 */
	Key max ( ) const ;

	/**
	 * @brief      Get the key successor
	 *
	 * @param[in]  _x    The reference key
	 * @param      _y    where save _x's successor
	 *
	 * @return     True if successor found, False othewise.
	 */
	bool sucessor ( const Key & _x , Key & _y ) const;

	/**
	 * @brief      Get the key prodecessor
	 *
	 * @param[in]  _x    The reference key
	 * @param      _y    Where save _x's prodecessor
	 *
	 * @return     True if prodecessor found, False othewise
	 */
	bool predecessor ( const Key & _x , Key & _y ) const ;
	
	/**
	 * @brief      Sends back to the output stream an ascii representation for the list .
	 *
	 * @param      _os     The operating system
	 * @param[in]  _oList  The list
	 *
	 * @return     {Content of the list
	 */
	inline friend std::ostream & operator << ( std::ostream & _os , const DAL & _oList ) 
	{
		_os << "[ ";
		for ( int i(0); i < _oList.m_length; ++i )
			_os << "{ id: " << _oList.m_data[ i ].id << ", info: "
				<< _oList.m_data[ i ].info << " } ";
			_os << " ] " ;
	
		return _os;
	}

	/**
	 * @brief      For tests, get the max list capacity 
	 *
	 * @return     the max list capacity
	 */
	int capacity ( ) const
	{
		return m_capacity;
	}

};

template <typename Key, typename Data, typename KeyComparator >
class DSAL: public DAL<Key, Data, KeyComparator >
{

private:

	const static int SIZE = 50; //<! Tamanho default da lista .
	/**
	 * @brief      Searches for the first match.
	 *
	 * @param[in]  _x    The key
	 *
	 * @return     Table index
	 */
	int _search ( const Key & _x ) const ;


public:

	/**
	 * @brief      Basic constructor
	 *
	 * @param[in]  _MaxSz  The maximum size
	 */
	DSAL ( int _MaxSz = SIZE ) : DAL<Key, Data, KeyComparator>( _MaxSz ) { /* Empty */ };

	/**
	 * @brief      Destroys the object.
	 */
	virtual ~DSAL () { /* Empty */ };

	/**
	 * @brief      Remove an element from the list
	 *
	 * @param[in]  _x    element key
	 * @param      _s    element data that was remove
	 *
	 * @return     True if remove successfully, False otherwise
	 */
	bool remove ( const Key & _x, Data & _s ); 

	/**
	 * @brief      Inserts an new element in list
	 *
	 * @param[in]  _newKey   The new key
	 * @param[in]  _newInfo  The new information
	 *
	 * @return     True if inserted, false otherwise
	 */
	bool insert ( const Key & _newKey , const Data & _newInfo );

	/**
	 * @brief      Retrieves the smallest list key
	 *
	 * @return     The smallest key or a std::out_of_range if the list is empty
	 */
	Key min ( ) const ;

	/**
	 * @brief      Retrieves the largest list key
	 *
	 * @return     The largest key or a std::out_of_range if the list is empty
	 */
	Key max ( ) const ;

	/**
	 * @brief      Get the key successor
	 *
	 * @param[in]  _x    The reference key
	 * @param      _y    where save _x's successor
	 *
	 * @return     True if successor found, False othewise.
	 */
	bool sucessor ( const Key & _x , Key & _y ) const;

	/**
	 * @brief      Get the key prodecessor
	 *
	 * @param[in]  _x    The reference key
	 * @param      _y    Where save _x's prodecessor
	 *
	 * @return     True if prodecessor found, False othewise
	 */
	bool predecessor ( const Key & _x , Key & _y ) const ;

};

#include "dictionary.inl"

#endif