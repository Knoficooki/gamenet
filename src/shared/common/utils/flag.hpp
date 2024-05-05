#pragma once

namespace flags {

    template<typename flagtype>
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

} // namespace flags
