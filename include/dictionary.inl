#include "dictionary.h"

template <typename Key, typename Data, typename KeyComparator>
int DAL<Key, Data, KeyComparator>::_search ( const Key & _x ) const 
{
	//<! Comparison function
	KeyComparator comp;
	Key master;

	for ( auto i(0); i < m_length; ++i)
	{
		master = m_data[i].id;
		//<! if master is not smaller and _x is not smaller, so
		//   master = _x;
		if ( !comp(master, _x) and !comp(_x, master)  )
			return i;
	}

	return -1;
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::remove ( const Key & _x, Data & _s )
{
	//<! can not remove nothink of an empty list
	if ( m_length == 0 )
		return false;

	//<! seach the position element
	auto pos = _search( _x );

	//<! special case, remove last element
	if ( pos == (m_length-1))
	{
		_s = m_data[pos].info;
		m_length--;
		return true;

	} else if ( pos != -1 )
	{
		_s = m_data[pos].info;
		std::copy( &m_data[pos+1], &m_data[m_length+1], &m_data[pos] );
		m_length--;

		return true;
	}else
		return false;
} 

//<! searchs an element in list
template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::search ( const Key & _x, Data & _s ) const
{
	auto pos = _search( _x );
	
	//<! check if the element exist
	if ( pos != -1 )
	{
		_s = m_data[pos].info;
		return true;
	}
	else
		return false;
}

//<! insert an new element in list
template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::insert ( const Key & _newKey , const Data & _newInfo )
{
	//<! check if has space in list 
	if ( m_length == m_capacity ) return false;

	m_data[m_length].id = _newKey;
	m_data[m_length].info = _newInfo;
	m_length++;

	return true;
}

//<! the smallest list key
template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::min ( ) const
{
	if ( m_length == 0 ) 
		throw std::out_of_range("[min()]: Cannot recover an min element from an empty list!");

	//<! Comparison function
	KeyComparator comp;
	Key min = m_data[0].id;
	Key aux;

	for ( auto i(1); i < m_length; ++i )
	{
		aux = m_data[i].id;
		if ( comp(aux, min) ) min = aux;
	}

	return min;
} 

//<! the largest list key
template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::max ( ) const
{
	if ( m_length == 0 ) 
		throw std::out_of_range("[min()]: Cannot recover an min element from an empty list!");

	//<! Comparison function
	KeyComparator comp;
	Key max = m_data[0].id;
	Key aux;

	for ( auto i(1); i < m_length; ++i )
	{
		aux = m_data[i].id;
		if ( comp(max, aux) ) max = aux;
	}

	return max;
}

//<! search successor
template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::sucessor ( const Key & _x , Key & _y ) const
{
	if ( m_length == 0 ) return false;

	//<! Comparison function
	KeyComparator comp;
	Key successor = max();
	Key aux;
	
	for ( auto i(0); i < m_length; ++i )
	{
		aux = m_data[i].id;
		if ( comp(_x, aux ) and ( comp(aux, successor) )) successor = aux; 
	}

	//<! successor == max()
	auto sucM = (!comp(successor, max()) and !comp(max(), successor));

	//<! successor == _x
	auto sucX = (!comp(successor, _x) and !comp(_x, successor));

	if ( sucM or sucX ) return false;
	else _y = successor;

	return true;	
}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::predecessor ( const Key & _x , Key & _y ) const 
{
	if ( m_length == 0 ) return false;

	//<! Comparison function
	KeyComparator comp;
	Key predecessor = min();
	Key aux;

	for ( auto i(0); i < m_length; ++i )
	{
		aux = m_data[i].id;
		if ( comp(aux, _x ) and ( comp(predecessor,aux ) )) predecessor = aux; 
	}

	//<! predecessor == min()
	auto preM = (!comp(predecessor, min()) and !comp(min(), predecessor));

	//<! predecessor == _x
	auto preX = (!comp(predecessor, _x) and !comp(_x, predecessor));

	if ( preM or preX ) return false;
	else _y = predecessor;

	return true;	
}

/***********************
 *	Methods from DSAL. *
 ***********************
 */

template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::_search ( const Key & _x ) const
{
	auto sz = DAL<Key, Data, KeyComparator>::m_length, first = 0, last = sz-1;
	KeyComparator comp;

	while ( first <= last )
	{
		int mid = (first + last)/2;
		auto at  = DAL<Key, Data, KeyComparator>::m_data[mid].id;

		if ( (!comp(_x, at)) and (!comp(at, _x)) ) return mid;
		else if ( comp(_x, at) ) last = mid-1;
		else first = mid+1;
	
	}
	
	return -1;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::remove ( const Key & _x, Data & _s )
{
	auto &length = DAL<Key, Data, KeyComparator>::m_length;
	auto &data = DAL<Key, Data, KeyComparator>::m_data;

	if ( length == 0 ) return false;

	int pos = _search( _x );

	//<! special case
	if ( pos == (length-1) )
	{
		_s = data[pos].info;
		length--;
		return true;

	}else if ( pos != -1 )
	{
		_s = data[pos].info;
		for ( auto i(pos); i < length-1; ++i )
		{
			data[i].id = data[i+1].id;
			data[i].info = data[i+1].info;
		}

		length--;	
		return true;
	}
	return false;
} 

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::insert ( const Key & _newKey , const Data & _newInfo )
{
	auto &length = DAL<Key, Data, KeyComparator>::m_length;
	auto &data = DAL<Key, Data, KeyComparator>::m_data;
	auto capacity = DAL<Key, Data, KeyComparator>::m_capacity;

	auto t = _search(_newKey);
	//<! check if has space in list or if empty list
	if ( length == capacity or t != -1) return false;

	
	KeyComparator comp;
	Key aux;
	auto possible_pos = 0;
	auto pos = -1;

	//<! finds the correct position to insert
	while ( possible_pos < length )
	{
		aux = data[possible_pos].id;
		if ( comp( aux, _newKey) ) pos = possible_pos;

		possible_pos++;
	}

	//<! check if the insertion is in the end
	if ( pos == length-1 )
	{
		data[length].id = _newKey;
		data[length].info = _newInfo;
		length++;
		return true;
	}
	else if ( pos == -1)
	{
		//<! open space
		for ( auto i(length); i > pos+1; --i)
		{
			data[i].id = data[i-1].id;
			data[i].info = data[i-1].info;
		}
		data[0].id = _newKey;
		data[0].info = _newInfo;
		length++;
		return true;
	}else
	{
		//<! open space
		for ( auto i(length); i > pos+1; --i)
		{
			data[i].id = data[i-1].id;
			data[i].info = data[i-1].info;
		}

		data[pos+1].id = _newKey;
		data[pos+1].info = _newInfo;
		length++;
		return true;
	}
	
	return false;
}

template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::min ( ) const
{
	auto &data = DAL<Key, Data, KeyComparator>::m_data;
	auto &length = DAL<Key, Data, KeyComparator>::m_length;

	if ( length == 0 ) 
		throw std::out_of_range("[min()]: Cannot recover an min element from an empty list!");

	return data[0].id;
}

template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::max ( ) const 
{
	auto &data = DAL<Key, Data, KeyComparator>::m_data;
	auto &length = DAL<Key, Data, KeyComparator>::m_length;

	if ( length == 0 ) 
		throw std::out_of_range("[max()]: Cannot recover an max element from an empty list!");

	return data[length-1].id;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::sucessor ( const Key & _x , Key & _y ) const
{
	auto &data = DAL<Key, Data, KeyComparator>::m_data;
	auto &length = DAL<Key, Data, KeyComparator>::m_length;

	auto pos = _search(_x);
	if ( length == 0 or pos == length-1) return false;

	_y = data[pos+1].id;
	return true;
}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::predecessor ( const Key & _x , Key & _y ) const
{
	auto &data = DAL<Key, Data, KeyComparator>::m_data;
	auto &length = DAL<Key, Data, KeyComparator>::m_length;

	auto pos = _search(_x);
	if ( length == 0 ) return false;

	_y = data[pos-1].id;
	return true;
}