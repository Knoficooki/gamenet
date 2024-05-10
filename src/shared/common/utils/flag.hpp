// FlagManager.hpp

#pragma once

namespace flags {

    template<typename _type, typename flag_type>
    class FlagManager {
    public:
        static _type add(_type &flags, const flag_type &add_flags);
        static _type rem(_type &flags, const flag_type &rem_flags);
        static _type set(_type &flags, const flag_type &new_flags);
        static bool get(const _type &flags, const flag_type &check_flags);
    };

}

#ifdef NET_FLAGMAN_IMPLEMENTATION
// FlagManager.cpp

namespace flags {

    template<typename _type, typename flag_type>
    _type FlagManager<_type, flag_type>::add(_type &flags, const flag_type &add_flags) {
        return (flags = static_cast<_type>(static_cast<_type>(flags) | static_cast<_type>(add_flags)));
    }

    template<typename _type, typename flag_type>
    _type FlagManager<_type, flag_type>::rem(_type &flags, const flag_type &rem_flags) {
        return (flags = static_cast<_type>(static_cast<_type>(flags) & ~static_cast<_type>(rem_flags)));
    }

    template<typename _type, typename flag_type>
    _type FlagManager<_type, flag_type>::set(_type &flags, const flag_type &new_flags) {
        return (flags = static_cast<_type>(new_flags));
    }

    template<typename _type, typename flag_type>
    bool FlagManager<_type, flag_type>::get(const _type &flags, const flag_type &check_flags) {
        return (static_cast<_type>(flags) & static_cast<_type>(check_flags)) == static_cast<_type>(check_flags);
    }
}
#undef NET_FLAGMAN_IMPLEMENTATION
#endif
