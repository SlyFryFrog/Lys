module;
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>
export module lys.vulkan.vk_renderer;

import renderer;

// Enable Vulkan debugging while in Debug mode
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

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

		void update_viewport(int width, int height) override
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
			appInfo.pEngineName = "Lys Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			std::vector<const char*> requiredExtensions = get_required_extensions();

			// Vulkan Instance Create Info
			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pNext = nullptr;
#ifdef __APPLE__
			createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR; // Required on macOS
#endif
			createInfo.pApplicationInfo = &appInfo;

			createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
			createInfo.ppEnabledExtensionNames = requiredExtensions.data();

			createInfo.enabledLayerCount = 0;
			createInfo.ppEnabledLayerNames = nullptr;

			// Create the Vulkan Instance
			VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
			if (result != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create Vulkan instance!");
			}
		}

		/**
		 * @brief Get the required extensions object
		 * 
		 * @throws std::runtime_error Failed to get required GLFW extensions.
		 *
		 * @return std::vector<const char*> 
		 */
		static std::vector<const char*> get_required_extensions()
		{
			uint32_t glfwExtensionCount = 0;
			const char** glfwExtensions;
			glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const char*> extensions(glfwExtensions,
												glfwExtensions + glfwExtensionCount);

			// Failed to get required extensions, stop
			if (!glfwExtensions)
			{
				throw std::runtime_error("Failed to get GLFW required instance extensions");
			}

			// Enable debugging if building in Debug mode
			if (enableValidationLayers)
			{
				extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			}

			// Since Vulkan 1.3 this is needed for Apple devices
#ifdef __APPLE__
			extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

			return extensions;
		}
	};
} // namespace Lys
