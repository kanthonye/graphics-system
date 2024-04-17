//
//  shader-program.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "hashmap.hpp"
#include "shader-preprocessor.hpp"
#include "json.hpp"
#include "../../../graphics/initializer/graphics.hpp"

namespace kege{

    uint32_t sizeOf( kege::Format format )
    {
        switch( format )
        {
            case R32_SINT:
            case R32_FLOAT:
            case R32_UINT: return sizeof(float);

            case RG32_SINT:
            case RG32_FLOAT:
            case RG32_UINT: return 2 * sizeof(float);

            case RGB32_SINT:
            case RGB32_FLOAT:
            case RGB32_UINT: return 3 * sizeof(float);

            case RGBA32_SINT:
            case RGBA32_FLOAT:
            case RGBA32_UINT: return 4 * sizeof(float);

            case R64_SINT:
            case R64_FLOAT:
            case R64_UINT: return sizeof(double);

            case RG64_SINT:
            case RG64_FLOAT:
            case RG64_UINT: return 2 * sizeof(double);

            case RGB64_SINT:
            case RGB64_FLOAT:
            case RGB64_UINT: return 3 * sizeof(float);

            case RGBA64_SINT:
            case RGBA64_FLOAT:
            case RGBA64_UINT: return 4 * sizeof(float);

            default: return 0;
        }
    }
//
//    kege::Ref< kege::Shader > loadShaderStage( kege::ShaderStageBit stage, const kege::string& filename )
//    {
//        std::vector< char > source = FileIO::loadFile( filename );
//        if ( source.empty() )
//        {
//            return nullptr;
//        }
//        return kege::Shader::create({ stage, source });
//    }

    static kege::Format stringToFormat( const kege::string& str )
    {
        static kege::Hashmap< kege::Format > formats;
        if ( formats.empty() )
        {
            formats.insert("int",   kege::R32_SINT );
            formats.insert("float", kege::R32_FLOAT );
            formats.insert("double", kege::R64_FLOAT );
            formats.insert("vec2",  kege::RG32_FLOAT );
            formats.insert("ivec2", kege::RG32_SINT );
            formats.insert("dvec2", kege::RG64_FLOAT );
            formats.insert("vec3",  kege::RGB32_FLOAT );
            formats.insert("ivec3", kege::RGB32_SINT );
            formats.insert("dvec3", kege::RGB64_FLOAT );
            formats.insert("vec4",  kege::RGBA32_FLOAT );
            formats.insert("ivec4", kege::RGBA32_SINT );
            formats.insert("dvec4", kege::RGBA64_FLOAT );
            formats.insert("mat3",  kege::RGBA64_FLOAT );
            formats.insert("mat4", kege::RGBA64_FLOAT );
        }
        return formats[ str ];
    }

    static uint32_t siseOfDataType( const kege::string& str )
    {
        static kege::Hashmap< uint32_t > formats;
        if ( formats.empty() )
        {
            formats.insert("int",    4 );
            formats.insert("float",  4 );
            formats.insert("double", 8 );
            formats.insert("vec2",   sizeof( kege::fvec2 ) );
            formats.insert("ivec2",  sizeof( kege::ivec2 ) );
            formats.insert("dvec2",  sizeof( kege::dvec2 ) );
            formats.insert("vec3",   sizeof( kege::fvec3 ) );
            formats.insert("ivec3",  sizeof( kege::ivec3 ) );
            formats.insert("dvec3",  sizeof( kege::dvec3 ) );
            formats.insert("vec4",   sizeof( kege::fvec4 ) );
            formats.insert("ivec4",  sizeof( kege::ivec4 ) );
            formats.insert("dvec4",  sizeof( kege::dvec4 ) );
            formats.insert("mat2",   sizeof( kege::mat22 ) );
            formats.insert("mat3",   sizeof( kege::mat33 ) );
            formats.insert("mat4",   sizeof( kege::mat44 ) );
            formats.insert("mat2x3",  sizeof( kege::mat23 ) );
            formats.insert("mat2x4",  sizeof( kege::mat24 ) );
            formats.insert("mat3x4",  sizeof( kege::mat34 ) );
            formats.insert("mat4x3",  sizeof( kege::mat43 ) );
            formats.insert("mat4x2",  sizeof( kege::mat42 ) );
        }
        return formats[ str ];
    }

