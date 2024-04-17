//
//  file-io.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#ifndef kege_file_io_hpp
#define kege_file_io_hpp

#include "vir-dir.hpp"

namespace kege
{
    class File;

    /**
     * @class FileIO
     * @brief The FileIO module responsible for handling file input/output operations.
     *
     * This module provides functionality for initializing and managing file input/output operations
     * within the game engine. It inherits from the Module class.
     */
    class FileIO
    {
    public:

        /**
         * @brief Loads the source code of a shader from a file.
         * @param filename The name of the file containing the shader source code.
         * @return A vector of uint32_t representing the loaded shader source code.
         */
        static std::vector< uint32_t > loadShaderSource( const std::string& filename );

        /**
         * @brief Loads the content of a file into memory.
         * @param filename The name of the file to load.
         * @return A vector of char representing the content of the loaded file.
         */
        static std::vector< char > loadFile( const kege::string& filename );

        /**
         * @brief Opens a file for reading or writing.
         * @param filename The name of the file to open.
         * @return A File object representing the opened file.
         */
        static File open( const kege::string& filename );

        /**
         * @brief Get the real filename of a virtual filename
         * @param vfname The virtual filename
         * @return The real filename.
         */
        static kege::string dir( const kege::string& vfname );

        /**
         * @brief Retrieves the virtual directory for file operations.
         * @return A reference to the virtual directory.
         */
        static kege::VirDir& virdir();
        /**
         * @brief Saves a file.
         * @return True if the file is successfully saved, false otherwise.
         */
        static bool saveFile();

        /**
         * @brief Initializes the FileIO module.
         * @param rootpath The root path for file resources.
         * @return True if initialization is successful, false otherwise.
         */
        bool init( const kege::string& rootpath );

        /**
         * @brief Uninitializes the FileIO module.
         */
        void uninit();

    private:

        FileIO& operator =( const kege::FileIO& other ) = delete;
        FileIO( const kege::FileIO& other ) = delete;
        ~FileIO();
        FileIO();

    private:

        static kege::Ref< kege::VirDir > _virdir;
        friend kege::Ref< kege::FileIO >;
    };

}

#endif /* kege_file_io_hpp */
