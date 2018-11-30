#pragma once

#include "KeyVal.hpp"
#include <iostream>

template<class K, class V>
class BSTKeyVal;

template <class K, class V>
class BSTKeyValNode
{
friend class BSTKeyVal<K,V>;
private: 
	BSTKeyValNode() = default;
	BSTKeyValNode(const BSTKeyValNode &other) = delete;

	BSTKeyValNode &operator=(const BSTKeyValNode &other)
	{
		m_key = other.m_key;
		m_val = other.m_val;
		
		if (m_left == nullptr)
		{
			m_left = nullptr;
		}
		else 
		{
			m_left.reset(new BSTKeyValNode<K,V>());
			*m_left = *(other.m_left);
		}
	
		if (m_right == nullptr)
		{
			m_right = nullptr;
		}
		else 
		{
			m_right.reset(new BSTKeyValNode<K,V>());
			*m_right = *(other.m_left);
		}
	}
	
	std::shared_ptr<K> m_key;
	std::shared_ptr<V> m_val;
	std::shared_ptr<BSTKeyValNode<K,V>> m_left;
	std::shared_ptr<BSTKeyValNode<K,V>> m_right;
	std::weak_ptr<BSTKeyValNode<K,V>> m_prev;
};

template<class K, class V>
class BSTKeyVal : public KeyVal<K,V>
{
	public:
		BSTKeyVal()
		{
			m_rootNode.reset(new BSTKeyValNode<K, V>());
		}
		BSTKeyVal &operator=(const BSTKeyVal &other)
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
			std::shared_ptr<V> ValVar;
			ValVar.reset(new V);
			ValVar = getInternal(key,m_rootNode);
			return ValVar;
		}
		virtual void forEach(std::function<void(const K &key, V &val)> callback) override //TODO L/P 
		{
			forEachInternal(callback, m_rootNode);
		}
	private:
		
	//Helpers
	
	std::shared_ptr<V> getInternal (const K &key, std::shared_ptr<BSTKeyValNode<K,V>> &parent)
	{
		std::shared_ptr<V> ValVar;
		ValVar.reset(new V);
		if (key == *(parent->m_key))
			return parent->m_val;
		else if (key < *(parent->m_key))
			ValVar = getInternal (key, parent->m_left);
		else 
			ValVar = getInternal (key, parent->m_right);
	}

	void forEachInternal (std::function<void(const K &key, V &val)> callback, std::shared_ptr<BSTKeyValNode<K,V>> &parent)
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


	void insertInternal(const K &key, const V &val,std::shared_ptr<BSTKeyValNode<K,V>> &parent)
	{
		auto thingToInsert = std::shared_ptr<BSTKeyValNode<K,V>>(new BSTKeyValNode<K,V>());
		thingToInsert->m_key.reset(new K(key));
		thingToInsert->m_val.reset(new V(val));
		thingToInsert->m_right.reset(new BSTKeyValNode<K,V>());
		thingToInsert->m_left.reset(new BSTKeyValNode<K,V>());
		
	
		if (m_rootNode == nullptr)
		{
			m_rootNode = thingToInsert;
		}	
		else 
		{
			if(parent->m_key == nullptr)
			{
				parent = thingToInsert;
			}
			else if (key == *(parent->m_key))
			{
				*(parent->m_val) = val;
			}
			else if (key < *(parent->m_key))
				{
				thingToInsert->m_prev = parent;
				insertInternal(key,val, parent->m_left);
				}
			else 
				{
				thingToInsert->m_prev = parent;
				insertInternal(key,val, parent->m_right);
				}
		}
	}
		
	void delInternal(const K &key, std::shared_ptr<BSTKeyValNode<K,V>> &parent)
	{
		if (parent->m_key == nullptr)
		{
			return;
		}
	
		if (key == *(parent->m_key))
		{
			std::shared_ptr<BSTKeyValNode<K,V>> succesor = parent;
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
	
	std::shared_ptr<BSTKeyValNode<K,V>> m_rootNode;

};






































