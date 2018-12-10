#pragma once

#include "KeyVal.hpp"
#include <iostream>
#include <list>

enum color
{
	red = 0,
	black = 1
};

/*
 red 
 black
color::red
color::black
*/

template<class K, class V>
class RBTKeyVal;

template <class K, class V>
class RBTKeyValNode : public std::enable_shared_from_this<RBTKeyValNode<K,V>>
{
friend class RBTKeyVal<K,V>;
private: 
	RBTKeyValNode() = default;
	RBTKeyValNode(const RBTKeyValNode &other) = delete;

	RBTKeyValNode &operator=(const RBTKeyValNode &other)
	{

	

		m_prev.reset();
		if (other.m_key == nullptr)
		{
			m_right = nullptr;
			m_left = nullptr;
			m_key = nullptr;
			m_val = nullptr;
		}
		else 
		{
		m_key.reset(new K(*(other.m_key)));
                m_val.reset(new V(*(other.m_val)));

		m_right.reset(new RBTKeyValNode<K,V>());
                *m_right = *(other.m_right);	

		m_left.reset(new RBTKeyValNode<K,V>());
                *m_left = *(other.m_left);

		m_left->m_prev = this->shared_from_this();
		m_right->m_prev = this->shared_from_this();
		
		}
	}
	
	color m_color; 
	std::shared_ptr<K> m_key;
	std::shared_ptr<V> m_val;
	std::shared_ptr<RBTKeyValNode<K,V>> m_left;
	std::shared_ptr<RBTKeyValNode<K,V>> m_right;
	std::weak_ptr<RBTKeyValNode<K,V>> m_prev;
};

template<class K, class V>
class RBTKeyVal : public KeyVal<K,V>
{
	public:
		RBTKeyVal()
		{
			m_rootNode.reset(new RBTKeyValNode<K, V>());
		}

		RBTKeyVal(const RBTKeyVal &other)
		{
			m_rootNode.reset(new RBTKeyValNode<K, V>());
			*this = other;
		}
		RBTKeyVal &operator=(const RBTKeyVal &other)
		{
			*(this->m_rootNode) = *(other.m_rootNode);
		}

		virtual void insert (const K &key, const V &val) override
		{
			insertInternal(key,val,m_rootNode);
		}
		virtual void del (const K &key) override
		{
			delInternal(key, m_rootNode);
		}
		virtual std::shared_ptr<V> get(const K &key) override //TODO write helper func
		{
			return getInternal(key,m_rootNode);
		}
		virtual void forEach(std::function<void(const K &key, V &val)> callback) override //TODO L/P 
		{
			forEachInternal(callback, m_rootNode);
		}
		
	/*
 	* Nates Code		
 	*/

	//get red code
	bool getColor(std::shared_ptr<RBTKeyValNode<K,V>> current)
	{
		if (current->m_color == red)
			return true;
		else 
			return false;
	}
	
	void printTree()
	{
		//create some working variables on stack
		//and initially populate
	
		std::list<std::shared_ptr<RBTKeyValNode<K,V>>> workList;
		std::list<int> levelList;
		workList.push_back(m_rootNode);
		levelList.push_back(0);
	
		//while more nodes exist for BFS
		while(!workList.empty())
		{
			//determine information for current vertex
			auto pCurrent = workList.front();
			auto level = levelList.front();
			auto pParent = getParent(pCurrent); //PARENT FUNCTION
			auto color = (getColor(pCurrent)) ? "RED" : "BLACK";//NEEDS IS RED

			//remove current vertex from working lists
			workList.pop_front();
			levelList.pop_front();

			//print the node
			std::cout << "{k:" << *(pCurrent->m_key) << ", "; //KEY
			std::cout << "C:" << color << ", ";		//COLOR
			std::cout << "L:" << level << ", ";		//LEVEL
			if(pParent)
				std::cout << "PK:" << *(pParent->m_key) << "}";
			else 
				std::cout << "PK:NULL}";

			//add left child to work list if valid 
			if (pCurrent->m_left->m_key)
			{
				workList.push_back(pCurrent->m_left);
				levelList.push_back(level + 1);
			}
			//add right child to work list if valid 
			if (pCurrent->m_right->m_key)
			{
				workList.push_back(pCurrent->m_right);
				levelList.push_back(level + 1);
			}

			//print new line when level changes
			if(!levelList.empty() && (level != levelList.front()))
				std::cout << std::endl;
		}		
		//new line at end of traversal
		std::cout << std::endl;
	}	
		
