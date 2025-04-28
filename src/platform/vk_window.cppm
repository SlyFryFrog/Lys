module;
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <string>
#include <print>
export module lys.platform.vk_window;

import window_interface;
import lys.rendering;


namespace Lys
{
	export class VkWindow : public IWindow
	{
		VkSurfaceKHR m_surface{};

	public:
		VkWindow() = default;

		explicit VkWindow(const int width, const int height, const std::string& title) :
			IWindow(width, height, title)
		{
		}

		~VkWindow()
		{
			destroy();
		}

		void init() override
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize glfw.";
			}

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			if (!glfwVulkanSupported())
			{
				throw std::runtime_error("GLFW: Vulkan not supported on this system!");
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

			if (!m_window)
			{
				glfwTerminate();
				std::cout << "Failed to create Window instance! Terminating GLFW.";
				return;
			}

			// Makes the current window context
			glfwMakeContextCurrent(m_window);

			// // Associates window user pointer with current instance
			// glfwSetWindowUserPointer(m_window, this);
			// glfwSetFramebufferSizeCallback(m_window, frame_buffer_callback);
			// // glfwSetKeyCallback(_window, InputManager::_process_input_callback);
			// // glfwSetCursorPosCallback(_window, InputManager::_process_mouse_callback);
			// glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_FALSE);
			// glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			// frame_buffer_callback(m_window, m_width, m_height);
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
