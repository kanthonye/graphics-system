//
//  io.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include "file-io.hpp"
#include "logger.hpp"

namespace kege{

    std::vector< char > FileIO::loadFile( const kege::string& filename )
    {
        kege::File file = _virdir->open( filename );
        if ( !file )
        {
            KEGE_ERROR("file not found -> %s", filename.c_str());
            return {};
        }
        std::vector< char > buffer( file.size() + 1 );
        file.read( buffer.data(), 1, file.size() );
        buffer[ file.size() ] = 0;
        return buffer;
    }

    File FileIO::open( const kege::string& filename )
    {
        return _virdir->open( filename );
    }

    bool FileIO::saveFile()
    {
        return true;
    }

    kege::string FileIO::dir( const kege::string& fname )
    {
        return _virdir->fetch( fname );
    }

    kege::VirDir& FileIO::virdir()
    {
        return *_virdir;
    }
    
    void FileIO::uninit()
    {
    }

    bool FileIO::init( const kege::string& rootpath )
    {
        kege::string filename = rootpath + "/assets/config/directories.txt";
        kege::File file = kege::File::open(filename.c_str(), "r");
        if ( !file )
        {
            KEGE_ERROR("directories file %s not found at", filename.c_str());
            return false;
        }

        _virdir = new kege::VirDir();
        std::vector< char > buffer( file.size() + 1 );
        file.read(buffer.data(), 1, file.size());
        buffer[ file.size() ] = 0;
        
        const char* str = buffer.data();
        char tmp[2][128];

        while( *str != EOF && *str != 0 )
        {
            str = strskp( str, " \t\n" );
            str = strcpy( tmp[0], 128, " :\t\n", str );

            str = strskp( str, " :\t\n" );
            str = strcpy( tmp[1], 128, " :\t\n", str );

            str = strskp( str, " :\t\n" );

            _virdir->add( tmp[0], tmp[1] );
        }
        return true;
    }

    FileIO::~FileIO()
    {}

    FileIO::FileIO()
    {}


    kege::Ref< kege::VirDir > FileIO::_virdir;

}




namespace kege{
    
    std::vector< uint32_t > loadSPIRV( const std::string& filename )
    {
        kege::File file = kege::File::open( filename.c_str(), "r" );
        if ( !file )
        {
            return {};
        }
        int64_t size = file.size() / sizeof(uint32_t);
        std::vector< uint32_t > buffer( size + 1 );
        file.read( buffer.data(), sizeof(uint32_t), file.size() );
        buffer[ size ] = 0;
        return buffer;
    }


    std::string getFileEXT( const std::string& filename )
    {
        return filename.substr( filename.find_last_of(".") + 1 );
    }

    std::string creatSPIRVFileFromGLSLFile( const std::string& filename )
    {
        const std::string exe = "/Applications/Developer/VulkanSDK/1.3.236.0/macOS/bin/glslc";
        const std::string file = filename.substr( filename.find_last_of("/\\") + 1 );
        const std::string name = file.substr(0, file.rfind("."));
        const std::string ext = getFileEXT( file );// file.substr(0, file.rfind("."));

        // create directory to store SPIR-V files
        size_t last_slash_idx = filename.rfind("/");
        const std::string directory = filename.substr(0, last_slash_idx) + "/spv";
        std::filesystem::create_directory( directory );

        // compile vs file into SPIR-V files and store into directory spv
        const std::string output = directory + "/" + name + "-" + ext + ".spv";
        const std::string command = exe + " " + filename + " -o " + output;
        if( system( command.data() ) != 0 )
        {
            KEGE_ERROR( "something went wrong while converting GLSL file %s to SPIRV file %s", filename.c_str(), output.c_str() );
            //throw std::runtime_error("");
            return "";
        }

        return output;
    }

    /**
     load SPIR-V file, or GLSL file. if the @b filename ext is not an  spv, then the file is converted to SPIR-V, loaded, and the content of the file is returned
     @param filename should be an SPIR-V file, or GLSL file.
     @return SPIR-V binary file data
     */
    std::vector< uint32_t > FileIO::loadShaderSource( const std::string& filename )
    {
        const std::string& ext = getFileEXT( filename );
        if ( ext == "spv" )
        {
            return loadSPIRV( _virdir->fetch( filename.c_str() ).c_str() );
        }
        else
        {
            const std::string spirv_filename = creatSPIRVFileFromGLSLFile( _virdir->fetch( filename.c_str() ).c_str() );
            if ( spirv_filename == "" )
            {
                KEGE_ERROR("failed to compile file -> %s", filename.c_str(), " to SPIR-V !!" );
                return {};
            }
            else
            {
                return loadSPIRV( spirv_filename );
            }
        }
    }
}
