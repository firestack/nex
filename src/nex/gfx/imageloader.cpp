#include <nex/gfx/imageloader.h>
#include <nex/system/instream.h>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <cstring>
#include <cctype>
#include <iostream>

namespace
{
    // Convert a string to lower case
    std::string toLower(std::string str)
    {
        for (std::string::iterator i = str.begin(); i != str.end(); ++i)
            *i = static_cast<char>(std::tolower(*i));
        return str;
    }

    // stb_image callbacks that operate on a sf::InputStream
    int read(void* user, char* data, int size)
    {
        nx::InStream* stream = static_cast<nx::InStream*>(user);
        return static_cast<int>(stream->read(data, size));
    }
    void skip(void* user, int size)
    {
        nx::InStream* stream = static_cast<nx::InStream*>(user);
        stream->seek(stream->tell() + size);
    }
    int eof(void* user)
    {
        nx::InStream* stream = static_cast<nx::InStream*>(user);
        return stream->tell() >= stream->size();
    }
}

namespace nx
{
namespace priv
{

ImageLoader& ImageLoader::getInstance()
{
    static ImageLoader instance;

    return instance;
}

ImageLoader::ImageLoader()
{ }

ImageLoader::~ImageLoader()
{ }

bool ImageLoader::loadImageFromFile(const std::string& filename, std::vector<uint8>& pixels, vec2u& size)
{
    // Clear the array (just in case)
    pixels.clear();

    // Load the image and get a pointer to the pixels in memory
    int width, height, channels;
    unsigned char* ptr = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (ptr && width && height)
    {
        // Assign the image properties
        size.x = width;
        size.y = height;

        // Copy the loaded pixels to the pixel buffer
        pixels.resize(width * height * 4);
        memcpy(&pixels[0], ptr, pixels.size());

        // Free the loaded pixels (they are now in our own pixel buffer)
        stbi_image_free(ptr);

        return true;
    }
    else
    {
        // Error, failed to load the image
        std::cout << "Failed to load image \"" << filename << "\". Reason: " << stbi_failure_reason() << std::endl;

        return false;
    }
}

bool ImageLoader::loadImageFromMemory(const void* data, std::size_t dataSize, std::vector<uint8>& pixels, vec2u& size)
{
    // Check input parameters
    if (data && dataSize)
    {
        // Clear the array (just in case)
        pixels.clear();

        // Load the image and get a pointer to the pixels in memory
        int width, height, channels;
        const unsigned char* buffer = static_cast<const unsigned char*>(data);
        unsigned char* ptr = stbi_load_from_memory(buffer, static_cast<int>(dataSize), &width, &height, &channels, STBI_rgb_alpha);

        if (ptr && width && height)
        {
            // Assign the image properties
            size.x = width;
            size.y = height;

            // Copy the loaded pixels to the pixel buffer
            pixels.resize(width * height * 4);
            memcpy(&pixels[0], ptr, pixels.size());

            // Free the loaded pixels (they are now in our own pixel buffer)
            stbi_image_free(ptr);

            return true;
        }
        else
        {
            // Error, failed to load the image
            std::cout << "Failed to load image from memory. Reason: " << stbi_failure_reason() << std::endl;

            return false;
        }
    }
    else
    {
        std::cout << "Failed to load image from memory, no data provided" << std::endl;
        return false;
    }
}

bool ImageLoader::loadImageFromStream(InStream& stream, std::vector<uint8>& pixels, vec2u& size)
{
    // Clear the array (just in case)
    pixels.clear();

    // Make sure that the stream's reading position is at the beginning
    stream.seek(0);

    // Setup the stb_image callbacks
    stbi_io_callbacks callbacks;
    callbacks.read = &read;
    callbacks.skip = &skip;
    callbacks.eof  = &eof;

    // Load the image and get a pointer to the pixels in memory
    int width, height, channels;
    unsigned char* ptr = stbi_load_from_callbacks(&callbacks, &stream, &width, &height, &channels, STBI_rgb_alpha);

    if (ptr && width && height)
    {
        // Assign the image properties
        size.x = width;
        size.y = height;

        // Copy the loaded pixels to the pixel buffer
        pixels.resize(width * height * 4);
        memcpy(&pixels[0], ptr, pixels.size());

        // Free the loaded pixels (they are now in our own pixel buffer)
        stbi_image_free(ptr);

        return true;
    }
    else
    {
        // Error, failed to load the image
        std::cout << "Failed to load image from stream. Reason: " << stbi_failure_reason() << std::endl;

        return false;
    }
}

bool ImageLoader::saveImageToFile(const std::string& filename, const std::vector<uint8>& pixels, const vec2u& size)
{
    // Make sure the image is not empty
    if (!pixels.empty() && (size.x > 0) && (size.y > 0))
    {
        // Deduce the image type from its extension
        if (filename.size() > 3)
        {
            // Extract the extension
            std::string extension = toLower(filename.substr(filename.size() - 3));

            if (extension == "bmp")
            {
                // BMP format
                if (stbi_write_bmp(filename.c_str(), size.x, size.y, 4, &pixels[0]))
                    return true;
            }
            else if (extension == "tga")
            {
                // TGA format
                if (stbi_write_tga(filename.c_str(), size.x, size.y, 4, &pixels[0]))
                    return true;
            }
            else if (extension == "png")
            {
                // PNG format
                if (stbi_write_png(filename.c_str(), size.x, size.y, 4, &pixels[0], 0))
                    return true;
            }
            else if (extension == "jpg")
            {
                // JPG format
                //if (writeJpg(filename, pixels, size.x, size.y))
                    //return true;
            }
        }
    }

    std::cout << "Failed to save image \"" << filename << "\"" << std::endl;
    return false;
}

} // namespace priv
} // namespace nx