	private:
		
	//Helpers
	
	std::shared_ptr<V> getInternal (const K &key, std::shared_ptr<RBTKeyValNode<K,V>> &parent)
	{
		if (parent->m_key == nullptr)
			return nullptr;
		if (key == *(parent->m_key))
			return parent->m_val;
		else if (key < *(parent->m_key))
			return getInternal(key, parent->m_left);
		else 
			return getInternal(key, parent->m_right);
	}

	void forEachInternal (std::function<void(const K &key, V &val)> callback, std::shared_ptr<RBTKeyValNode<K,V>> &parent)
	{
		//return in sorterd order
		if (parent->m_key !=nullptr)
		{
			forEachInternal(callback, parent->m_left);
			callback(*(parent->m_key),*(parent->m_val));
			forEachInternal(callback, parent->m_right);
		}
		else 
			return;
			
	}


	void insertInternal(const K &key, const V &val,std::shared_ptr<RBTKeyValNode<K,V>> &current)
	{
		auto thingToInsert = std::shared_ptr<RBTKeyValNode<K,V>>(new RBTKeyValNode<K,V>());
		thingToInsert->m_key.reset(new K(key));
		thingToInsert->m_val.reset(new V(val));
		thingToInsert->m_right.reset(new RBTKeyValNode<K,V>());
			thingToInsert->m_right->m_color = black;//null black
		thingToInsert->m_left.reset(new RBTKeyValNode<K,V>());
			thingToInsert->m_left->m_color = black;//null black
		thingToInsert->m_color = red;

		//std::shared_ptr<BSTKeyValNode<K,V>> parent;
		//std::shared_ptr<BSTKeyValNode<K,V>> grandParent;

		//parent = getParent(current);
		//grandParent = getGrandParent(current);
		
	
		if (m_rootNode == nullptr)
		{
			m_rootNode = thingToInsert;
			m_rootNode->m_left->m_prev = m_rootNode;
			m_rootNode->m_right->m_prev = m_rootNode;
			//m_rootNode->m_color = black;
		}	
		else 
		{
			if(current->m_key == nullptr)
			{	
				current = thingToInsert;
				recolor(current);
				//current->m_left->m_prev = current;
				//current->m_right->m_prev = current;
				
			}
			if (key == *(current->m_key))
			{
				*(current->m_val) = val;
			}
			else if (key < *(current->m_key))
				{
				current->m_left->m_prev = current;
                                current->m_right->m_prev = current;
				insertInternal(key,val, current->m_left);
				}
			else if (key > *(current->m_key)) 
				{
				current->m_left->m_prev = current;
                                current->m_right->m_prev = current;
				insertInternal(key,val, current->m_right);
				}
			else 
			{
				current = thingToInsert;
				recolor(current);
			}
		}
		
		//recolor(current);
		
		
	}

	std::shared_ptr<RBTKeyValNode<K,V>> getParent(std::shared_ptr<RBTKeyValNode<K,V>> &current)
	{//parent
			return current->m_prev.lock();
		
	}

	std::shared_ptr<RBTKeyValNode<K,V>> getGrandParent(std::shared_ptr<RBTKeyValNode<K,V>> &current)
	{//grandParent
		std::shared_ptr<RBTKeyValNode<K,V>> parent;
		parent = getParent(current);
		
		if (parent == nullptr)
			return nullptr;
		else 
			return getParent(parent);
	} 
	
	std::shared_ptr<RBTKeyValNode<K,V>> getSibling(std::shared_ptr<RBTKeyValNode<K,V>> &current)
	{//sibling
		std::shared_ptr<RBTKeyValNode<K,V>> parent;
		parent = getParent(current);
		if (parent != nullptr && current != nullptr)
		{
			if (*(current->m_key) > *(parent->m_key))
			{
				return parent->m_left;
			}
			else 
				return parent->m_right;
		}
		else 
			return nullptr;
	}
	
