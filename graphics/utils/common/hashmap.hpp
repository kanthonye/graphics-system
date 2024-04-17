//
//  hashmap.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/10/24.
//

#ifndef hashmap_hpp
#define hashmap_hpp

#include <assert.h>
#include <vector>
#include <unordered_map>
#include "kege-string.hpp"

namespace kege{

    template< typename T > class Hashmap
    {
    public:

        typedef std::pair< kege::string,T > Item;
        typedef std::vector< Item > VectorPair;
        typedef std::vector< Item >::iterator ListIterator;
        typedef std::unordered_map< kege::string, VectorPair > HashTable;
        typedef HashTable::const_iterator ConstIterator;
        typedef HashTable::iterator Iterator;

        const T& operator[](const kege::string& name)const
        {
            Iterator i = _table.find( name );
            if (i != end())
            {
                for (Item& item : i->second )
                {
                    if( (item)->first == name )
                    {
                        return (item)->second;
                    }
                }
            }
            VectorPair& v = _table[ name ];
            v.push_back({ name, {} });
            throw v[ v.size() - 1 ].second;//std::runtime_error("invalid hash map index operator []");
        }

        T& operator[](const kege::string& name)
        {
            Iterator i = _table.find( name );
            if (i != end())
            {
                for (Item& item : i->second )
                {
                    if( (item).first == name )
                    {
                        return (item).second;
                    }
                }
            }
            VectorPair& v = _table[ name ];
            v.push_back({ name, {} });
            throw v[ v.size() - 1 ].second;//throw std::runtime_error("invalid hash map index operator []");
        }

        void insert(const kege::string& name, T item)
        {
            Item i;
            i.first = name;
            i.second = item;
            _table[ name ].push_back(i);
        }

        bool contained(const kege::string& name)const
        {
            Iterator i = _table.find( name );
            if (i != end())
            {
                for (Item& item : i->second )
                {
                    if( (item)->first == name )
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        const T* at(const kege::string& name)const
        {
            ConstIterator i = _table.find( name );
            if (i != cend())
            {
                for (const Item& item : i->second )
                {
                    if( (item).first == name )
                    {
                        return &(item).second;
                    }
                }
            }
            return nullptr;
        }

        T* at(const kege::string& name)
        {
            Iterator i = _table.find( name );
            if (i != end())
            {
                for (Item& item : i->second )
                {
                    if( (item).first == name )
                    {
                        return &(item).second;
                    }
                }
            }
            return nullptr;
        }

        void remove(const kege::string& name)
        {
            Iterator i = _table.find( name );
            if (i != end())
            {
                for (typename VectorPair::iterator j = i->second.begin(); j != i->second.end(); j++ )
                {
                    if( (*j).first == name )
                    {
                        i->second.erase( j );
                        return;
                    }
                }
            }
        }

        ConstIterator cbegin()const
        {
            return _table.cbegin();
        }

        ConstIterator cend()const
        {
            return _table.cend();
        }

        Iterator begin()
        {
            return _table.begin();
        }

        Iterator end()
        {
            return _table.end();
        }

        bool empty()const
        {
            return _table.empty();
        }

        void clear()
        {
            _table.clear();
        }

    private:

        HashTable _table;
    };

}
#endif /* hashmap_hpp */
