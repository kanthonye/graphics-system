//
//  vk-image.hpp
//  new-engine
//
//  Created by Kenneth Esdaile on 1/3/24.
//

#ifndef kege_graphics_vk_image_hpp
#define kege_graphics_vk_image_hpp

#include "../vulkan/vk.hpp"

namespace kege{namespace vk{

    struct Image
    {
        VkDeviceMemory memory; ///< The handle of the Vulkan device memory associated with the image.
        VkImageView view;      ///< The handle of the Vulkan image view associated with the image.
        VkImage handle;        ///< The handle of the Vulkan image.
        VkFormat format;       ///< The format of the image.
        VkExtent3D extend;     ///< The extent of the image (width, height, depth).
        uint32_t layers;
    };

    /**
     * @brief Creates a Vulkan image.
     * @return VK_SUCCESS if the image creation is successful, otherwise an error code.
     */
    VkResult createImage
    (
        vk::Device* device,
        VkImageType image_type,
        VkFormat format,
        VkExtent3D extent,
        uint32_t mip_levels,
        uint32_t array_layers,
        VkImageViewType view_type,
        VkImageAspectFlagBits aspect_type,
        VkImageUsageFlags usage,
        vk::Image& image,
        uint64_t size,
        const void* data
    );

    /**
     * @brief Creates a Vulkan image view.
     *
     * @param device_handle The Vulkan device associated with the image view.
     * @param image_format The format of the image.
     * @param view_type The type of image view (e.g., 2D, 3D, cube map).
     * @param aspect_flags Flags specifying which aspects of the image are included in the view.
     * @param image The handle of the Vulkan image.
     * @param handle Reference to a VkImageView object to be filled with the created image view.
     *
     * @return VK_SUCCESS if the image view creation is successful, otherwise an error code.
     */
    VkResult createView
    (  VkDevice device_handle
     , VkFormat image_format
     , VkImageViewType view_type
     , VkImageAspectFlags aspect_flags
     , VkImage image
     , VkImageView& handle
    );
}}



namespace kege{namespace vk{

    /**
     * @brief Represents a Vulkan image object.
     *
     * This class encapsulates a Vulkan image, providing a convenient interface for
     * creating, managing, and using image resources in Vulkan applications.
     */
    class Image2d : public kege::Image2d
    {
    public:

        /**
         * @brief Creates a Vulkan image using information provided by a kege::Image::CreateInfo structure.
         *
         * @param info Reference to a kege::Image::CreateInfo structure containing image creation information.
         *
         * @return VK_SUCCESS if the image creation is successful, otherwise an error code.
         */
        VkResult construct( const kege::Image2d::CreateInfo& info );

        void getDescriptorBufferInfo( void* data );

        /**
         * @brief Retrieves a pointer to the Vulkan image handle.
         *
         * @return A pointer to the Vulkan image handle.
         */
        const vk::Image* vulkan()const;

        /**
         * @brief Retrieves a mutable pointer to the Vulkan image handle.
         *
         * @return A mutable pointer to the Vulkan image handle.
         */
        vk::Image* vulkan();

        /**
         * @brief Retrieves the Vulkan device associated with the image.
         *
         * @return Pointer to the Vulkan device.
         */
        vk::Device* device();

        /**
         * @brief Retrieves the number of array layer of this image.
         *
         * @return The total image layers.
         */
        uint32_t layers()const;

        /**
         * @brief Retrieves the height of the image.
         *
         * @return The height of the image.
         */
        uint32_t height()const;

        /**
         * @brief Retrieves the width of the image.
         *
         * @return The width of the image.
         */
        uint32_t width()const;

        /**
         * @brief Retrieves the depth of the image.
         *
         * @return The depth of the image.
         */
        uint32_t depth()const;

        /**
         * @brief Constructs an Image object.
         *
         * @param device Pointer to the Vulkan device associated with the image.
         * @param image The Vulkan image parameters.
         */
        Image2d( vk::Device* device, const vk::Image& image );

        /**
         * @brief Destroys the Image object and releases associated Vulkan resources.
         */
        ~Image2d();

        /**
         * @brief Constructs an Image object.
         */
        Image2d( vk::Device* device );

    private:

        vk::Image _params;
        vk::Device* _device;
    };

}}



namespace kege{namespace vk{
    /**
     * @brief Represents a Vulkan image object.
     *
     * This class encapsulates a Vulkan image, providing a convenient interface for
     * creating, managing, and using image resources in Vulkan applications.
     */
    class Image2dArray: public kege::Image2dArray
    {
    public:

        /**
         * @brief Creates a Vulkan image using information provided by a kege::Image::CreateInfo structure.
         *
         * @param info Reference to a kege::Image::CreateInfo structure containing image creation information.
         *
         * @return VK_SUCCESS if the image creation is successful, otherwise an error code.
         */
        VkResult construct( const kege::Image2dArray::CreateInfo& info );

        void getDescriptorBufferInfo( void* data );

        /**
         * @brief Retrieves a pointer to the Vulkan image handle.
         *
         * @return A pointer to the Vulkan image handle.
         */
        const vk::Image* vulkan()const;

