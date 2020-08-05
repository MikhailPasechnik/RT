#include "gui.h"
#include "libft.h"

static int	gl_setup(t_gui *gui)
{
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	gui->gl_context = SDL_GL_CreateContext(gui->win);
	glViewport(0, 0, GUI_WIN_WIDTH, GUI_WIN_HEIGHT);
	if (glewInit() != GLEW_OK) {
		ft_putstr("Failed to setup GLEW\n");
		return (0);
	}
	return (1);
}

int			gui_setup(t_gui *gui)
{
	struct nk_font_atlas	*atlas;

	gui->win = SDL_CreateWindow(
			"RT Gui", 0, 0, GUI_WIN_WIDTH, GUI_WIN_HEIGHT,
			SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);;
	if (!gui->win || !gl_setup(gui))
		return (0);
	gui->ctx = nk_sdl_init(gui->win);
	nk_sdl_font_stash_begin(&atlas);
	nk_sdl_font_stash_end();
	return (1);
}
