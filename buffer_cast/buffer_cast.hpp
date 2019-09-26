/*
 * buffer_cast header implementation
 */

#include <cstring>
#include <array>
#include <type_traits>

#ifndef __BUFFER_CAST__
#define __BUFFER_CAST__

namespace dmv {

template<typename T, size_t size_ = 1>
class buffer_cast {
 public:
    buffer_cast() = delete;
    buffer_cast(const buffer_cast&) = delete;
    buffer_cast(buffer_cast&&) = default;
    buffer_cast& operator=(const buffer_cast&) = delete;
    buffer_cast& operator=(buffer_cast&&) = default;

    explicit buffer_cast(void* buffer) : type_cast_buffer_{0}, origin_buffer_(buffer)  {
        static_assert(size_, "buffer_cast cannot work with zero size");
        //static_assert(std::is_pointer<Z>::value, "buffer_cast can only receive pointers as parameter");
        //static_assert(std::is_trivially_copyable<Z>::value, "buffer_cast can only work with trivially copyable buffers");
        //static_assert(!std::is_const<Z>::value, "buffer type cannot work with const buffers");

        std::memcpy(type_cast_buffer_.data(), origin_buffer_, sizeof(type_cast_buffer_));
    }

    ~buffer_cast() {
        std::memcpy(origin_buffer_, type_cast_buffer_.data(), sizeof(type_cast_buffer_));
    }

    T& operator[](const size_t index) {
        return type_cast_buffer_.at(index);
    }

 private:
    std::array<T, size_> type_cast_buffer_;
    void* origin_buffer_;
};

}

#endif
