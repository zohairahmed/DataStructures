/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{

    elems++;
    if (shouldResize())
      resizeTable();

    unsigned listNum = hashes::hash(key, size);
    table[listNum].push_front(std::pair<K, V>(key, value));
    /**
     * @todo Implement this function.
     *
     */
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    if (!keyExists(key))
      return;
    unsigned listIdx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it = table[listIdx].begin();
    while (it != table[listIdx].end()){
      if (it->first == key){
        elems--;
        table[listIdx].erase(it);
        break;
      }

      ++it;
    }

    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    if (!keyExists(key))
      return V();
    unsigned listIdx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it = table[listIdx].begin();
    while (it != table[listIdx].end()){
      if (it->first == key)
        return it->second;
      ++it;
    }

    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename std::list<std::pair<K, V>>::iterator it;
    size_t oldSize = size;
    size = findPrime(size * 2);
    std::list<std::pair<K, V>>* newTab = new std::list<std::pair<K, V>>[size];
    for (unsigned i = 0; i < oldSize; i++){
      it = table[i].begin();
      while (it != table[i].end()){
        unsigned newIdx = hashes::hash(it->first, size);
        std::pair<K,V>a(it->first, it->second);
        newTab[newIdx].push_front(a);
        ++it;
      }
    }
    delete[] table;
    table = newTab;
}
