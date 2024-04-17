//
//  vk-device.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    void imageTransitionLayout( VkCommandBuffer command_buffer, VkImage image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout )
    {
        VkImageMemoryBarrier barrier{};
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;
        barrier.oldLayout = old_layout;
        barrier.newLayout = new_layout;
        barrier.image = image;

        VkPipelineStageFlags source_stage;
        VkPipelineStageFlags destination_stage;

        if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
        {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        }
        else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
        {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            source_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        }
        else
        {
            throw std::invalid_argument("unsupported layout transition!");
        }

        vkCmdPipelineBarrier
        (
             command_buffer,
             source_stage,
             destination_stage,
             0,
             0, nullptr,
             0, nullptr,
             1, &barrier
        );
    }

    bool operator ==( const vk::DescriptorSetLayoutObject& a, const vk::DescriptorSetLayoutObject& b )
    {
        if ( a.bindings.size() != b.bindings.size() )
        {
            return false;
        }

        for (int i=0; i<a.bindings.size(); i++ )
        {
            bool match =
            (
                a.bindings[ i ].descriptorCount == b.bindings[ i ].descriptorCount &&
                a.bindings[ i ].descriptorType == b.bindings[ i ].descriptorType &&
                a.bindings[ i ].binding == b.bindings[ i ].binding
            );

            if ( !match || a.names[ i ] != b.names[ i ] )
            {
                return false;
            }

        }
        return true;
    };

    uint64_t hashDescriptorSetLayoutBindings( uint64_t hash, const VkDescriptorSetLayoutBinding& binding, const kege::string& name )
    {
        uint32_t PRIME_A = 54059; /* a prime */
        uint32_t PRIME_B = 76963; /* another prime */
        //uint32_t PRIME_C = 86969; /* yet another prime */

        hash = (hash * PRIME_A) ^ (binding.binding         * PRIME_B);
        hash = (hash * PRIME_A) ^ (binding.descriptorType  * PRIME_B);
        hash = (hash * PRIME_A) ^ (binding.descriptorCount * PRIME_B);

        for ( const char * s = name.c_str(); *s; s++ )
        {
            hash = (hash * PRIME_A) ^ (*s * PRIME_B);
        }
        return hash;
    }

    uint64_t Device::getDescriptorSetLayoutBindingsSignature( const vk::DescriptorSetLayoutObject& object )
    {
        uint64_t signature = 0;
        for ( int i = 0; i < object.names.size(); i++ )
        {
            uint32_t* index = _descriptor_index_map.at( object.names[i] );
            if ( !index )
            {
                _descriptor_index_map.insert( object.names[i], _distinct_descriptor_counter );
                signature |= _distinct_descriptor_counter << 1;
                _distinct_descriptor_counter++;
            }
            else
            {
                signature |= *index << 1;
            }
        }
        return signature;
    }

    vk::DescriptorSetLayout* Device::createDescriptorSetLayout( const vk::DescriptorSetLayoutObject& descriptor_set_layout_object )
    {
        uint64_t signature = getDescriptorSetLayoutBindingsSignature( descriptor_set_layout_object );
        std::set< vk::PipelineLayout* >* pipeline_layout_set = &_pipeline_layout_sets[ signature ];
        kege::Ref< vk::DescriptorSetLayout > descriptor_set_layout = new vk::DescriptorSetLayout( this );
        if ( descriptor_set_layout->create( descriptor_set_layout_object, pipeline_layout_set ) != VK_SUCCESS )
        {
            KEGE_FATAL("Failed to create descriptor set layout!");
            return nullptr;
        }
        _descriptor_set_layouts[ signature ] = descriptor_set_layout;
        return descriptor_set_layout.ref();
    }

    vk::DescriptorSetLayout* Device::getDescriptorSetLayout( const vk::DescriptorSetLayoutObject& descriptor_set_layout_object )
    {
        uint64_t signature = getDescriptorSetLayoutBindingsSignature( descriptor_set_layout_object );
        DescriptorSetLayoutMap::iterator m = _descriptor_set_layouts.find( signature );
        if ( m != _descriptor_set_layouts.end() )
        {
            return m->second.ref();
        }
        return nullptr;
    }

    kege::Ref< kege::DrawIndexedCommandBuffer > Device::createDrawIndexedCommandBuffer( const kege::DrawIndexedCommandBuffer::CreateInfo& info )
    {
        kege::Ref< vk::DrawIndexedCommandBuffer > buffer =  new vk::DrawIndexedCommandBuffer( this );
        if ( buffer->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return buffer;
    }

    kege::Ref< kege::DrawCommandBuffer > Device::createDrawCommandBuffer( const kege::DrawCommandBuffer::CreateInfo& info )
    {
        kege::Ref< vk::DrawCommandBuffer > buffer =  new vk::DrawCommandBuffer( this );
        if ( buffer->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return buffer;
    }

    kege::Ref< kege::Framebuffer > Device::createFramebuffer( const std::vector< kege::Framebuffer::Attachment >& attachment )
    {
        kege::Ref< vk::Framebuffer > framebuffer =  new vk::Framebuffer( this );
        if ( framebuffer->construct( attachment ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return framebuffer.ref();
    }

    kege::Ref< kege::PipelineLayout > Device::createPipelineLayout( const kege::PipelineLayout::CreateInfo& info )
    {
        kege::Ref< vk::PipelineLayout > pipeline_layout = new vk::PipelineLayout;
        if( vk::PipelineLayout::create( this, info, *pipeline_layout) != VK_SUCCESS )
        {
            return nullptr;
        }
        return pipeline_layout.ref();
    }

    kege::Ref< kege::Pipeline > Device::createPipeline( const kege::Pipeline::CreateInfo& info )
    {
        kege::Ref< vk::Pipeline > pipeline = new vk::Pipeline();
        
        if ( info.pipeline_layout->vulkan()->pipelineBindPoint() == VK_PIPELINE_BIND_POINT_GRAPHICS )
        {
            if ( vk::Pipeline::createGraphicsPipeline( this, info, *pipeline ) != VK_SUCCESS )
            {
                return nullptr;
            }
        }
        else if ( info.pipeline_layout->vulkan()->pipelineBindPoint() == VK_PIPELINE_BIND_POINT_COMPUTE )
        {
            if ( vk::Pipeline::createComputePipeline( this, info, *pipeline ) != VK_SUCCESS )
            {
                return nullptr;
            }
        }

        return pipeline.ref();
    }

    kege::Ref< kege::CommandBuffer > Device::createCommandBuffer( const kege::CommandBuffer::CreateInfo& info )
    {
        kege::Ref< vk::CommandBuffer > cmb = new vk::CommandBuffer( this );
        if ( cmb->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        };
        return cmb.ref();
    }

    kege::Ref< kege::Renderpass > Device::createRenderpass( const kege::Renderpass::CreateInfo& info )
    {
        return nullptr;
    }
    
    kege::Ref< kege::Shader > Device::createShaderModule( const kege::Shader::CreateInfo& info )
    {
        kege::Ref< vk::Shader > shader = new vk::Shader( this );
        if ( shader->construct( info ) != VK_SUCCESS )
        {
            KEGE_FATAL("Device::createShaderModule() : failed to create shader!" );
            return nullptr;
        }
        return shader.ref();
    }

    kege::Ref< kege::Sampler > Device::createSampler( const kege::Sampler::CreateInfo& info )
    {
        kege::Ref< vk::Sampler > sampler = new vk::Sampler( this );
        if( sampler->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return sampler.ref();
    }

    kege::Ref< kege::VertexBuffer > Device::createVertexBuffer( const kege::CreateBufferInfo& info )
    {
        kege::Ref< vk::VertexBuffer > buffer = new vk::VertexBuffer( this );
        if ( buffer->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return buffer.ref();
    }

    kege::Ref< kege::IndexBuffer > Device::createIndexBuffer( const kege::CreateIndexBufferInfo& info )
    {
        kege::Ref< vk::IndexBuffer > buffer = new vk::IndexBuffer( this );
        if ( buffer->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return buffer.ref();
    }

    kege::Ref< kege::StorageBuffer > Device::createStorageBuffer( const kege::CreateBufferInfo& info )
    {
        kege::Ref< vk::StorageBuffer > buffer = new vk::StorageBuffer( this );
        if ( buffer->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return buffer.ref();
    }

    kege::Ref< kege::UniformBuffer > Device::createUniformBuffer( const kege::CreateBufferInfo& info )
    {
        kege::Ref< vk::UniformBuffer > buffer = new vk::UniformBuffer( this );
        if ( buffer->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return buffer.ref();
    }

    kege::Ref< kege::Image2d > Device::createImage2d( const kege::Image2d::CreateInfo& info )
    {
        kege::Ref< vk::Image2d > image = new vk::Image2d( this );
        if ( image->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }

        return image.ref();
    }

    kege::Ref< kege::Image3d > Device::createImage3d( const kege::Image3d::CreateInfo& info )
    {
        kege::Ref< vk::Image3d > image = new vk::Image3d( this );
        if ( image->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return image.ref();
    }

    kege::Ref< kege::Image1dArray > Device::createImage1dArray( const kege::Image1dArray::CreateInfo& info )
    {
        kege::Ref< vk::Image1dArray > image = new vk::Image1dArray( this );
        if ( image->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return image.ref();
    }

    kege::Ref< kege::Image2dArray > Device::createImage2dArray( const kege::Image2dArray::CreateInfo& info )
    {
        kege::Ref< vk::Image2dArray > image = new vk::Image2dArray( this );
        if ( image->construct( info ) != VK_SUCCESS )
        {
            return nullptr;
        }
        return image.ref();
    }

    kege::Ref< kege::ShaderResource > Device::createShaderResource()
    {
        return new vk::DescriptorSet( this );
    }

    void Device::copyBufferToImage( const vk::Buffer& buffer, vk::Image& image )
    {
        // allocate a single command buffer from the command pool
        VkCommandBuffer command_buffer;
        _command_pools[ kege::TRANSFER_QUEUE ].allocateCommandBuffers( VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1, &command_buffer );

        // begin recording commands into the command buffer
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer( command_buffer, &begin_info );

        imageTransitionLayout
        (
            command_buffer,
            image.handle,
            image.format,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
        );

        // copy buffer data to image
        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;
        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1;
        region.imageOffset = {0, 0, 0};
        region.imageExtent = image.extend;
        vkCmdCopyBufferToImage( command_buffer, buffer.handle, image.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region );

        // To be able to start sampling from the texture image in the shader, we need to prepare it for shader access
        imageTransitionLayout
        (
            command_buffer, image.handle, image.format,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        );

        vkEndCommandBuffer( command_buffer );

        // submit the command buffer to the graphics queue for execution
        VkSubmitInfo submit_info = {};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &command_buffer;
        vkQueueSubmit( _transfer_queue, 1, &submit_info, VK_NULL_HANDLE );
        vkQueueWaitIdle( _transfer_queue );

        // free the command buffer and command pool
        _command_pools[ kege::TRANSFER_QUEUE ].freeCommandBuffer( 1, &command_buffer );
    }

    void Device::copyBuffer( vk::Buffer& dst, const vk::Buffer& src )
    {
        // allocate a single command buffer from the command pool
        VkCommandBuffer command_buffer;
        _command_pools[ kege::TRANSFER_QUEUE ].allocateCommandBuffers( VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1, &command_buffer );

        // begin recording commands into the command buffer
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer( command_buffer, &begin_info );

        // record commands here
        VkBufferCopy copy_region{};
        copy_region.srcOffset = 0; // Optional
        copy_region.dstOffset = 0; // Optional
        copy_region.size = src.size;
        vkCmdCopyBuffer( command_buffer, src.handle, dst.handle, 1, &copy_region );

        // end recording commands into the command buffer
        vkEndCommandBuffer( command_buffer );

        // submit the command buffer to the graphics queue for execution
        VkSubmitInfo submit_info = {};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &command_buffer;
        vkQueueSubmit( _transfer_queue, 1, &submit_info, VK_NULL_HANDLE );
        vkQueueWaitIdle( _transfer_queue );

        // free the command buffer and command pool
        _command_pools[ kege::TRANSFER_QUEUE ].freeCommandBuffer( 1, &command_buffer );
    }


    int Device::init( kege::Ref< kege::RenderWindow >& window )
    {
        _window = window;

        if ( KEGE_VULKAN_VALIDATION_LAYER_ENABLES )
        {
            _validation_layers.push_back( new vk::Debugger );
        }

        if( _instance.init( _validation_layers ) != VK_SUCCESS )
        {
            return 0;
        }

        if ( glfwCreateWindowSurface( _instance.handle(), window->handle(), nullptr, &_surface ) != VK_SUCCESS )
        {
            return 0;
        }

        if ( _physical_device.selectPhysicalDevice( _instance, _surface ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong while selecting a vk-physical-device");
            return 0;
        }

        if ( createLogicalDevice( _instance, _physical_device ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong in vk::Device::createLogicalDevice().");
            return 0;
        }

        _command_pools.resize( 4 );
        if ( vk::CommandPool::create( this, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, kege::GRAPHICS_QUEUE, _command_pools[ kege::GRAPHICS_QUEUE ] ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong in vk::CommandPool::create().");
            return 0;
        }

        if ( vk::CommandPool::create( this, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, kege::PRESENT_QUEUE, _command_pools[ kege::PRESENT_QUEUE ] ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong in vk::CommandPool::create().");
            return 0;
        }

        if ( vk::CommandPool::create( this, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, kege::TRANSFER_QUEUE, _command_pools[ kege::TRANSFER_QUEUE ] ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong in vk::CommandPool::create().");
            return 0;
        }
        
        if ( vk::CommandPool::create( this, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, kege::COMPUTE_QUEUE, _command_pools[ kege::COMPUTE_QUEUE ] ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong in vk::CommandPool::create().");
            return 0;
        }

        if ( _render_context.init( this ) != VK_SUCCESS )
        {
            KEGE_ERROR("something when wrong while initalizing vk::RenderContext.");
            return 0;
        }

        const vk::DeviceQueueFamily& device_queue_family = getPhysicalDevice().deviceQueueFamily();
        vkGetDeviceQueue( getLogicalDevice(), device_queue_family[ kege::TRANSFER_QUEUE ].value(), 0, &_transfer_queue );
        return 1;
    }

    vk::CommandPool& Device::getCommandPool( uint32_t queue_index )
    {
        return _command_pools[ queue_index ];
    }
    
    kege::RenderContext& Device::getRenderContext()
    {
        return _render_context;
    }

    vk::PhysicalDevice& Device::getPhysicalDevice()
    {
        return _physical_device;
    }

    const VkDevice Device::getLogicalDevice()const
    {
        return _device;
    }

    kege::RenderWindow* Device::window()
    {
        return _window.ref();
    }

    VkSurfaceKHR Device::getSurface()
    {
        return _surface;
    }


    VkResult Device::createLogicalDevice( vk::Instance& instance, vk::PhysicalDevice& physical_device )
    {
        const vk::DeviceQueueFamily& device_queue_family = physical_device.deviceQueueFamily();
        std::set< uint32_t > unique_queue_families =
        {
            device_queue_family[ kege::GRAPHICS_QUEUE ].value(),
            device_queue_family[ kege::COMPUTE_QUEUE  ].value(),
            device_queue_family[ kege::PRESENT_QUEUE  ].value(),
            device_queue_family[ kege::TRANSFER_QUEUE ].value()
        };

        float queue_priority = 1.0f;
        std::vector< VkDeviceQueueCreateInfo > queue_create_infos;
        for ( uint32_t queue_family : unique_queue_families )
        {
            VkDeviceQueueCreateInfo info{};
            info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            info.queueFamilyIndex = queue_family;
            info.queueCount = 1;
            info.pQueuePriorities = &queue_priority;
            queue_create_infos.push_back(info);
        }

        VkPhysicalDeviceFeatures device_features{};
        device_features.fillModeNonSolid    = VK_TRUE; // Enable the fillModeNonSolid feature
        device_features.tessellationShader  = VK_TRUE; // Enable the tessellationShader feature
        device_features.imageCubeArray      = VK_TRUE;
        device_features.multiDrawIndirect   = VK_TRUE;
        //device_features.geometryShader      = VK_TRUE; // Enable the geometryShader feature

        VkDeviceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount = static_cast<uint32_t>( queue_create_infos.size() );
        create_info.pQueueCreateInfos = queue_create_infos.data();
        create_info.pEnabledFeatures = &device_features;
        create_info.enabledExtensionCount = static_cast<uint32_t>( physical_device.deviceExtensions().size() );
        create_info.ppEnabledExtensionNames = physical_device.deviceExtensions().data();

        if ( KEGE_VULKAN_VALIDATION_LAYER_ENABLES )
        {
            create_info.enabledLayerCount = static_cast<uint32_t>( instance.validationLayerNames().size());
            create_info.ppEnabledLayerNames = instance.validationLayerNames().data();
        }
        else
        {
            create_info.enabledLayerCount = 0;
        }

        return vkCreateDevice( physical_device.handle(), &create_info, nullptr, &_device );
    }

    void Device::waitIdle()
    {
        vkDeviceWaitIdle( _device );
    }

    Device::~Device()
    {
        _command_pools.clear();
        _descriptor_set_layouts.clear();
        
        _render_context.uninit();
        if ( _device != nullptr )
        {
            vkDestroyDevice( _device, nullptr );
            _device = VK_NULL_HANDLE;
        }

        if ( _surface != nullptr )
        {
            vkDestroySurfaceKHR( _instance.handle(), _surface, nullptr );
            _surface = VK_NULL_HANDLE;
        }

        _validation_layers.clear();
        _instance.uninit();
    }

    Device::Device()
    :   _device( VK_NULL_HANDLE )
    ,   _distinct_descriptor_counter( 0 )
    {
    }

}}
