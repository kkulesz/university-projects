#include <utility>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdexcept>

template<typename KeyType, typename ValueType>
class Heap4
{
  public:
    using KeyValueType = std::pair< KeyType, ValueType>;

	bool empty() const noexcept
	{
		return array.size() == 0;
		//std::terminate();
	}

	void insert(KeyType const & key, ValueType const & value)
	{
		KeyValueType new_pair = KeyValueType(key,value);
		insert(new_pair);
	}


	void insert(KeyValueType const & key_value)
	{
		if(empty()){
			array.push_back(key_value);
			return;
		}
		
		array.push_back(key_value);
		int current_index = array.size()-1;
		int parent_index = getParentIndex(current_index);
		while( array[parent_index].first > array[current_index].first ){
			std::swap( array[parent_index],array[current_index]);
			current_index = parent_index;
			if( parent_index != 0){
				parent_index = getParentIndex(current_index);
			}
			//if(parent_index<0) break;
		}

	}

	KeyValueType const & peek() const
	{
		if( !empty() ){
			return array[0];
		}else
		{
			
			throw std::logic_error("tak");
		}
		
	}

	KeyValueType pop()
	{
		if( empty() ){
			throw;
		}


		KeyValueType result = array[0];
		std::swap(array[0],array[array.size()-1]);
		array.pop_back();

		int current = 0;
		while (true)
		{
			int min = getMin(current);
			if(min == current){
				break;
			}else{
				std::swap(array[current],array[min]);
				current = min;
			}

		}
		
	}

	size_t size() const noexcept
	{
		return array.size();
	}

	template<typename StreamType>
	void print(StreamType& stream) //const
	{
		std::stringstream ss;
		getPrintSs(ss);
		stream<<ss.str();
	}


private:
	std::vector<KeyValueType> array;

	void getPrintSs(std::stringstream& ss){

		int spaceAmount=0;
		ss<<array[0].first<<":"<<array[0].second<<std::endl;

		for(int i=0; i<4; ++i){
			recursiveAdd(ss, getChildIndex(0,i), spaceAmount+1);			
		}
		
	}

	void recursiveAdd(std::stringstream& ss, int index, int spaceAmount){
;
		for (size_t i = 0; i < spaceAmount; i++)
		{
			ss<<"\t";
		}
		ss<<array[index].first<<":"<<array[index].second<<std::endl;

		for(int i=0; i<4; ++i){
			if(getChildIndex(index,i )==-1) return;

			recursiveAdd(ss, getChildIndex(index,i), spaceAmount+1);			
		}
	}

	int getMin(int current){
		int min = current;
		
		int child;
		for(int i=0; i<4; ++i){
			if((child = getChildIndex(current,i)) == -1 ){
				return min;
			}
			if( array[child].first < array[min].first ){
				min = child;
			}
		}

		return min;
	}

	int getParentIndex(int current){
		if( current == 0){
			throw;
		}
		return (current-1)/4;
	}
	int getChildIndex(int parent,unsigned int whichChild){
		if( whichChild > 3 ){
			throw;
		}
		
		int result = (parent)*4 + whichChild +1;
		if (result >= array.size()){
			return -1; // not in range
		}
		return result;
	}


};
