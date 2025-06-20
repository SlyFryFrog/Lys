module;
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vulkan/vulkan.h>
export module lys.platform.vk_window;

import lys.rendering;
import lys.platform.platform_interfaces;
import lys.platform.input.input_manager;


namespace Lys
{
	export class VkWindow final : public IWindow
	{
		VkSurfaceKHR m_surface{};

	public:
		VkWindow() = default;

		explicit VkWindow(const int width, const int height, const std::string& title) :
			IWindow(width, height, title)
		{
		}

		~VkWindow() override
		{
			destroy();
		}

		void init() override
		{
			if (!glfwInit())
			{
				std::println("Failed to initialize glfw.");
			}

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			if (!glfwVulkanSupported())
			{
				throw std::runtime_error(
					"GLFW: Vulkan not supported on this system! Try selecting an OpenGL context.");
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

			if (!m_window)
			{
				glfwTerminate();
				std::println("Failed to create Window instance! Terminating GLFW.");
				return;
			}

			// Makes the current window context
			glfwMakeContextCurrent(m_window);

			// // Associates window user pointer with current instance
			glfwSetWindowUserPointer(m_window, this);
			glfwSetFramebufferSizeCallback(m_window, frame_buffer_callback);
			glfwSetKeyCallback(m_window, InputManager::_process_input_callback);
			glfwSetCursorPosCallback(m_window, InputManager::_process_mouse_callback);
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_FALSE);
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			frame_buffer_callback(m_window, m_width, m_height);
		}

	private:
		void create_surface()
		{
			// if (glfwCreateWindowSurface(instance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
			// 	throw std::runtime_error("failed to create window surface!");
			// }
		}
	};
} // namespace Lys
