#ifndef LISTKEYVAL_HPP
#define LISTKEYVAL_HPP

#include "KeyVal.hpp"
#include <iostream>

/*********************************************************************
 * This is an example header without any implementation that you
 * may find useful in your effort to create an associative array.
 *
 * You are not required to conform to this header in any way, you are
 * only required to conform to the overall interface header provided
 * in KeyVal.hpp.
 *
 * However, there are helpful hints contained here that may make both
 * this PEX and future PEXes which build on the base interface easier
 * for you to implement.  A careful study of this architecture is 
 * highly recommended. *
 ********************************************************************/

//forward declaration
template<class K, class V>
class ListKeyVal;

/**
 * @class ListKeyValNode
 *
 * The purpose of this class is to store key value pairs in a sorted list.
 * Note that all methods and members are private and only accessible by the
 * friend class ListKeyVal.
 *
 * The reason that the ListKeyValNode class and the ListKeyVal class are 
 * separate is to make usage cleaner.  We must be able to create ListKeyVal 
 * objects on the stack just as we would any other object.  Since additions and
 * deletions to the list may change the root node, it is not effective to 
 * create a root node as the base object
 *
 * This separate private class also allows us to remove some default constuctors
 * and use only deep copy assignment in this class while exposing all options
 * in the public class.
 */
template<class K, class V>
class ListKeyValNode : public std::enable_shared_from_this<ListKeyValNode<K, V> >
{
friend class ListKeyVal<K, V>;
private:
  /**
   * @brief Default Constructor 
   */
  ListKeyValNode() = default;
  /**
   * @brief Remove the copy constructor
   */
  ListKeyValNode(const ListKeyValNode &other) = delete;
  /**
   * @brief provide an assignment operator which deep copies our
   * data structure
   *
   * @param other Ref to RHS object; deep copy this structure
   * @return ListKeyNodeVal ref for chaining assignments
   */
  ListKeyValNode &operator=(const ListKeyValNode &other)
  {
	m_prev.reset();
	if (other.m_key == nullptr)
	{
		m_key = nullptr;
		m_val = nullptr;
		m_next = nullptr;
		//m_prev = nullptr;
	}
	else 
	{
		m_key.reset(new K(*(other.m_key)));
		m_val.reset(new V(*(other.m_val)));

		m_next.reset(new ListKeyValNode<K,V>());
		*m_next = *(other.m_next);
		m_next->m_prev = this->shared_from_this();
	}
  }  	
  /** @brief Ptr to key; may be null for last item in list */
  std::shared_ptr<K> m_key;
  /** @brief Ptr to value; may be null for last item in list */
  std::shared_ptr<V> m_val;
  /** @brief Ptr to next node in list; may be null for last item in list */
  std::shared_ptr<ListKeyValNode> m_next;
  /** @brief Weak ptr to prev node in list; may be null for first item in list 
       note that weak ref is used to avoid mem leak islands*/
  std::weak_ptr<ListKeyValNode<K, V> > m_prev; 
};

/**
 * @class ListKeyVal
 */
template<class K, class V>
class ListKeyVal : public KeyVal<K, V>
{
public:
  /**
   * @brief Constructor
   * 
   * This ctor creates a valid root node
   */
  ListKeyVal()
  {
	m_rootNode.reset (new ListKeyValNode<K, V>());
  }


