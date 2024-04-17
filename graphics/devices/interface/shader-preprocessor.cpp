//
//  shader-preprocessor.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 4/5/24.
//

#include "shader-preprocessor.hpp"

namespace kege{

    ShaderReflection::~ShaderReflection()
    {
        inputs.clear();
        outputs.clear();
        descriptors.clear();
        push_constants.clear();

        for (kege::ShaderReflection::Layout* a : layouts ) delete a;
        layouts.clear();

        for (kege::ShaderReflection::Struct* a : structs ) delete a;
        structs.clear();
    }


    const char* sskp( const char* s, const char* b )
    {
        while (*s == *b && *s != 0 && *b != 0)
        {
            s++;
            b++;
        }
        return s;
    }
    const char* strseek( const char* s, const char* b )
    {
        while ( *b != 0 && strchr( b, *s ) == nullptr ) s++;
        return s;
    }

    bool is_word( const char* s )
    {
        return
        (
         *s != 0 &&
         (
          (*s >= 'A' && *s <= 'Z') ||
          (*s >= 'a' && *s <= 'z') ||
          (*s >= '0' && *s <= '9') ||
          (*s == '_')
         )
        );
    }

    bool is_numeric( const char* s )
    {
        return
        (
         *s != 0 &&
         (
          (*s >= '0' && *s <= '9') ||
          (*s == '.') ||
          (*s == '+') ||
          (*s == '-') ||
          (*s == 'e') ||
          (*s == 'E')
         )
        );
    }

    const char* getWord( const char* source, char* buf )
    {
        int i=0;
        if ( is_word( source ) )
        {
            while ( is_word( source ) && i <= 63 )
            {
                buf[ i++ ] = *source++;
            }
            buf[i] = 0;
        }
        return source;
    }
    const char* getNumeric( const char* source, char* buf )
    {
        int i=0;
        if ( is_numeric( source ) )
        {
            while ( is_numeric( source ) && i <= 63 )
            {
                buf[ i++ ] = *source++;
            }
            buf[i] = 0;
        }
        return source;
    }

    void clearWhiteSpace( int &lines, const char*& source, const char* flags )
    {
        while ( *source != 0 )
        {
            if ( *source == '\n' || *source == '\r' )
            {
                source++;
                lines++;
                continue;
            }

            if ( *source == ' ' )
            {
                source = kege::strskp( source, " " );
                continue;
            }

            if ( flags != nullptr )
            {
                if ( strchr( flags, *source ) != nullptr )
                {
                    source = kege::strskp( source, flags );
                    continue;;
                }
            }

            break;
        }
    }

