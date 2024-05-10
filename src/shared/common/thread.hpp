#pragma once

#include <thread>
#include <atomic>
#include "utils/flag.hpp"

/* TODO:
 *		bug on "std::invoke"
*/ 

namespace net {
	enum class thread_state_flags : uint8_t {
		none = 0,
		running = 1,
		stop_requested = 1 << 1,
	};

	template<typename ts = uint8_t, typename flag = thread_state_flags>
	class thread {
	public:
		using thread_state = flag;
		template< class F, class... Args >
		explicit thread(F&& f, Args&&... args);

		void join();

		void stop(bool wait_till_stop = true);

		using Flagman = flags::FlagManager<ts, flag>;

	private:
		std::thread t;
		std::atomic<ts> state;
	};
}


#ifdef NET_THREAD_IMPLEMENTATION

template<typename ts, typename flag>
template< class F, class... Args >
net::thread<ts, flag>::thread(F&& f, Args&&... args)
{
	t = std::thread(f, std::ref(state), std::move(args...));
	ts newState = state.load();

	Flagman::set(newState, thread_state_flags::none);
	Flagman::add(newState, thread_state_flags::running);

	state = newState;
}

template<typename ts, typename flag>
void net::thread<ts, flag>::join() {
	ts newState = state.load();
	Flagman::set(newState, thread_state_flags::none);

	Flagman::rem(newState, thread_state_flags::running);

	state = newState;

	t.join();
}

template<typename ts, typename flag>
void net::thread<ts, flag>::stop(bool wait_till_stop) {
	ts newState = state.load();
	Flagman::add(newState, thread_state_flags::stop_requested);
	state = newState;
	if (wait_till_stop) {
		join();
	}
}

#undef NET_THREAD_IMPLEMENTATION
#endif // NET_THREAD_IMPLEMENTATION
