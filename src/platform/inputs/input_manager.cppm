module;
#include <GLFW/glfw3.h>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
export module lys.platform.input.input_manager;

export import lys.platform.input.input_event;
export import lys.platform.input.input_map;

namespace Lys
{

	export class InputManager
	{
		static std::queue<std::shared_ptr<InputEvent>> m_eventQueue; // Put events in order
		static std::queue<std::shared_ptr<InputEvent>> m_recentQueue;
		static std::map<Key, std::shared_ptr<InputEvent>> m_events; // Register events for quick
																	// access
		static const size_t MAX_RECENT_QUEUE = 10;

	public:
		static void _process_input_callback(GLFWwindow* window, int key, int scancode, int action,
											int mods)
		{
			Key lysKey = convert_code(key);
			InputState state;

			if (action == GLFW_PRESS && !m_events.contains(lysKey))
			{
				std::cout << "Size: " << m_recentQueue.size() << "\n";
				state = InputState::JUST_PRESSED;
			}
			else if (action == GLFW_RELEASE)
			{
				state = InputState::JUST_RELEASED;
			}
			else if (action == GLFW_REPEAT)
			{
				if (m_events[lysKey]->get_state() == InputState::JUST_PRESSED)
				{
					m_events[lysKey]->set_state(InputState::PRESSED);
				}
				else
				{
					m_events[lysKey]->set_state(InputState::RELEASED);
				}
			}

			std::shared_ptr<InputEvent> event = std::make_shared<InputEvent>(lysKey, state);

			// Add to recent queue if just pressed
			if (state == InputState::JUST_PRESSED)
			{
				m_recentQueue.push(event);

				if (m_recentQueue.size() > MAX_RECENT_QUEUE)
				{
					m_recentQueue.pop(); // Keep the queue size limited
				}
			}

			m_eventQueue.push(event);
			m_events[lysKey] = event;
		}

		static void _process_mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
		{
		}

		/**
		 * @brief Processes and updates Input states and events.
		 */
		static void _process()
		{
			// Handle all events in the queue
			while (!m_eventQueue.empty())
			{
				std::shared_ptr<InputEvent> event = m_eventQueue.front();
				m_eventQueue.pop();

				Key key = event->get_key();
				InputState state = event->get_state();

				// Update the map depending on the event state
				if (state == InputState::JUST_PRESSED)
				{
					m_events[key]->set_state(InputState::PRESSED);
				}
				else if (state == InputState::JUST_RELEASED)
				{
					m_events.erase(key); // Key is released, remove from active map
				}
			}

			clear_recent_queue();
		}

		static bool is_pressed(Key key)
		{
			if (!m_events.contains(key))
			{
				return false;
			}

			return m_events[key]->is_pressed();
		}

		static bool is_just_pressed(Key key)
		{
			if (!m_events.contains(key))
			{
				return false;
			}

			return m_events[key]->is_just_pressed();
		}

		static bool is_just_released(Key key)
		{
			if (!m_events.contains(key))
			{
				return false;
			}

			return m_events[key]->is_just_released();
		}

		static bool is_released(Key key)
		{
			return !m_events.contains(key);
		}

		/**
		 * @return std::map<Key, std::shared_ptr<InputEvent>> Map of Key, InputEvent pairs.
		 */
		static std::map<Key, std::shared_ptr<InputEvent>> get_events()
		{
			return m_events;
		}

		/**
		 * @brief Checks if keys are pressed in a specific order.
		 *
		 * @param keys Order of keys being pressed.
		 * @return true Keys are pressed in the specific order.
		 * @return false Either not all keys are pressed or some key is pressed that is not in the
		 * keys.
		 */
		static bool is_ordered_combo_hold(const std::initializer_list<Key>& keys)
		{
			std::queue<std::shared_ptr<InputEvent>> tempRecentQueue = m_recentQueue;
			auto it = keys.begin();

			while (it != keys.end() && !tempRecentQueue.empty())
			{
				std::shared_ptr<InputEvent> currentEvent = tempRecentQueue.front();
				if (currentEvent->get_key() == *it && currentEvent->is_pressed())
				{
					tempRecentQueue.pop();
					it++;
				}
				else if (!currentEvent->is_just_pressed())
				{
					tempRecentQueue.pop(); // Skip non-JUST_PRESSED events
				}
				else
				{
					return false; // Sequence doesn't match
				}
			}

			// If we've gone through all the keys in the desired sequence,
			// now check if all those keys are currently being held down.
			if (it == keys.end())
			{
				for (const Key& key : keys)
				{
					if (!m_events.contains(key) || !m_events[key]->is_pressed())
					{
						return false; // Not all keys are held
					}
				}

				for (const auto& pair : m_events)
				{
					bool inCombo = false;
					for (const Key& comboKey : keys)
					{
						if (pair.first == comboKey)
						{
							inCombo = true;
							break;
						}
					}
					if (!inCombo && pair.second->is_pressed())
					{
						return false; // Another key is pressed
					}
				}

				return true; // Sequence matched and all keys are held
			}

			return false; // The recent queue didn't contain the full sequence of presses
		}

	private:
		/**
		 * @brief Converts a integer code from GLFW to enum Key.
		 *
		 * @param key The GLFW key code.
		 * @return Key The converted key.
		 */
		static Key convert_code(int key)
		{
			Key lysKey;
			if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			{
				lysKey = Key::KEY_SHIFT;
			}
			else if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
			{
				lysKey = Key::KEY_ALT;
			}
			else
			{
				lysKey = static_cast<Key>(key);
			}

			return lysKey;
		}

		/**
		 * @brief Clear all elements that are not currently pressed from recent queue.
		 */
		static void clear_recent_queue()
		{
			// Clear recentQueue of all !is_pressed elements
			std::queue<std::shared_ptr<InputEvent>> tempQueue;
			while (!m_recentQueue.empty())
			{
				std::shared_ptr<InputEvent> event = m_recentQueue.front();
				m_recentQueue.pop();

				// Copy element to other queue
				if (is_pressed(event->get_key())) // Checks if event contains key and is pressed
				{
					tempQueue.emplace(event);
				}
			}

			// Update queue
			m_recentQueue = tempQueue;
		}
	};

	std::queue<std::shared_ptr<InputEvent>> InputManager::m_eventQueue;
	std::queue<std::shared_ptr<InputEvent>> InputManager::m_recentQueue;
	std::map<Key, std::shared_ptr<InputEvent>> InputManager::m_events;
} // namespace Lys