    static kege::PrimitiveTopology stringToPrimitiveTopology( const kege::string& str )
    {
        static kege::Hashmap< kege::PrimitiveTopology > polygon_types;
        if ( polygon_types.empty() )
        {
            polygon_types.insert( "point-list",                     kege::POINT_LIST );
            polygon_types.insert( "triangle-list",                  kege::TRIANGLE_LIST );
            polygon_types.insert( "triangle-strip",                 kege::TRIANGLE_STRIP );
            polygon_types.insert( "triangle-fan",                   kege::TRIANGLE_FAN );
            polygon_types.insert( "triangle-list-with-adjacency",   kege::TRIANGLE_LIST_WITH_ADJACENCY );
            polygon_types.insert( "triangle-strip-with-adjacency",  kege::TRIANGLE_STRIP_WITH_ADJACENCY );
            polygon_types.insert( "line-list",                      kege::LINE_LIST );
            polygon_types.insert( "line-strip",                     kege::LINE_STRIP );
            polygon_types.insert( "line-list-with-adjacency",       kege::LINE_LIST_WITH_ADJACENCY );
            polygon_types.insert( "line-strip-with-adjacency",      kege::LINE_STRIP_WITH_ADJACENCY );
        }
        return polygon_types[ str ];
    }

    static kege::DescriptorType stringToDescriptorType( const kege::string& str )
    {
        static kege::Hashmap< kege::DescriptorType > descriptors;
        if ( descriptors.empty() )
        {
            descriptors.insert( "sampler", kege::DESCRIPTOR_SAMPLER );
            descriptors.insert( "sampler-2d", kege::DESCRIPTOR_COMBINED_IMAGE_SAMPLER );
            descriptors.insert( "sampled-image", kege::DESCRIPTOR_SAMPLED_IMAGE );
            descriptors.insert( "storage-image", kege::DESCRIPTOR_STORAGE_IMAGE );
            descriptors.insert( "uniform-texel-buffer", kege::DESCRIPTOR_UNIFORM_TEXEL_BUFFER );
            descriptors.insert( "storage-texel-buffer", kege::DESCRIPTOR_STORAGE_TEXEL_BUFFER );
            descriptors.insert( "uniform-buffer", kege::DESCRIPTOR_UNIFORM_BUFFER );
            descriptors.insert( "storage-buffer", kege::DESCRIPTOR_STORAGE_BUFFER );
            descriptors.insert( "uniform-buffer-dynamic", kege::DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC );
            descriptors.insert( "storage-buffer-dynamic", kege::DESCRIPTOR_STORAGE_BUFFER_DYNAMIC );
            descriptors.insert( "input-attachment", kege::DESCRIPTOR_INPUT_ATTACHMENT );
        }
        return descriptors[ str ];
    }

    static kege::ShaderStageBit stringToShaderStageBit( const kege::string& str )
    {
        static kege::Hashmap< kege::ShaderStageBit > shaders_types;
        if ( shaders_types.empty() )
        {
            shaders_types.insert( "vertex",             kege::VERTEX_SHADER );
            shaders_types.insert( "fragment",           kege::FRAGMENT_SHADER );
            shaders_types.insert( "tess-evaluation",    kege::TESS_EVALUATION_SHADER );
            shaders_types.insert( "tess-control",       kege::TESS_CONTROL_SHADER );
            shaders_types.insert( "geometry",           kege::GEOMETRY_SHADER );
            shaders_types.insert( "compute",            kege::COMPUTE_SHADER );
        }

        return shaders_types[ str ];
    }

    static uint32_t stringToShaderStageFlags( const Json::Elem* stages )
    {
        uint32_t i = 0;
        uint32_t shader_stage_bits = 0;
        const Json::Elem* stage;
        for(i = 0; (stage = stages->at( i )) != nullptr; i++ )
        {
            shader_stage_bits |= stringToShaderStageBit( *stage->str() );
        }

        return shader_stage_bits;
    }


