//
//  VirDir.hpp
//  KEGE
//
//  Created by Kenneth Esdaile on 5/27/16.
//  Copyright © 2016 Kenneth Anthony Esdaile. All rights reserved.
//

#ifndef VirDir_hpp
#define VirDir_hpp
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include "ref.hpp"
#include "file.hpp"
#include "hashmap.hpp"
#include "kege-string.hpp"
#include "logger.hpp"
namespace kege{

    class VirDir : public kege::RefCounter
    {
    public:

        /**
         * @param id The string id for the path to add
         * @param path The path to add to the directory
         */
        void add( const kege::string& id, const kege::string& path );

        /**
         * Get the full real file directory of a virtual file or path
         *
         * @code
         * // use file extension virtual directory which returns the full directory + grass.jpg
         * virdir.fetch( "grass.jpg" )
         *
         * // use virtual directory which returns the full directory for image + stone.jpg
         * virdir.fetch( "images/stone.jpg" )
         *
         * // use virtual directory which returns the full directory for assets + images/stone.jpg
         * virdir.fetch( "assets/images/stone.jpg" )
         *
         * // use full directory which returns the same full directory
         * virdir.fetch( "/users/kege/project/images/stone.jpg" )
         *
         * // to get the full directory for the folder images
         * virdir.fetch( "images/" )
         * @endcode
         *
         * @param name Get the real filename of a virtual filename
         *
         * @return The real filename
         */
        kege::string fetch( const kege::string& name );

        /**
         * @param name The virtual filename or the real filename of a file to open
         */
        kege::File open( const kege::string& name );

        /**
         * constructor
         */
        VirDir();

    private:

        kege::Hashmap< uint32_t > _virmap;
        std::vector< kege::string > _directories;
    };


    kege::string readfile( const kege::string& filename );
}
#endif /* vsf_hpp */


