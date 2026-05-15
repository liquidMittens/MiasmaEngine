#ifndef PULSE_EVENT_HPP
#define PULSE_EVENT_HPP
#include <functional>
#include <vector>
#include <memory>

namespace pulse
{
	/// <summary>
	/// Wraps the std::bind call in a friendly name
	/// </summary>
	/// <typeparam name="Class"></typeparam>
	/// <typeparam name="Arg"></typeparam>
	class EventBinder
	{
	public:
		template<typename Class, typename Ret, typename... Args>
		static std::function<Ret(Args...)>	 bind(Class* obj, Ret(Class::* method)(Args...)) {
			return [obj, method](Args... args) -> Ret {
				std::invoke(method, obj, std::forward<Args>(args)...);
				};
		}

		template<typename Class, typename Ret, typename... Args>
		static std::function<Ret(Args...)>	 bind(const Class* obj, Ret(Class::*method)(Args...)) {
			return [obj, method](Args... args) -> Ret {
				std::invoke(method, obj, std::forward<Args>(args)...);
				};
		}
	};

	/// <summary>
	/// Event class definition
	/// </summary>
	/// <typeparam name="...Args"></typeparam>
	template<typename ...Args>
	class Event
	{

	public:
		using Func = std::function<void(Args...)>;

		/// <summary>
		/// EventConnection allows for manual disconnection (unregistering) from an event.
		/// </summary>
		class EventConnection
		{
		public:
			friend Event;

			inline void connect(Event* owner, std::size_t newID)
			{
				_eventOwner = owner;
				_id = newID;
			}

			inline void disconnect()
			{
				if (_eventOwner != nullptr) {
					_eventOwner->disconnectListener(_id);
				}
			}

			std::size_t _id = 0;
			Event* _eventOwner = nullptr;
		};

		/// <summary>
		/// Adds a listener to the event.
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="fn"></param>
		/// <returns></returns>
		template<typename ...Args>
		EventConnection addListener(Func fn) {
			++_currentID;
			EventConnection conn;
			conn.connect(this, _currentID);
			_listeners.emplace_back(_currentID, std::move(fn));
			return conn;
		}

		/// <summary>
		/// Adds a listener to the event.
		/// </summary>
		/// <typeparam name="F"></typeparam>
		/// <param name="f"></param>
		/// <returns></returns>
		template<class F>
		EventConnection addListener(F&& f) {
			const std::size_t id = ++_currentID;
			EventConnection c; c.connect(this, id);
			_listeners.emplace_back(id, Func(std::forward<F>(f)));
			return c;
		}

		/// <summary>
		/// invoke calls all methods associated with this Event.
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="...args"></param>
		template<typename ...Args>
		void invoke(const Args&... args) {
			for (auto fn : _listeners) {
				fn.second(args...);
			}
		}

		/// <summary>
		/// Clears the vector of listeners and sets current ID back to 0.
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		template<typename ...Args>
		void clear() {
			_listeners.clear();
			_currentID = 0;
		}

		/// <summary>
		/// Get the number of listeners to this event
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <returns></returns>
		template<typename ...Args>
		std::size_t count() {
			return _listeners.size();
		}

		/// <summary>
		/// This method removes a EventConnection from the listeners vector based on the provided id.  This is an internal function called by EventConnection::disconnect()
		/// </summary>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="removeID"></param>
		/// <returns></returns>
		template<typename ...Args>
		bool disconnectListener(std::size_t removeID)
		{
			auto iter = std::remove_if(_listeners.begin(), _listeners.end(), [&](auto& pair) {
				return (pair.first == removeID);
				});

			_listeners.erase(iter);
			return true;
		}

	private:

		inline bool disconnectListener(std::size_t removeID);

		std::vector <std::pair<std::size_t, Func>> _listeners;
		std::size_t _currentID = 0;
	};
}
#endif