module;
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>
export module vulkan;

import renderer;

namespace Lys
{
	export class VkRenderer : public IRenderer
	{
		VkInstance m_instance{};

	public:
		VkRenderer() = default;

		void init() override
		{
			create_vulkan_instance();
		}

		void begin_frame() override
		{
		}

		void draw() override
		{
		}

		void end_frame() override
		{
		}

		void resize(int width, int height) override
		{
		}

		void shutdown() override
		{
		}

	private:
		void create_vulkan_instance()
		{
			// -- Vulkan Application Info --
			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Vulkan WIP";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			// -- Get GLFW required extensions --
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
			if (!glfwExtensions)
			{
				throw std::runtime_error("Failed to get GLFW required instance extensions");
			}

			// -- Required extensions including portability --
			std::vector<const char*> requiredExtensions(glfwExtensions,
														glfwExtensions + glfwExtensionCount);
			requiredExtensions.emplace_back(
				VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME); // macOS requires this

			// -- Vulkan Instance Create Info --
			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pNext = nullptr;
			createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR; // Required on
																				 // macOS
			createInfo.pApplicationInfo = &appInfo;

			createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
			createInfo.ppEnabledExtensionNames = requiredExtensions.data();

			createInfo.enabledLayerCount = 0;
			createInfo.ppEnabledLayerNames = nullptr;

			// -- Create the Vulkan Instance --
			VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan instance!");
			}
		}
	};
} // namespace Lys
