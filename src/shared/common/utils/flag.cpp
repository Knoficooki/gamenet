#include "flag.hpp"

namespace flags {

    template<typename flagtype>
    void FlagManager<flagtype>::add(flagtype& flags, const flagtype& add_flags) {
        flags |= add_flags;
    }

    template<typename flagtype>
    void FlagManager<flagtype>::add(flagtype& flags, const unsigned char add_flag) {
        flags |= (1 << add_flag);
    }

    template<typename flagtype>
    void FlagManager<flagtype>::rem(flagtype& flags, const flagtype& rem_flags) {
        flags &= ~rem_flags;
    }

    template<typename flagtype>
    void FlagManager<flagtype>::rem(flagtype& flags, const unsigned char rem_flag) {
        flags &= ~(1 << rem_flag);
    }

    template<typename flagtype>
    void FlagManager<flagtype>::set(flagtype& flags, const flagtype& new_flags) {
        flags = new_flags;
    }

    template<typename flagtype>
    void FlagManager<flagtype>::set(flagtype& flags, const unsigned char flag_position) {
        flags = (1 << flag_position);
    }

    template<typename flagtype>
    bool FlagManager<flagtype>::get(const flagtype& flags, const flagtype& check_flags) {
        return (flags & check_flags) == check_flags;
    }

    template<typename flagtype>
    bool FlagManager<flagtype>::get(const flagtype& flags, const unsigned char check_flag) {
        return (flags & (1 << check_flag)) != 0;
    }


} // namespace flags