	std::shared_ptr<RBTKeyValNode<K,V>> getUncle(std::shared_ptr<RBTKeyValNode<K,V>> &current)
	{//uncle
		std::shared_ptr<RBTKeyValNode<K,V>> parent;
		parent = getParent(current);
		if(parent == nullptr)
			return nullptr;
		else 
			return getSibling(parent);
	
		
	}

	void rotateRight(std::shared_ptr<RBTKeyValNode<K,V>> current)
	{
		std::shared_ptr<RBTKeyValNode<K,V>> parent;
		parent = getParent(current);
		
		parent->m_left = current->m_right;
		current->m_right = parent;
		parent->m_prev = current;
		

		if(*(parent->m_key) == *(m_rootNode->m_key))
			m_rootNode = current;	
	}
	
	void rotateLeft(std::shared_ptr<RBTKeyValNode<K,V>> current)
	{
		std::shared_ptr<RBTKeyValNode<K,V>> parent;
		parent = getParent(current);

		parent->m_right = current->m_left;
		current->m_left = parent;
		parent->m_prev = current;
		
		if(*(parent->m_key) == *(m_rootNode->m_key))
			m_rootNode = current;
	}

	void recolor(std::shared_ptr<RBTKeyValNode<K,V>> current)
	{
		std::shared_ptr<RBTKeyValNode<K,V>> parent;
		std::shared_ptr<RBTKeyValNode<K,V>> grandParent;
		std::shared_ptr<RBTKeyValNode<K,V>> sibling;
		std::shared_ptr<RBTKeyValNode<K,V>> uncle;
		//first to test / initialize helpers
		
		parent = getParent(current);
		grandParent = getGrandParent(current);
		sibling = getSibling(current);
		uncle = getUncle(current);
		
		

		if (grandParent == nullptr)
		{
			current->m_color = black;
			return;
		}	
		else if (parent->m_color == red && uncle->m_color == red)
		{
			if (parent == nullptr)
			{
				current->m_color = black;
				return;
			}
			else 
			{
				parent->m_color = black;
				uncle->m_color = black;
				grandParent->m_color = red;
				recolor(grandParent);
			}
		}
		else 
		{
			if(*(parent->m_key) > *(current->m_key) && *(current->m_key) > *(current->m_left->m_key))
			{//left left
				rotateRight(parent);
			}
			else if (*(parent->m_key) < *(current->m_key) && *(current->m_key) < *(current->m_left->m_key))
			{//right right
				rotateLeft(parent);
			}
			else if (*(parent->m_key) > *(current->m_key) && *(current->m_key) < *(current->m_left->m_key))
			{//left right
				rotateLeft(current);
				rotateRight(parent);
			}
			else 
			{//left right
				rotateRight(current);
				rotateLeft(parent);
			}
		}
		
	
	}
	
	/*
	 * Delete is from regular binary tree
 	 */
 		
	void delInternal(const K &key, std::shared_ptr<RBTKeyValNode<K,V>> &parent)
	{
		if (parent->m_key == nullptr)
		{
			return;
		}
	
		if (key == *(parent->m_key))
		{
			std::shared_ptr<RBTKeyValNode<K,V>> succesor = parent;
			if (succesor->m_right->m_key != nullptr)
			{
				succesor = succesor->m_right;
				while (succesor->m_left->m_key != nullptr)
				{
					succesor = succesor->m_left;
				}
			}
			else if (succesor->m_left->m_key != nullptr)
			{
				succesor = succesor->m_left;
				while (succesor->m_right->m_key != nullptr)
				{
					succesor = succesor->m_right;
				}
			}
			else {
				parent->m_key = nullptr;
				parent->m_key = nullptr;
				parent->m_left = nullptr;
				parent->m_right = nullptr;
				return;
			}

			parent->m_key = succesor->m_key;
			parent->m_val = succesor->m_val;
			
			delInternal(*(succesor->m_key), succesor);
			
		}
		else if (key < *(parent->m_key))
			delInternal(key, parent->m_left);
		else 
			delInternal(key, parent->m_right);
	}
	
	std::shared_ptr<RBTKeyValNode<K,V>> m_rootNode;

};






