    Hashmap< uint32_t > shaders_types;
    static kege::PolygonMode stringToPolygonMode( const kege::string& str )
    {
        static Hashmap< kege::PolygonMode > polygon_modes;
        if ( polygon_modes.empty() )
        {
            polygon_modes.insert( "fill",         kege::FILL );
            polygon_modes.insert( "line",         kege::LINE );
            polygon_modes.insert( "point",        kege::POINT );
        }
        return polygon_modes[ str ];
    }

    static kege::CullMode stringToCullMode( const kege::string& str )
    {
        static Hashmap< kege::CullMode > cull_modes;
        if ( cull_modes.empty() )
        {
            cull_modes.insert( "cull_cw",   kege::CULL_CW );
            cull_modes.insert( "cull_ccw",  kege::CULL_CCW );
            cull_modes.insert( "cull_none", kege::CULL_NONE );
        }
        return cull_modes[ str ];
    }

    uint32_t parseSizeOf( const kege::string& str )
    {
        uint32_t sum = 0;
        const char* s = str.c_str();
        if ( match(s, "sizeof") )
        {
            s = kege::strskp( s, "sizeof( " );
            char buf[32];
            while ( *s != 0 && *s != ')' )
            {
                s = strcpy(buf, 32, "), ", s);
                s = strskp(s, "), ");
                sum += kege::sizeOf( stringToFormat( buf ) );
            }
        }
        else
        {
            sum = std::stoi( str.c_str() );
        }
        return sum;
    }

