//
//  File.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/13/24.
//

#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <stdlib.h>
#include "kege-string.hpp"

namespace kege
{
    class File
    {
    public:

        uint64_t write( const void*, uint64_t size,  uint64_t count );
        uint64_t read( void* bufr, uint64_t size,  uint64_t count )const;

        static File open( const kege::string& filename, const char* flags );
        operator bool()const;
        uint64_t size()const;

        File( FILE* file, uint64_t filesize );
        File( File& file );
        File();

        ~File();

    private:

        uint64_t _size;
        FILE* _file;
    };
}
#endif /* File_hpp */
