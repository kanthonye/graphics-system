//
//  vk-sampler.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/4/24.
//

#include "vk-core.hpp"

namespace kege{namespace vk{

    VkResult Sampler::construct( kege::Sampler::CreateInfo create_info )
    {
        VkSamplerCreateInfo sampler_info{};
        sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;

        sampler_info.magFilter = getFilter( create_info.min );
        sampler_info.minFilter = getFilter( create_info.mag );

        sampler_info.addressModeU = getAddressMode( create_info.x );
        sampler_info.addressModeV = getAddressMode( create_info.y );
        sampler_info.addressModeW = getAddressMode( create_info.z );

        sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        sampler_info.unnormalizedCoordinates = VK_FALSE;

        sampler_info.compareEnable = VK_FALSE;
        sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;

        sampler_info.mipmapMode = (create_info.mag == kege::LINEAR) ? VK_SAMPLER_MIPMAP_MODE_LINEAR: VK_SAMPLER_MIPMAP_MODE_NEAREST;
        sampler_info.mipLodBias = 0.0f;
        sampler_info.minLod = 0.0f;
        sampler_info.maxLod = 0.0f;

        sampler_info.anisotropyEnable = VK_FALSE;
        sampler_info.maxAnisotropy = _device->getPhysicalDevice().properties().limits.maxSamplerAnisotropy;
        /* The maxAnisotropy field limits the amount of texel samples that can be used to calculate the
        final color. A lower value results in better performance, but lower quality results. To
        figure out which value we can use, we need to retrieve the properties of the physical device.
        */
        VkResult result = vkCreateSampler( _device->getLogicalDevice(), &sampler_info, nullptr, &_handle );
        if ( result != VK_SUCCESS )
        {
            KEGE_ERROR( "%s: failed to create texture sampler!", vk::getError( result ) );
            return result;
        }
        return result;
    }

    VkSamplerAddressMode Sampler::getAddressMode( kege::Wrapping wrap )
    {
        switch ( wrap )
        {
            case kege::REPEAT:                return VK_SAMPLER_ADDRESS_MODE_REPEAT;
            case kege::MIRRORED_REPEAT:       return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
            case kege::CLAMP_TO_EDGE:         return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            case kege::CLAMP_TO_BORDER:       return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
            case kege::MIRROR_CLAMP_TO_EDGE:  return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
            default: break;
        }
        return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    }

    VkFilter Sampler::getFilter( kege::Filter filter )
    {
        switch ( filter )
        {
            case kege::LINEAR:  return VK_FILTER_LINEAR;
            case kege::NEAREST: return VK_FILTER_NEAREST;
            case kege::CUBIC:   return VK_FILTER_CUBIC_IMG;
            default: break;
        }
        return VK_FILTER_LINEAR;
    }

    void Sampler::getDescriptorBufferInfo( void* data )
    {
        VkDescriptorImageInfo* info = (VkDescriptorImageInfo*) data;
        info->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        info->sampler = _handle;
    }

    const vk::Sampler* Sampler::vulkan()const
    {
        return this;
    }
    
    vk::Sampler* Sampler::vulkan()
    {
        return this;
    }

    const VkSampler Sampler::handle()const
    {
        return _handle;
    }

    Sampler::~Sampler()
    {
        if ( _handle != VK_NULL_HANDLE )
        {
            _device->waitIdle();
            vkDestroySampler( _device->getLogicalDevice(), _handle, nullptr );
            _handle = VK_NULL_HANDLE;
        }
    }

    Sampler::Sampler(vk::Device* device)
    :   _handle( VK_NULL_HANDLE )
    ,   _device( device )
    {}

}}
