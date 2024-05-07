// FlagManager.hpp

#pragma once

namespace flags {

    template<typename flagtype, typename cast_type = unsigned int>
    class FlagManager {
    public:
        static void add(flagtype& flags, const flagtype& add_flags);
        static void add(flagtype& flags, const unsigned char add_flag);
        static void rem(flagtype& flags, const flagtype& rem_flags);
        static void rem(flagtype& flags, const unsigned char rem_flag);
        static void set(flagtype& flags, const flagtype& new_flags);
        static void set(flagtype& flags, const unsigned char flag_position);
        static bool get(const flagtype& flags, const flagtype& check_flags);
        static bool get(const flagtype& flags, const unsigned char check_flag);
    };

}

#ifdef NET_FLAGMAN_IMPLEMENTATION
// FlagManager.cpp

namespace flags {

    template<typename flagtype, typename cast_type>
    void FlagManager<flagtype, cast_type>::add(flagtype& flags, const flagtype& add_flags) {
        flags = static_cast<flagtype>(static_cast<cast_type>(flags) | static_cast<cast_type>(add_flags));
    }

    template<typename flagtype, typename cast_type>
    void FlagManager<flagtype, cast_type>::add(flagtype& flags, const unsigned char add_flag) {
        flags = static_cast<flagtype>(static_cast<cast_type>(flags) | (1u << add_flag));
    }

    template<typename flagtype, typename cast_type>
    void FlagManager<flagtype, cast_type>::rem(flagtype& flags, const flagtype& rem_flags) {
        flags = static_cast<flagtype>(static_cast<cast_type>(flags) & ~static_cast<cast_type>(rem_flags));
    }

    template<typename flagtype, typename cast_type>
    void FlagManager<flagtype, cast_type>::rem(flagtype& flags, const unsigned char rem_flag) {
        flags = static_cast<flagtype>(static_cast<cast_type>(flags) & ~(1u << rem_flag));
    }

    template<typename flagtype, typename cast_type>
    void FlagManager<flagtype, cast_type>::set(flagtype& flags, const flagtype& new_flags) {
        flags = new_flags; // Direct assignment remains unchanged
    }

    template<typename flagtype, typename cast_type>
    void FlagManager<flagtype, cast_type>::set(flagtype& flags, const unsigned char flag_position) {
        flags = static_cast<flagtype>(1u << flag_position);
    }

    template<typename flagtype, typename cast_type>
    bool FlagManager<flagtype, cast_type>::get(const flagtype& flags, const flagtype& check_flags) {
        return (static_cast<cast_type>(flags) & static_cast<cast_type>(check_flags)) == static_cast<cast_type>(check_flags);
    }

    template<typename flagtype, typename cast_type>
    bool FlagManager<flagtype, cast_type>::get(const flagtype& flags, const unsigned char check_flag) {
        return (static_cast<cast_type>(flags) & (1u << check_flag)) != 0;
    }
}
#undef NET_FLAGMAN_IMPLEMENTATION
#endif