  /**
   * @brief Copy ctor
   *
   * Creates a deep copy of entire data structure
   *
   * @param other Data structure to copy
   */
  ListKeyVal(const ListKeyVal &other)
  {
	m_rootNode.reset (new ListKeyValNode<K, V>());
	*this = other;
  }
  /**
   * @brief Assignment operator
   *
   * Creates a deep copy of entire data structure
   *
   * @param other Data structure to copy
   * @return ref to populated object for assignment chaining
   */
  ListKeyVal &operator=(const ListKeyVal &other)
  {
	*(this->m_rootNode) = *(other.m_rootNode);
  }
  /**
   * @brief Insert an object
   *
   * This will place a COPY of the val object
   * into the associative array
   *
   * Note that since an insert may change the root node, I have 
   * created an "internal" function that returns the new root.
   * this function will call the internal version and then reset
   * the root node if needed.  This model will make follow on
   * PEXs where recursion is required more clean/understandable.
   *
   * @param key Key associated with value
   * @param val Value which is stored at location key
   */
  virtual void insert(const K &key,
                      const V &val) override 
  {
	m_rootNode = insertInternal(key,val); 
  }
  /**
   * @brief Remove an object from the associative array
   *
   * This will remove the key/value pair from the array
   * If the key is not found, no action is taken
   *
   * Note that since a delete may change the root node, I have 
   * created an "internal" function that returns the new root.
   * this function will call the internal version and then reset
   * the root node if needed.  This model will make follow on
   * PEXs where recursion is required more clean/understandable.
   *
   * @param key Key for which key/val pair is removed
   */
  virtual void del(const K &key) override
  {
	m_rootNode = delInternal(key);
  }
  /**
   * @brief Get a pointer to value
   *
   * Given a key, a shared_ptr to a value is returned.
   * note that if the key did not exist, then the returned
   * ptr is not valid
   *
   * @param key Key for which value is returned
   * @return ptr to value if key existed
   */
  virtual std::shared_ptr<V> get(const K &key) override
  {
	std::shared_ptr<ListKeyValNode<K,V>> tempNode = m_rootNode;
	while (tempNode->m_key != nullptr && key >= *(tempNode->m_key))
	{
		if (key == *(tempNode->m_key))
		{
			return tempNode->m_val; 
		}
		else 
		{
			tempNode = tempNode->m_next;
		}
	}
	return nullptr; //m_rootNode->m_val;
  }
  /**
   * @brief Execute callback for each entry
   *
   * Rather than force students to create an inner iterator class,
   * this functiona allows a callback function to be executed for
   * every item in the associative array.  Note that callbacks should
   * be called in order of keys sorted least to greatest
   *
   * @param callback Function to be called with each item in the associative array
   */
  virtual void forEach(std::function<void(const K &key, V &val)> callback) override
  {
	std::shared_ptr<ListKeyValNode<K,V>> tempNode = m_rootNode;
	while (tempNode->m_next != nullptr)
	{
		//tempNode = tempNode->m_next;
		callback (*(tempNode->m_key),*(tempNode->m_val));
		tempNode = tempNode->m_next;
	}
  }
private:
  /**
   * @brief Insert a node and return new root
   *
   >* @param key Key to insert
   * @param val Value associated with key
   * @return New root of node list
   */
  std::shared_ptr<ListKeyValNode <K, V> > insertInternal(const K &key,
                                                         const V &val)
  {	
	auto thingToInsert = std::shared_ptr<ListKeyValNode<K, V>>(new ListKeyValNode<K, V>()); //new node
	thingToInsert->m_key.reset(new K(key));
        thingToInsert->m_val.reset(new V(val));
	thingToInsert->m_next.reset(new ListKeyValNode<K,V>());
	thingToInsert->m_next->m_prev = thingToInsert;

	std::shared_ptr<ListKeyValNode<K,V>> tempNode = m_rootNode; 
	
	if (m_rootNode->m_key == nullptr) //root is null, new root
	{
		//m_rootNode = thingToInsert;
		return thingToInsert;
	}
	else if (key < *(m_rootNode->m_key)) //key less than root, new root
	{
		thingToInsert->m_next = m_rootNode;
		m_rootNode->m_prev = thingToInsert;
		return thingToInsert;
	}
	else 
	{
		while (tempNode->m_key != nullptr && key > *(tempNode->m_key))
		{
			tempNode = tempNode->m_next;
		}
	}

	if (tempNode->m_key == nullptr) //end of list
	{
		std::shared_ptr<ListKeyValNode<K,V>> end = tempNode->m_prev.lock();
		end->m_next = thingToInsert;
		thingToInsert->m_prev = end;
//		tempNode = thingToInsert;
	}
	else if (*(tempNode->m_key) == key) // == key
	{
		*(tempNode->m_val) = val;
	}
	else 
	{
		thingToInsert->m_next = tempNode;
		thingToInsert->m_prev = tempNode->m_prev;
		auto end = tempNode->m_prev.lock();
		end->m_next = thingToInsert;
		tempNode->m_prev = thingToInsert;
//		tempNode->m_next = thingToInsert;
	}


	return m_rootNode;



  }
 
  /**
   * @brief Delete a node and return new root
   *
   * @param key Key to insert
   * @return New root of node list
   */
  std::shared_ptr<ListKeyValNode <K, V> > delInternal(const K &key)
  {
	std::shared_ptr<ListKeyValNode<K,V>> tempNode = m_rootNode;

	if (m_rootNode->m_key != nullptr && key == *(m_rootNode->m_key))
	{
		m_rootNode->m_next->m_prev.reset();
		return m_rootNode->m_next;
	}

	while (tempNode->m_key != nullptr && key >= *(tempNode->m_key))
	{
		if (key == *(tempNode->m_key))
		{
			tempNode->m_next->m_prev = tempNode->m_prev;
			tempNode->m_prev.lock()->m_next = tempNode->m_next;
			return m_rootNode;
		}
		else 
		{
			tempNode = tempNode->m_next;
		}
	}
	return m_rootNode;
  }
  /** @breif Track root node */
  std::shared_ptr<ListKeyValNode<K, V> > m_rootNode;
};

#endif /* LISTKEYVAL */
