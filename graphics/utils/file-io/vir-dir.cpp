//
//  VirDir.cpp
//  KEGE
//
//  Created by Kenneth Esdaile on 5/27/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#include "vir-dir.hpp"

namespace kege{

    void VirDir::add( const kege::string& name, const kege::string& path )
    {
        int32_t directory_index = (int32_t) _directories.size();
        _directories.push_back( path );
        _virmap.insert( name, directory_index );
    }

    kege::string VirDir::fetch( const kege::string& name )
    {
        /*
         If name[0] starts with '/' then we have the full root file path thus no
         furthure operation need to be applied. Just return the result.
         example name = "/users/kae/projects/assets/textures"
         */
        if( name[0] == '/' )
        {
            return name;
        }
        else  // name = "filename.ext" or "assets/textures/rock.png" or "assets/" 
        {
            char id[64];
            const char* str = strcpy(id, 64, "./\\", name.c_str());

            uint32_t* directory_index = nullptr;

            /*
             In this case 'id' is just the name of a file with no path. So, we need
             to find the path attached to the file extension which is stored in str
             */
            if( *str == '.' )
            {
                directory_index = _virmap.at( str );
            }

            /*
             In this case 'id' is the name of a path and str is the rest of the filename. 
             So, we need to find the path attached to the pathname which is stored in 'id'
             */
            else
            {
                directory_index = _virmap.at( id );
            }

            /*
             If there exist a directory_index then we have a path to a real file. So, we
             will build the file path using the return string from a recursive call to fetch
             */
            if ( directory_index )
            {
                kege::string path = fetch( _directories[ *directory_index ] );
                if( *str == '.' )
                {
                    return path + "/" + name;
                }
                return path + str;
            }

            KEGE_ERROR( "virtual directory don't exist for input %s", name.c_str() );
            return "";
        }
        return "";
    }

    kege::File VirDir::open( const kege::string& fname )
    {
        return kege::File::open( this->fetch( fname ).c_str(), "r" );
    }

    VirDir::VirDir()
    {}

    kege::string readfile( const kege::string& filename )
    {
        FILE* file = fopen(filename.c_str(), "r");
        if ( !file )
        {
            return "";
        }

        fseek(file, 0, SEEK_END);
        uint64_t filesize = ftell(file);
        rewind(file);

        if (filesize == 0) return "";
        char* buffer = new char[ filesize + 1 ];

        fread( buffer, filesize, sizeof(char), file );
        fclose(file);

        buffer[ filesize ] = '\0';
        return kege::string( buffer, filesize, true );
    }
}

