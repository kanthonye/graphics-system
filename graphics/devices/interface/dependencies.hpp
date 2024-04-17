//
//  graphics-dependencies.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/31/23.
//

#ifndef kege_graphics_dependencies_hpp
#define kege_graphics_dependencies_hpp

#include <set>
#include <map>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <stdexcept>
#include <iostream>
#include "ref.hpp"
#include "math.hpp"
#include "kege-string.hpp"
#include "logger.hpp"
#include "hashmap.hpp"

namespace kege
{
    class Mesh;
    
    static const int MAX_FRAMES_IN_FLIGHT = 2;

    enum ShaderStageBit
    {
        VERTEX_SHADER          = 0b00000001,
        FRAGMENT_SHADER        = 0b00000010,
        TESS_CONTROL_SHADER    = 0b00000100,
        TESS_EVALUATION_SHADER = 0b00001000,
        GEOMETRY_SHADER        = 0b00010000,
        COMPUTE_SHADER         = 0b00100000
    };

    enum PipelineLayoutType
    {
        GRAPHICS_PIPELINE_BIND_POINT,
        COMPUTE_PIPELINE_BIND_POINT,
        RAYTRACE_PIPELINE_BIND_POINT,
    };

    enum PrimitiveTopology
    {
        POINT_LIST,
        LINE_LIST,
        LINE_STRIP,
        TRIANGLE_LIST,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        LINE_LIST_WITH_ADJACENCY,
        LINE_STRIP_WITH_ADJACENCY,
        TRIANGLE_LIST_WITH_ADJACENCY,
        TRIANGLE_STRIP_WITH_ADJACENCY,
        PATCH_LIST,
    };

    enum PolygonMode
    {
        FILL,
        LINE,
        POINT,
    };

    enum CullMode
    {
        CULL_CW,
        CULL_CCW,
        CULL_NONE,
    };

    enum DeviceQueueType
    {
        GRAPHICS_QUEUE,
        COMPUTE_QUEUE,
        TRANSFER_QUEUE,
        PRESENT_QUEUE,
        MAX_QUEUE_COUNT
    };


    /**
     * @brief Specifies how the commands within the subpass will be provided.
     * It can take one of two values:
     *
     * @b VK_SUBPASS_CONTENTS_INLINE: The commands
     * for the subpass will be recorded inline within the primary command buffer.
     *
     * @b VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS: The commands for the subpass
     * will be recorded in secondary command buffers that are executed within the
     * primary command buffer.
     */
    typedef enum SubpassContents
    {
        /**
         * Specify that the commands for the subpass will be recorded inline within the
         * primary command buffer.
         */
        SUBPASS_CONTENTS_PRIMARY_COMMAND_BUFFERS,

        /**
         * Specify that the commands for the subpass will be recorded in secondary command
         * buffers that are executed within the primary command buffer.
         */
        SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS
    } SubpassContents;


    typedef enum CommandBufferType
    {
        PRIMARY_COMMAND_BUFFER,
        SECONDARY_COMMAND_BUFFER
    } CommandBufferType;


    typedef enum IndexType
    {
        INDEX_TYPE_U8,
        INDEX_TYPE_U16,
        INDEX_TYPE_U32,
    } IndexType;

    typedef enum VertexInputRate
    {
        VERTEX_INPUT_PER_VERTEX,
        VERTEX_INPUT_PER_INSTANCE,
    } VertexInputRate;

    enum Format
    {
        R8_UNORM,
        RG8_UNORM,
        RGB8_UNORM,
        RGBA8_UNORM,

        R8_UINT,
        RG8_UINT,
        RGB8_UINT,
        RGBA8_UINT,

        R16_UINT,
        RG16_UINT,
        RGB16_UINT,
        RGBA16_UINT,

        R32_UINT,
        RG32_UINT,
        RGB32_UINT,
        RGBA32_UINT,

        R64_UINT,
        RG64_UINT,
        RGB64_UINT,
        RGBA64_UINT,

        R8_SINT,
        RG8_SINT,
        RGB8_SINT,
        RGBA8_SINT,

        R16_SINT,
        RG16_SINT,
        RGB16_SINT,
        RGBA16_SINT,

        R32_SINT,
        RG32_SINT,
        RGB32_SINT,
        RGBA32_SINT,

        R64_SINT,
        RG64_SINT,
        RGB64_SINT,
        RGBA64_SINT,

        R32_FLOAT,
        RG32_FLOAT,
        RGB32_FLOAT,
        RGBA32_FLOAT,

        R64_FLOAT,
        RG64_FLOAT,
        RGB64_FLOAT,
        RGBA64_FLOAT,

        R8_SRGB,
        RG8_SRGB,
        RGB8_SRGB,
        RGBA8_SRGB,

        BGR8_SRGB,
        BGRA8_SRGB,

        DEPTH_16_UNORM,
        DEPTH_24_UNORM_PACK32,
        DEPTH_32_SFLOAT,
        DEPTH_16_UNORM_S8_UINT,
        DEPTH_24_UNORM_S8_UINT,
        DEPTH_32_SFLOAT_S8_UINT,
    };

    enum Attachment
    {
        COLOR_ATTACHMENT,
        DEPTH_ATTACHMENT,
        DEPTH_STENCIL_ATTACHMENT,
    };

    typedef enum BufferType
    {
        VERTEX_BUFFER,
        INDEX_BUFFER,
        UNIFORM_BUFFER,
        STORAGE_BUFFER,
        TRANSFER_BUFFER,
        UNIFORM_TEXEL_BUFFER,
        STORAGE_TEXEL_BUFFER,
        INDIRECT_BUFFER,
    } BufferType;

    typedef enum MemoryUsage
    {
        STATIC_BUFFER,
        DYNAMIC_BUFFER,
        STREAM_BUFFER,
    } MemoryUsage;

}


