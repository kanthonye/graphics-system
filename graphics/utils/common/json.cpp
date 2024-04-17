//
//  json.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/16/24.
//

#include "json.hpp"

namespace kege{namespace json{

    class Integer : public Json::Elem
    {
    public:

        uint32_t uint32()const{ return uint32_t(_value); }
        int32_t  sint32()const{ return int32_t(_value); }
        float  float32()const{ return _value; }
        double float64()const{ return _value; }
        void setNumber( double v ){ _value = v; }
        Integer( int32_t v ):Elem( NUMBERIC ){ _value = v; }
        Integer():Elem( NUMBERIC ){}
        void print(int gaps);
    private:

        int32_t _value;
    };
    void Integer::print(int gaps)
    {
        printf("%i,\n", _value);
    }


    class Number : public Json::Elem
    {
    public:

        uint32_t uint32()const{ return uint32_t(_value); }
        int32_t  sint32()const{ return int32_t(_value); }
        float  float32()const{ return _value; }
        double float64()const{ return _value; }
        void setNumber( double v ){ _value = v; }
        Number( double v ):Elem( NUMBERIC ){ _value = v; }
        Number():Elem( NUMBERIC ){}
        void print(int gaps);
    private:

        double _value;
    };
    void Number::print(int gaps)
    {
        printf("%f,\n", _value);
    }


    class String : public Json::Elem
    {
    public:

        virtual void setString( const kege::string& str ){ _str = str; }
        virtual const kege::string* str()const{ return &_str; }
        void print(int gaps);
        String( const kege::string& str ):Elem( STRING ), _str( str ){}
        String():Elem( STRING ){}

    private:

        kege::string _str;
    };
    void String::print(int gaps)
    {
        printf("%s,\n", _str.c_str());
    }

    struct Boolean : public Json::Elem
    {};


    class Array : public Json::Elem
    {
    public:

        void append( kege::Ref< Json::Elem > element );
        const Json::Elem* at( uint32_t i )const;
        void print(int gaps);
        Array():Elem( ARRAY ){}
        ~Array();

    public:

        std::vector< kege::Ref< Json::Elem > > _elements;
    };
    void Array::append(kege::Ref< Json::Elem > element)
    {
        _elements.push_back( element );
    }
    const Json::Elem* Array::at( uint32_t i )const
    {
        if ( i >= _elements.size() ) return nullptr;
        return _elements[ i ].ref();
    }
    void Array::print(int gaps)
    {
        printf("%*s[\n", gaps,"");
        for (int i=0; i<_elements.size(); i++)
        {
            if( _elements[ i ]->type != Json::Elem::OBJECT && _elements[ i ]->type != Json::Elem::ARRAY )
            {
                printf("%*s", gaps+2, "");
                _elements[ i ]->print(gaps + 2);
            }
            else
            {
                _elements[ i ]->print(gaps + 2);
            }
        }
        printf("%*s", gaps, "");
        printf("],\n");
    }
    Array::~Array()
    {
        _elements.clear();
    }
}}





namespace kege{

    void Json::Object::insert( const kege::string& name, kege::Ref< Json::Elem > element )
    {
        _lookup_table[ name.hash() ].push_back( uint32_t( _elements.size() ) );

        Json::ElemPair pair;
        pair.first = name;
        pair.second = element;
        _elements.push_back( pair );
    }
    const Json::Elem* Json::Object::get( const kege::string& name )const
    {
        auto m = _lookup_table.find( name.hash() );
        if ( m != _lookup_table.end() )
        {
            for (int i=0; i<m->second.size(); i++ )
            {
                if ( _elements[ m->second[ i ] ].first == name )
                {
                    return _elements[ m->second[ i ] ].second.ref();
                }
            }
        }
        return nullptr;
    }
    void Json::Object::print(int gaps)
    {
        printf("%*s{\n", gaps,"");
        for (int i=0; i<_elements.size(); i++)
        {
            printf("%*s", gaps+2, "");
            if( _elements[ i ].second->type != Json::Elem::OBJECT && _elements[ i ].second->type != Json::Elem::ARRAY )
            {
                printf("%s: ", _elements[ i ].first.c_str());
                _elements[ i ].second->print( gaps+2 );
            }
            else
            {
                printf("%s:\n",_elements[ i ].first.c_str());
                _elements[ i ].second->print( gaps+2 );
            }
        }
        printf("%*s},\n", gaps, "");
    }
    Json::Object::~Object()
    {
        _elements.clear();
    }




    const Json::Elem* Json::operator[]( const kege::string& name )const
    {
        return _objects.get( name );
    }

    bool Json::load( const kege::File& file )
    {
        if ( file )
        {
            std::vector< char > buffer( file.size() );
            file.read( buffer.data(), 1, file.size() );
            buffer[ buffer.size() - 1 ] = 0;
            parse( buffer.data() );
            return true;
        }
        return false;
    }

