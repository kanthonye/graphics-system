//
//  vk-shader.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/31/23.
//

#include "vk-core.hpp"
#include "shaderc/shaderc.hpp"

namespace kege{namespace vk{

    const char* toString( kege::ShaderStageBit type )
    {
        switch ( type )
        {
            case kege::VERTEX_SHADER: return "VERTEX_SHADER";
            case kege::COMPUTE_SHADER: return "COMPUTE_SHADER";
            case kege::FRAGMENT_SHADER: return "FRAGMENT_SHADER";
            case kege::GEOMETRY_SHADER: return "GEOMETRY_SHADER";
            case kege::TESS_EVALUATION_SHADER: return "TESS_EVALUATION_SHADER";
            case kege::TESS_CONTROL_SHADER: return "TESS_CONTROL_SHADER";
            default: return "UNKNOWN_SHADER";
        }
    }

    VkResult compileGlslToSpv( kege::ShaderStageBit type, const std::vector< char >& source, std::vector< uint32_t >& spirv_code )
    {
        shaderc_shader_kind shaderc_shader_type;
        switch ( type )
        {
            case kege::VERTEX_SHADER: shaderc_shader_type = shaderc_vertex_shader; break;
            case kege::COMPUTE_SHADER: shaderc_shader_type = shaderc_compute_shader; break;
            case kege::FRAGMENT_SHADER: shaderc_shader_type = shaderc_fragment_shader; break;
            case kege::GEOMETRY_SHADER: shaderc_shader_type = shaderc_geometry_shader; break;
            case kege::TESS_EVALUATION_SHADER: shaderc_shader_type = shaderc_tess_evaluation_shader; break;
            case kege::TESS_CONTROL_SHADER: shaderc_shader_type = shaderc_tess_control_shader; break;
            default: throw std::runtime_error("INVALID_ENUM being passed to vk::getShaderStateFlagBit( kege::ShaderStageBit )");
        }

        shaderc::Compiler compiler;
        shaderc::CompileOptions options;
        shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv( source.data(), shaderc_shader_type, toString( type ), options );

        if (result.GetCompilationStatus() != shaderc_compilation_status_success)
        {
            KEGE_ERROR( result.GetErrorMessage().c_str() );
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        spirv_code = std::vector< uint32_t >(result.cbegin(), result.cend());
        return VK_SUCCESS;
    }

    VkShaderModule Shader::compileShaderSource( VkDevice device, kege::ShaderStageBit type, const std::vector< char >& source )
    {
        std::vector< uint32_t > spirv_code;
        if( vk::compileGlslToSpv( type, source, spirv_code ) != VK_SUCCESS )
        {
            return VK_NULL_HANDLE;
        }

        VkShaderModuleCreateInfo create_module_info{};
        create_module_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_module_info.codeSize = spirv_code.size() * 4;
        create_module_info.pCode = spirv_code.data();

        VkResult result;
        VkShaderModule handle;
        
        result = vkCreateShaderModule( device, &create_module_info, nullptr, &handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_FATAL( "%s: failed to create shader module!", vk::getError( result ) );
            return VK_NULL_HANDLE;
        }
        return handle;
    }

    VkResult Shader::construct( const kege::Shader::CreateInfo& info )
    {
        _handle = compileShaderSource( _device->getLogicalDevice(), info.type, info.source );
        if ( _handle == VK_NULL_HANDLE )
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        _stage = vk::getShaderStateFlagBit( info.type );
        return VK_SUCCESS;
    }

    VkShaderStageFlagBits Shader::stage()const
    {
        return _stage;
    }

    const vk::Shader* Shader::vulkan()const
    {
        return this;
    }
    
    vk::Shader* Shader::vulkan()
    {
        return this;
    }
    
    const VkShaderModule Shader::handle()const
    {
        return _handle;
    }

    Shader::~Shader()
    {
        if ( _handle )
        {
            vkDestroyShaderModule( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }


    Shader::Shader( vk::Device* device )
    :   _stage()
    ,   _device( device )
    ,   _handle( VK_NULL_HANDLE )
    {}

}}
