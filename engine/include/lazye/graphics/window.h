#pragma once
#include <lazye/lazye.h>

#include <memory>
#include <string>

namespace lazye
{
	class RenderingContext;

	/**
	 * Simple Window class 
	 */
	class lazyedll Window
	{
	public:
		enum class Mode
		{
			Windowed,
			Fullscreen
		};

		struct Size
		{
			std::uint16_t width;
			std::uint16_t height;
		};

		struct Position
		{
			std::uint16_t x;
			std::uint16_t y;
		};

		Window() = default;
		virtual ~Window() = default;

		Window(const Window& other) = delete;
		Window& operator=(const Window& other) = delete;

		virtual bool IsOpen() const = 0;

		virtual void SetTitle(const std::string& title) = 0;
		virtual void SetPosition(Position position) = 0;
		virtual void Resize(Size size) = 0;
		virtual void SetMode(Mode mode) = 0;
		virtual void Display() = 0;
		virtual void Close() = 0;

		virtual RenderingContext& GetRenderingContext() = 0;

	protected:
		static constexpr Size DEFAULT_WINDOW_SIZE = { 800, 600 };
		static constexpr const char* DEFAULT_WINDOW_TITLE = "LazyE Window";
		static constexpr Mode DEFAULT_WINDOW_MODE = Mode::Windowed;
	};
}