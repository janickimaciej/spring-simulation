#include "guis/gui.hpp"
#include "scene.hpp"
#include "window.hpp"

#include <glm/glm.hpp>

int main()
{
	Window window{};
	Scene scene{window.viewportSize()};
	GUI gui{window.getPtr(), scene};
	window.setWindowData(scene, gui);

	while (!window.shouldClose())
	{
		gui.update();
		scene.update();
		scene.render();
		gui.render();
		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}