    kege::Ref< ShaderProgram > ShaderProgram::load( const kege::string& filename, const kege::Framebuffer* framebuffer )
    {
        kege::Json json;
        if ( !json.load( FileIO::open( filename ) ) )
        {
            return nullptr;
        }

        kege::string path = FileIO::virdir().fetch( filename );
        path = path.parse_fpath();

        const Json::Elem* rasterization = nullptr;
        const Json::Elem* descriptors = nullptr;
        const Json::Elem* constants = nullptr;
        const Json::Elem* bindings = nullptr;
        const Json::Elem* stages = nullptr;
        const Json::Elem* name = nullptr;

        CreateInfo info = {};
        info.renderpass = framebuffer->renderpass();

        const Json::Elem* shader_program = json[ "shader-program" ];
        if ( !shader_program )
        {
            KEGE_ERROR( "'pipeline' not found in file json shader file %s", filename.c_str() );
            return nullptr;
        }
        
        const Json::Elem* pipeline = shader_program->get( "pipeline" );
        if ( *pipeline->str() == "graphics" )
        {
            info.pipeline_layout_create_info.pipeline_layout_type = kege::GRAPHICS_PIPELINE_BIND_POINT;
            rasterization   = shader_program->get( "rasterization" );
            bindings        = shader_program->get( "input-bindings" );
            stages          = shader_program->get( "shader-stages" );
            name            = shader_program->get( "name" );
        }
        else if ( *pipeline->str() == "compute" )
        {
            info.pipeline_layout_create_info.pipeline_layout_type = kege::COMPUTE_PIPELINE_BIND_POINT;

            descriptors     = shader_program->get( "descriptor-sets" );
            constants       = shader_program->get( "push-constants" );
            stages          = shader_program->get( "shader-stages" );
            name            = shader_program->get( "name" );
        }

        if ( name )
        {
            info.name = *name->str();
        }

        if ( rasterization )
        {
            info.primitive_topology = stringToPrimitiveTopology( *rasterization->get( "primative-topology" )->str() );
            info.polygon_mode = stringToPolygonMode( *rasterization->get( "polygon-mode" )->str() );
            info.cull_mode = stringToCullMode( *rasterization->get( "cull-mode" )->str() );
        }

        if ( bindings )
        {
            int i=0;
            const Json::Elem* binding;
            while( (binding = bindings->at( i++ )) != nullptr )
            {
                kege::VertexInputBindingDescription b;
                b.binding = binding->get( "binding" )->uint32();
                b.stride = parseSizeOf( *binding->get( "stride" )->str() );
                kege::string str = *binding->get( "input-rate" )->str();
                if (str == "input-per-instance")
                {
                    b.input_rate = kege::VERTEX_INPUT_PER_INSTANCE;
                }
                else
                {
                    b.input_rate = kege::VERTEX_INPUT_PER_VERTEX;
                }
                info.bindings.push_back( b );
            }
        }

        if ( stages )
        {
            ShaderReflection reflection;
            kege::Ref< kege::Shader > shader_module;

            for (int i=0; stages->at(i) != nullptr; i++)
            {
                kege::string stage_name = *stages->at(i)->get( "stage" )->str();
                kege::string file_name = *stages->at(i)->get( "file" )->str();
                ShaderStageBit shader_stage = stringToShaderStageBit( stage_name );

                std::vector< char > source = FileIO::loadFile( path +"/"+ file_name );
                shader_module = kege::Shader::create({ shader_stage, source });
                if ( !shader_module )
                {
                    return nullptr;
                }
                kege::parse( &reflection, shader_stage, source.data() );
                info.shaders.push_back( shader_module );
            }

            for (int i=0; i<reflection.attributes.size(); i++)
            {
                kege::VertexInputAttributeDescription attrib = {};
                attrib.location = reflection.attributes[i]->location;
                attrib.format = stringToFormat( reflection.attributes[i]->type );
                attrib.binding = 0;
                attrib.offset = 0;

                info.attributes.push_back( attrib );
            }

            for (int i=0; i<reflection.descriptors.size(); i++)
            {
                kege::DescriptorBinding binding = {};
                binding.count = 1;
                binding.set = reflection.descriptors[i]->set;
                binding.binding = reflection.descriptors[i]->binding;
                binding.descriptor_type = reflection.descriptors[i]->descriptor_type;
                info.pipeline_layout_create_info.bindings.push_back( binding );
                info.pipeline_layout_create_info.binding_names.push_back( reflection.descriptors[i]->name );
            }

            for (int i=0; i<reflection.push_constants.size(); i++)
            {
                kege::PushConstantRange push_constant = {};
                for (int j=0; j<reflection.push_constants[i]->members.size(); j++)
                {
                    push_constant.size += siseOfDataType( reflection.push_constants[i]->members[i].type );
                }
                push_constant.stages = reflection.push_constants[i]->shader_stage;
                push_constant.offset = 0;
                
                info.pipeline_layout_create_info.constansts.push_back( push_constant );
            }
        }
        return ShaderProgram::create( info );
    }

    kege::Ref< ShaderProgram > ShaderProgram::create( const CreateInfo& info )
    {
        kege::Ref< PipelineLayout > pipeline_layout = PipelineLayout::create( info.pipeline_layout_create_info );
        if ( !pipeline_layout )
        {
            return nullptr;
        }

        kege::Ref< Pipeline > pipeline = Pipeline::create
        ({
            info.attributes,
            info.bindings,
            info.shaders,
            pipeline_layout,
            info.renderpass,
            info.primitive_topology,
            info.polygon_mode,
            info.cull_mode
        });

        if ( !pipeline )
        {
            return nullptr;
        };

        return new kege::ShaderProgram( pipeline );
    }

    void ShaderProgram::pushConstants( kege::CommandBuffer* command_buffer, const kege::PushConstantBlock& constants )const
    {
        command_buffer->pushConstants( _pipeline->getPipelineLayout(), constants );
    }

    void ShaderProgram::use( kege::CommandBuffer* command_buffer )const
    {
        command_buffer->bindPipeline( _pipeline );
    }

    const kege::Pipeline* ShaderProgram::getPipeline()const
    {
        return _pipeline.ref();
    }
    
    ShaderProgram::ShaderProgram( kege::Ref< Pipeline > pipeline )
    :   _pipeline( pipeline )
    {}
}
