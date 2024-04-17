//
//  json.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/16/24.
//

#ifndef json_hpp
#define json_hpp

#include <stack>
#include <assert.h>
#include <ostream>
#include <unordered_map>
#include "ref.hpp"
#include "file-io.hpp"

namespace kege
{
    class Json : public kege::RefCounter
    {
    public:

        class Elem : public kege::RefCounter
        {
            public: virtual ~Elem(){}

            virtual const Elem* get( const kege::string& s )const{ return nullptr; }
            virtual const Elem* at( uint32_t i )const{ return nullptr; }

            virtual const kege::string* str()const{ return nullptr; }
            virtual float    float32()const{ return 0.0f; }
            virtual double   float64()const{ return 0.0; }
            virtual uint32_t uint32()const{ return 0; }
            virtual int32_t  sint32()const{ return 0; }
            virtual void print(int gaps){}

            enum Type{ STRING, NUMBERIC, OBJECT, ARRAY };
            Json::Elem::Type type;

            Elem( Json::Elem::Type t ):type( t ){}
        };

        typedef std::pair< kege::string, kege::Ref< Json::Elem > > ElemPair;

        class Object : public Json::Elem
        {
        public:

            void insert( const kege::string& name, kege::Ref< Json::Elem > element );
            const Json::Elem* get( const kege::string& s )const;
            void print(int gaps);
            Object():Elem( OBJECT ){}
            ~Object();

        public:

            std::unordered_map< uint64_t, std::vector< uint32_t > > _lookup_table;
            std::vector< ElemPair > _elements;
        };

    public:

        const Json::Elem* operator[]( const kege::string& name )const;

        bool load( const kege::File& file );
        virtual kege::string value()const;
        void parse( const char* str );

        void print();
        Json();

    private:

        void insert( std::stack< std::pair< kege::string, Json::Elem* > >& stack, const kege::string& name, kege::Ref< Json::Elem > elem );
        void print( std::ostream& stream, const Json::Elem& json, int gaps, bool v )const;
        const char* parseNumeric( const char* str, kege::string& value );
        const char* parseWord( const char* str, kege::string& value );

        Json::Object _objects;
        char _tmp[256];
    };
}
#endif /* json_hpp */