    const char* parseLayout( ShaderReflection* reflection, kege::ShaderStageBit shader_stage, const char* source, int& lines, char buf[64] )
    {
        kege::ShaderReflection::Layout* layout = new kege::ShaderReflection::Layout;
        reflection->layouts.push_back( layout );
        *layout = {};

        source = kege::sskp( source, "layout" );
        clearWhiteSpace( lines, source, nullptr );

        if ( *source == '(' )
        {
            layout->shader_stage = shader_stage;
            bool push_constants = false;
            clearWhiteSpace( lines, source, "(" );

            while ( *source != ')' && *source != 0 )
            {
                if ( kege::match( source,"set" ) )
                {
                    source = kege::sskp( source, "set" );
                    clearWhiteSpace( lines, source, "=" );

                    source = strcpy( buf, 64, ",) \t\n\r", source );
                    layout->set = atoi( buf );
                }
                else if ( kege::match( source,"binding" ) )
                {
                    source = kege::sskp( source, "binding" );
                    clearWhiteSpace( lines, source, "=" );

                    source = strcpy( buf, 64, ",) \t\n\r", source );
                    layout->binding = atoi( buf );
                }
                else if ( kege::match( source,"location" ) )
                {
                    source = kege::sskp( source, "location" );
                    clearWhiteSpace( lines, source, "=" );

                    source = strcpy( buf, 64, ",) \t\n\r", source );
                    layout->location = atoi( buf );
                }
                else if ( kege::match( source,"push_constant" ) )
                {
                    source = kege::sskp( source, "push_constant" );
                    clearWhiteSpace( lines, source, nullptr);

                    reflection->push_constants.push_back( layout );
                    push_constants = true;
                    layout->type = "push_constant";
                }
                else
                {
                    source = strseek( source, ",)" );
                }
                clearWhiteSpace( lines, source, "," );
            }

            clearWhiteSpace( lines, source, ")" );

            if ( kege::match( source, "in" ) )
            {
                reflection->inputs.push_back( layout );
                source = kege::sskp( source, "in" );
                clearWhiteSpace( lines, source, nullptr );

                source = strcpy( buf, 64, " \n\t\r", source );
                clearWhiteSpace( lines, source, nullptr );
                layout->type = buf;
                
                if ( shader_stage == kege::VERTEX_SHADER )
                {
                    reflection->attributes.push_back( layout );
                }
            }
            else if ( kege::match( source, "uniform" ) )
            {
                source = kege::sskp( source, "uniform" );
                clearWhiteSpace( lines, source, nullptr );

                if ( kege::match( source, "sampler2D") )
                {
                    source = kege::sskp( source, "sampler2D" );
                    clearWhiteSpace( lines, source, nullptr );
                    //source = strcpy( buf, 64, " ;\n\t\r", source );
                    layout->type = "sampler2D";
                    layout->descriptor_type = kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER;
                    reflection->descriptors.push_back( layout );
                }
                else if ( kege::match( source, "readonly") )
                {
                    source = kege::sskp( source, "readonly" );
                    clearWhiteSpace( lines, source, nullptr );
                    source = strcpy( buf, 64, "; \n\t\r", source );
                    layout->type = buf;
                    layout->descriptor_type = kege::DESCRIPTOR_STORAGE_IMAGE;
                    reflection->descriptors.push_back( layout );
                }
                else if ( kege::match( source, "writeonly") )
                {
                    source = kege::sskp( source, "writeonly" );
                    clearWhiteSpace( lines, source, nullptr );
                    source = strcpy( buf, 64, "; \n\t\r", source );
                    layout->type = buf;
                    layout->descriptor_type = kege::DESCRIPTOR_STORAGE_IMAGE;
                    reflection->descriptors.push_back( layout );
                }
                else if ( !push_constants )
                {
                    layout->type = "uniform";
                    layout->descriptor_type = kege::DESCRIPTOR_UNIFORM_BUFFER;
                    reflection->descriptors.push_back( layout );
                }
            }
            else if ( kege::match( source, "buffer" ) )
            {
                layout->type = "buffer";
                layout->descriptor_type = kege::DESCRIPTOR_STORAGE_BUFFER;
                reflection->descriptors.push_back( layout );
                source = kege::sskp( source, "buffer" );
                clearWhiteSpace( lines, source, nullptr );
            }
            else if ( kege::match( source, "out" ) )
            {
                reflection->outputs.push_back( layout );
                source = kege::sskp( source, "out" );
                clearWhiteSpace( lines, source, nullptr );

                source = strcpy( buf, 64, " \n\t\r", source );
                clearWhiteSpace( lines, source, nullptr );
                layout->type = buf;
            }

            clearWhiteSpace( lines, source, nullptr );
            source = strcpy( buf, 64, " ;\n\t\r", source );
            clearWhiteSpace( lines, source, nullptr );
            layout->name = buf;

            if ( *source == '{' )
            {
                source++;
                clearWhiteSpace( lines, source, nullptr );
                ShaderReflection::Variable member;
                while ( *source != '}' && *source != 0 )
                {
                    source = strcpy( buf, 64, "; \n\t\r", source );
                    member.type = buf;
                    clearWhiteSpace( lines, source, ";" );

                    source = strcpy( buf, 64, "; \n\t\r", source );
                    member.name = buf;
                    clearWhiteSpace( lines, source, ";" );

                    layout->members.push_back( member );
                }
                clearWhiteSpace( lines, source, "}" );
                if ( *source != ';' )
                {
                    clearWhiteSpace( lines, source, nullptr );
                    source = strcpy( buf, 64, "; \n\t\r", source );
                    layout->instance_name = buf;
                }
            }
            clearWhiteSpace( lines, source, ";" );
        }
        else
        {
            throw std::runtime_error("expected char '('. line: ");
        }
        return source;
    }

    void parse( ShaderReflection* reflection, kege::ShaderStageBit shader_stage, const char* source )
    {
        int lines = 0;
        char buf[64];
        while ( *source != 0 )
        {
            clearWhiteSpace( lines, source, nullptr );

            if ( kege::match( source, "layout" ) )
            {
                source = parseLayout( reflection, shader_stage, source, lines, buf );
            }
            else if ( kege::match( source, "struct" ) )
            {
                source = kege::sskp( source, "struct" );
                clearWhiteSpace( lines, source, nullptr );
                source = strcpy( buf, 64, "; \n\t\r", source );
                clearWhiteSpace( lines, source, nullptr );

                kege::ShaderReflection::Struct* object = new kege::ShaderReflection::Struct;
                object->name = buf;
                reflection->structs.push_back( object );

                if ( *source == '{' )
                {
                    clearWhiteSpace( lines, source, "{" );
                    ShaderReflection::Variable member;
                    while ( *source != '}' && *source != 0 )
                    {
                        source = strcpy( buf, 64, "; \n\t\r", source );
                        member.type = buf;
                        clearWhiteSpace( lines, source, ";" );

                        source = strcpy( buf, 64, "; \n\t\r", source );
                        member.name = buf;
                        clearWhiteSpace( lines, source, ";" );

                        object->members.push_back( member );
                    }
                    clearWhiteSpace( lines, source, "};" );
                }
                else
                {
                    throw std::runtime_error("expect char '{'. line: ");
                }
            }
            else
            {
//                const char* src = source;
//                if ( is_word( src ) )
//                {
//                    src = getWord( src, buf );
//                    src = strskp( src, " " );
//                    if ( is_word( src ) )
//                    {
//                        src = getWord( src, buf );
//                        src = strskp( src, " " );
//                        if ( *src == '(' )
//                        {
//                            clearWhiteSpace( lines, source, nullptr );
//                            src = strseek(src, ")\n");
//                            if ( *src == ')' )
//                            {
//                                clearWhiteSpace( lines, source, nullptr );
//                                src = strseek(src, "{\n");
//                                if ( *src == '{' )
//                                {
//                                    src = strseek(src, "}\n");
//                                    if ( *src == '}' )
//                                    {
//                                        src++;
//                                        source = src;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
                source = strseek( source, "\n" );
            }
        }
    }
}