    void Json::insert( std::stack< std::pair< kege::string, Json::Elem* > >& stack, const kege::string& name, kege::Ref< Json::Elem > elem )
    {
        if ( !stack.empty() )
        {
            if ( stack.top().second->type == Json::Elem::OBJECT )
            {
                Json::Object* obj = (Json::Object*) stack.top().second;
                obj->insert( name, elem );
            }
            else if ( stack.top().second->type == Json::Elem::ARRAY )
            {
                json::Array* obj = (json::Array*) stack.top().second;
                obj->append( elem );
            }
        }
        else
        {
            _objects.insert( name, elem );
        }
    }

    const char* Json::parseNumeric( const char* str, kege::string& value )
    {
        str = kege::strcpy(_tmp, 256, ", \t\n", str);
        str = kege::strskp( str, "," );
        value = _tmp;
        return str;
    }

    const char* Json::parseWord( const char* str, kege::string& value )
    {
        value = "";
        str = kege::strskp( str, "\"" );
        while (*str != '\"' && *str != 0)
        {
            str = kege::strcpy(_tmp, 256, "\"", str);
            value += _tmp;
        }
        str = kege::strskp( str, "\"" );
        return str;
    }

    void Json::parse( const char* str )
    {
        typedef std::pair< kege::string, Json::Elem* > StackElem;
        std::stack< StackElem > stack;
        kege::string name;
        char tmp[256];

        Json::ElemPair pair;

        int state = *str;
        enum Mode{ ARRAY_MODE, OBJECT_MODE};
        Mode mode = OBJECT_MODE;
        while ( state != 0 )
        {
            switch ( state )
            {
                default:
                    str = kege::strskp(str, " \t\n,");
                    state = *str;
                    break;

                case '\"':
                    str = parseWord( str, name );
                    state = *str;
                    if ( mode == ARRAY_MODE && !stack.empty() )
                    {
                        if ( stack.top().second->type == Json::Elem::ARRAY )
                        {
                            if (*str >= '0' && '9' >= *str)
                            {
                                ((json::Array*) stack.top().second)->append( new json::Integer(  atoi( name.c_str() ) ) );
                            }
                            else
                            {
                                ((json::Array*) stack.top().second)->append( new json::String( name ) );
                            }
                        }
                    }
                    break;

                case ':':
                    str = kege::strskp( str, ": \t\n" );
                    if ( *str == '\"' )
                    {
                        str = kege::strskp( str, "\"" );
                        state = 30;
                    }
                    else if ( *str == '{' )
                    {
                        mode = OBJECT_MODE;
                        str = kege::strskp( str, "{" );
                        state = '{';
                    }
                    else if ( *str == '[' )
                    {
                        mode = ARRAY_MODE;
                        str = kege::strskp( str, "[" );
                        state = '[';
                    }
                    else if (*str >= '0' && '9' >= *str)
                    {
                        state = 31;
                    }
                    break;

                case '{':
                    mode = OBJECT_MODE;
                    if ( !stack.empty() )
                    {
                        stack.push({ name, new Json::Object });
                    }
                    else
                    {
                        stack.push({ "", &_objects });
                    }
                    //insert( stack, name, new Json::Object );
                    str = kege::strskp( str, "{\n\t" );
                    state = *str;
                    break;

                case '[':
                    mode = ARRAY_MODE;
                    stack.push({ name, new json::Array });
                    str = kege::strskp( str, "[\n\t" );
                    state = *str;
                    break;

                case ']':
                case '}':{
                    StackElem pair = stack.top();
                    stack.pop();
                    if ( !stack.empty() )
                    {
                        if ( stack.top().second->type == Json::Elem::OBJECT )
                        {
                            Json::Object* obj = (Json::Object*) stack.top().second;
                            obj->insert( pair.first, pair.second );
                        }
                        else if ( stack.top().second->type == Json::Elem::ARRAY )
                        {
                            json::Array* obj = (json::Array*) stack.top().second;
                            obj->append( pair.second );
                        }
                    }
                    //insert( _elements, stack, pair.first, pair.second );
                    if(*str == ']' || *str == '}' )str++;
                    state = *str;
                }break;

                case 30:
                {
                    kege::string value;
                    str = parseWord( str, value );
                    str = kege::strskp( str, ", \t\n" );
                    state = *str;

                    insert( stack, name, new json::String( value ) );
                }break;

                case 31:{
                    kege::string value;
                    str = parseNumeric( str, value );
                    str = kege::strskp( str, ", \t\n" );
                    state = *str;

                    insert( stack, name, new json::Integer( atof( value.c_str() ) ) );
                }break;
            }
        }
    }
    void Json::print()
    {
        _objects.print(0);
    }

    Json::Json(){}

    kege::string Json::value()const
    {
        return kege::string();
    }

}
