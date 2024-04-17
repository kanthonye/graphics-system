//
//  Device.cpp
//  new-engine
//
//  Created by Kenneth Esdaile on 12/30/23.
//

#include "../../../graphics/devices/vulkan/vk-core.hpp"

namespace kege
{
    Device* Device::create()
    {
        return new vk::Device();
    }

    Device& Device::operator =(const kege::Device& other ){ return *this; }
    Device::Device(const kege::Device& other ){}
    Device:: ~Device(){}
    Device::Device(){}

}
