module;
export module lys.platform.input.input_event;

import lys.platform.input.input_map;

namespace Lys
{
	export class InputEvent
	{
		Key m_key{};
        InputState m_state{RELEASED};

	public:
		InputEvent() = default;

		explicit InputEvent(const Key key) : m_key(key)
		{
		}

        explicit InputEvent(const Key key, const InputState state) : m_key(key), m_state(state)
		{
		}

		bool operator==(const Key key) const
		{
			return m_key == key;
		}

        [[nodiscard]] Key get_key() const
        {
            return m_key;
        }

        [[nodiscard]] bool is_pressed() const
        {
            return m_state == JUST_PRESSED || m_state == PRESSED;
        }

        [[nodiscard]] bool is_just_pressed() const
        {
            return m_state == JUST_PRESSED;
        }

        [[nodiscard]] bool is_just_released() const
        {
            return m_state == JUST_RELEASED;
        }

        void set_state(const InputState state)
        {
            m_state = state;
        }

        [[nodiscard]] InputState get_state() const
        {
            return m_state;
        }
	};
} // namespace Lys
