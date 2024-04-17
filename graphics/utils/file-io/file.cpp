//
//  File.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/13/24.
//

#include "file.hpp"
namespace kege
{

    uint64_t File::write( const void* ptr, uint64_t size,  uint64_t count )
    {
        return fwrite( ptr, size, count, _file );
    }

    uint64_t File::read( void* ptr, uint64_t size,  uint64_t count )const
    {
        return fread( ptr, size, count, _file );
    }

    File File::open( const kege::string& filename, const char* flags )
    {
        FILE* file = fopen( filename.c_str(), flags );
        if ( file )
        {
            fseek( file, 0, SEEK_END );
            uint64_t size = ftell( file );
            rewind( file );

            return File( file, size );
        }
        return File( nullptr, 0 );
    }

    File::operator bool()const
    {
        return _file != nullptr;
    }

    uint64_t File::size()const
    {
        return _size;
    }

    File::File( FILE* file, uint64_t size )
    :   _file( file )
    ,   _size( size )
    {
    }

    File::File( File& other )
    :   _file( other._file )
    ,   _size( other._size )
    {
        other._file = nullptr;
        other._size = 0;
    }

    File::File()
    :   _file( nullptr )
    ,   _size( 0 )
    {}

    File::~File()
    {
        if ( _file )
        {
            fclose( _file );
            _file = nullptr;
        }
    }

}