        /**
         * @brief Retrieves a mutable pointer to the Vulkan image handle.
         *
         * @return A mutable pointer to the Vulkan image handle.
         */
        vk::Image* vulkan();

        /**
         * @brief Retrieves the Vulkan device associated with the image.
         *
         * @return Pointer to the Vulkan device.
         */
        vk::Device* device();

        /**
         * @brief Retrieves the number of array layer of this image.
         *
         * @return The total image layers.
         */
        uint32_t layers()const;

        /**
         * @brief Retrieves the height of the image.
         *
         * @return The height of the image.
         */
        uint32_t height()const;

        /**
         * @brief Retrieves the width of the image.
         *
         * @return The width of the image.
         */
        uint32_t width()const;

        /**
         * @brief Retrieves the depth of the image.
         *
         * @return The depth of the image.
         */
        uint32_t depth()const;

        /**
         * @brief Constructs an Image object.
         */
        Image2dArray( vk::Device* device );

        /**
         * @brief Destroys the Image object and releases associated Vulkan resources.
         */
        ~Image2dArray();

    private:

        vk::Image _params;
        vk::Device* _device;
    };

}}



namespace kege{namespace vk{
    /**
     * @brief Represents a Vulkan image object.
     *
     * This class encapsulates a Vulkan image, providing a convenient interface for
     * creating, managing, and using image resources in Vulkan applications.
     */
    class Image3d : public kege::Image3d
    {
    public:

        /**
         * @brief Creates a Vulkan image using information provided by a kege::Image::CreateInfo structure.
         *
         * @param info Reference to a kege::Image::CreateInfo structure containing image creation information.
         *
         * @return VK_SUCCESS if the image creation is successful, otherwise an error code.
         */
        VkResult construct( const kege::Image3d::CreateInfo& info );

        void getDescriptorBufferInfo( void* data );

        /**
         * @brief Retrieves a pointer to the Vulkan image handle.
         *
         * @return A pointer to the Vulkan image handle.
         */
        const vk::Image* vulkan()const;

        /**
         * @brief Retrieves a mutable pointer to the Vulkan image handle.
         *
         * @return A mutable pointer to the Vulkan image handle.
         */
        vk::Image* vulkan();

        /**
         * @brief Retrieves the Vulkan device associated with the image.
         *
         * @return Pointer to the Vulkan device.
         */
        vk::Device* device();

        /**
         * @brief Retrieves the number of array layer of this image.
         *
         * @return The total image layers.
         */
        uint32_t layers()const;

        /**
         * @brief Retrieves the height of the image.
         *
         * @return The height of the image.
         */
        uint32_t height()const;

        /**
         * @brief Retrieves the width of the image.
         *
         * @return The width of the image.
         */
        uint32_t width()const;

        /**
         * @brief Retrieves the depth of the image.
         *
         * @return The depth of the image.
         */
        uint32_t depth()const;

        /**
         * @brief Constructs an Image object.
         */
        Image3d( vk::Device* device );

        /**
         * @brief Destroys the Image object and releases associated Vulkan resources.
         */
        ~Image3d();

    private:

        vk::Image _params;
        vk::Device* _device;
    };

}}



namespace kege{namespace vk{
    /**
     * @brief Represents a Vulkan image object.
     *
     * This class encapsulates a Vulkan image, providing a convenient interface for
     * creating, managing, and using image resources in Vulkan applications.
     */
    class Image1dArray : public kege::Image1dArray
    {
    public:

        /**
         * @brief Creates a Vulkan image using information provided by a kege::Image::CreateInfo structure.
         *
         * @param info Reference to a kege::Image::CreateInfo structure containing image creation information.
         *
         * @return VK_SUCCESS if the image creation is successful, otherwise an error code.
         */
        VkResult construct( const kege::Image1dArray::CreateInfo& info );

        void getDescriptorBufferInfo( void* data );

        /**
         * @brief Retrieves a pointer to the Vulkan image handle.
         *
         * @return A pointer to the Vulkan image handle.
         */
        const vk::Image* vulkan()const;

        /**
         * @brief Retrieves a mutable pointer to the Vulkan image handle.
         *
         * @return A mutable pointer to the Vulkan image handle.
         */
        vk::Image* vulkan();

        /**
         * @brief Retrieves the Vulkan device associated with the image.
         *
         * @return Pointer to the Vulkan device.
         */
        vk::Device* device();

        /**
         * @brief Retrieves the number of array layer of this image.
         *
         * @return The total image layers.
         */
        uint32_t layers()const;

        /**
         * @brief Retrieves the height of the image.
         *
         * @return The height of the image.
         */
        uint32_t height()const;

        /**
         * @brief Retrieves the width of the image.
         *
         * @return The width of the image.
         */
        uint32_t width()const;

        /**
         * @brief Retrieves the depth of the image.
         *
         * @return The depth of the image.
         */
        uint32_t depth()const;

        /**
         * @brief Constructs an Image object.
         */
        Image1dArray( vk::Device* device );

        /**
         * @brief Destroys the Image object and releases associated Vulkan resources.
         */
        ~Image1dArray();

    private:

        vk::Image _params;
        vk::Device* _device;
    };

}}


#endif /* kege_graphics_vk_image_hpp */
