//
//  vk-descriptor-writer.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/1/24.
//

#ifndef kege_graphics_vk_descriptor_writer_hpp
#define kege_graphics_vk_descriptor_writer_hpp

#include "../vulkan/vk.hpp"

//namespace kege{namespace vk{
//
//    /**
//     * @brief Helper class for writing descriptor sets.
//     *
//     * This class provides methods for writing descriptor sets, managing descriptor buffer and image information,
//     * and integrating uniform layouts in Vulkan applications.
//     */
//    class DescriptorWriter
//    {
//    public:
//
//        /**
//         * @brief Retrieves the const reference to the vector of write descriptor sets.
//         *
//         * @return The const reference to the vector of write descriptor sets.
//         */
//        const std::vector< VkWriteDescriptorSet >& getWriteDescriptorSets()const;
//
//        /**
//         * @brief Retrieves the reference to the vector of write descriptor sets.
//         *
//         * @return The reference to the vector of write descriptor sets.
//         */
//        std::vector< VkWriteDescriptorSet >& getWriteDescriptorSets();
//
//        /**
//         * @brief Writes a descriptor set for a buffer.
//         *
//         * @param binding Pointer to the uniform binding.
//         */
//        void writeDescriptorSetBuffer( const kege::UniformBinding* binding );
//
//        /**
//         * @brief Writes a descriptor set for an image.
//         *
//         * @param binding Pointer to the uniform binding.
//         */
//        void writeDescriptorSetImage( const kege::UniformBinding* binding );
//
//        /**
//         * @brief Integrates a uniform layout.
//         *
//         * @param asset Pointer to the uniform layout.
//         */
//        void integrateUniformLayout( const kege::UniformLayout* asset );
//
//        /**
//         * @brief Creates a new descriptor buffer info.
//         *
//         * @param n Number of buffer infos to create.
//         * @return Pointer to the new descriptor buffer info.
//         */
//        VkDescriptorBufferInfo* newDescriptorBufferInfo( uint32_t n );
//
//        /**
//         * @brief Creates a new descriptor image info.
//         *
//         * @param n Number of image infos to create.
//         * @return Pointer to the new descriptor image info.
//         */
//        VkDescriptorImageInfo* newDescriptorImageInfo( uint32_t n );
//
//        /**
//         * @brief Creates a new descriptor write set.
//         *
//         * @return Pointer to the new descriptor write set.
//         */
//        VkWriteDescriptorSet* newDescriptorWriteSet();
//
//        /**
//         * @brief Conversion operator to bool.
//         *
//         * @return True if the DescriptorWriter object is valid; false otherwise.
//         */
//        operator bool()const;
//
//        /**
//         * @brief Constructs a DescriptorWriter object.
//         *
//         * @param layout Pointer to the uniform layout.
//         */
//        DescriptorWriter( const kege::UniformLayout* layout );
//
//    private:
//
//        std::vector< VkWriteDescriptorSet > _write_descriptor_sets;
//        std::array<VkDescriptorBufferInfo, 32> _descriptor_buffer_infos;
//        std::array<VkDescriptorImageInfo, 32> _descriptor_image_infos;
//        uint32_t _buffer_info_count;
//        uint32_t _image_info_count;
//    };
//
//}}
#endif /* kege_graphics_vk_descriptor_writer_hpp */