namespace kege{

    typedef struct ClearColorState
    {
        float color[4];
    } ClearColorState;

    typedef struct ClearDepthState
    {
        float value;
    } ClearDepthState;

    typedef struct DrawCommand
    {
        uint32_t vertex_count;
        uint32_t instance_count;
        uint32_t first_vertex;
        uint32_t first_instance;
    } DrawCommand;

    typedef struct DrawIndexedCommand
    {
        uint32_t index_count;
        uint32_t instance_count;
        uint32_t first_index;
        int32_t  vertex_offset;
        uint32_t first_instance;
    } DrawIndexedCommand;

    typedef struct CreateBufferInfo
    {
        uint64_t size;
        const void* data;
        MemoryUsage memory_usage;
    } CreateBufferInfo;

    typedef struct CreateIndexBufferInfo
    {
        uint64_t size;
        const void* data;
        MemoryUsage memory_usage;
        kege::IndexType index_type;
    } CreateIndexBufferInfo;

    typedef struct PushConstantBlock
    {
        uint32_t shader_stages;
        uint32_t offset;
        uint32_t size;
        const void* data;
    } PushConstantBlock;

    typedef enum DescriptorType : unsigned char
    {
        DESCRIPTOR_SAMPLER = 0,
        DESCRIPTOR_COMBINED_IMAGE_SAMPLER = 1,
        DESCRIPTOR_SAMPLED_IMAGE = 2,
        DESCRIPTOR_STORAGE_IMAGE = 3,
        DESCRIPTOR_UNIFORM_TEXEL_BUFFER = 4,
        DESCRIPTOR_STORAGE_TEXEL_BUFFER = 5,
        DESCRIPTOR_UNIFORM_BUFFER = 6,
        DESCRIPTOR_STORAGE_BUFFER = 7,
        DESCRIPTOR_UNIFORM_BUFFER_DYNAMIC = 8,
        DESCRIPTOR_STORAGE_BUFFER_DYNAMIC = 9,
        DESCRIPTOR_INPUT_ATTACHMENT = 10,
        DESCRIPTOR_MAX_ENUM = 11
    } DescriptorType;

    struct VertexAttribute
    {
        kege::Format format;
        uint32_t location;
        uint64_t offset;
        uint32_t binding;
    };
    typedef std::vector< kege::VertexAttribute > VertexAttributes;

    struct Vertex
    {
        kege::vec3 position;

        static VertexAttributes attribute()
        {
            return {{ kege::RGB32_FLOAT, 0, 0, 0 }};
        }
    };

    struct VertexPT
    {
        kege::vec3 position;
        kege::vec2 texcoord;

        static VertexAttributes attribute()
        {
            return {
                { kege::RGB32_FLOAT, 0, 0, 0 },
                { kege::RG32_FLOAT,  0, sizeof(kege::vec3), 0 },
            };
        }
    };

    struct VertexPN
    {
        kege::vec3 position;
        kege::vec3 normal;

        static VertexAttributes attribute()
        {
            return {
                { kege::RGB32_FLOAT, 0, 0, 0 },
                { kege::RGB32_FLOAT, 0, sizeof(kege::vec3), 0 },
            };
        }
    };

    struct VertexPC
    {
        kege::vec3 position;
        kege::vec4 color;

        static VertexAttributes attribute()
        {
            return {
                { kege::RGB32_FLOAT,  0, 0, 0 },
                { kege::RGBA32_FLOAT, 0, sizeof(kege::vec3), 0 },
            };
        }
    };

    struct VertexPNT
    {
        kege::vec3 position;
        kege::vec3 normal;
        kege::vec2 texcoord;

        static VertexAttributes attribute()
        {
            uint32_t size3 = sizeof(kege::vec3);
            return
            {
                { kege::RGB32_FLOAT, 0, 0, 0 },
                { kege::RGB32_FLOAT, 0, size3, 0 },
                { kege::RG32_FLOAT,  0, size3 + size3, 0 },
            };
        }
    };

    struct VertexPNC
    {
        kege::vec3 position;
        kege::vec3 normal;
        kege::vec4 color;

        static VertexAttributes attribute()
        {
            uint32_t size3 = sizeof(kege::vec3);
            return
            {
                { kege::RGB32_FLOAT,  0, 0, 0 },
                { kege::RGB32_FLOAT,  0, size3, 0 },
                { kege::RGBA32_FLOAT, 0, size3 + size3, 0 },
            };
        }
    };

    struct VertexPNTC
    {
        kege::vec3 position;
        kege::vec3 normal;
        kege::vec2 texcoord;
        kege::vec4 color;

        static VertexAttributes attribute()
        {
            uint32_t size3 = sizeof(kege::vec3);
            uint32_t size2 = sizeof(kege::vec2);
            return
            {
                { kege::RGB32_FLOAT,  0, 0, 0 },
                { kege::RGB32_FLOAT,  0, size3, 0 },
                { kege::RG32_FLOAT,   0, size3 + size3, 0 },
                { kege::RGBA32_FLOAT, 0, size3 + size3 + size2, 0 },
            };
        }
    };

}


namespace kege{namespace vk{

    class Device;
    class Shader;
    class Pipeline;
    class PipelineLayout;
    class DescriptorSet;
    class Framebuffer;
    class Image;
    class Sampler;
    class Buffer;
    class Swapchain;
    class CommandPool;
    class DescriptorPool;
    class CommandBuffer;
    class DescriptorAllocator;
    class DescriptorSetLayout;
    class Renderpass;

    class IndexBuffer;
    class VertexBuffer;
    class UniformBuffer;
    class StorageBuffer;
    class DrawCommandBuffer;
}}
#endif /* graphics_dependencies_hpp */
