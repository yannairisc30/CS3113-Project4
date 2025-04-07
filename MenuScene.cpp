#include "MenuScene.h"
#include "Utility.h"
#include "LevelA.h"
#include <SDL.h>


//GLuint font_texture_id;


void Menu::initialise() {
	m_game_state.next_scene_id = -1;
	font_texture_id = Utility::load_texture("assests/font1.png");
}

void Menu::update(float delta_time) {
	const Uint8 *key_state = SDL_GetKeyboardState(NULL);
	if (key_state[SDL_SCANCODE_RETURN]) {
		m_game_state.next_scene_id = 1;
	}
}

void Menu::render(ShaderProgram* program) {
	Utility::draw_text(program, font_texture_id, "Escape the snowman", 0.4f, 0.1f, glm::vec3(-3.9f, 1.5f, 0.0f));
	Utility::draw_text(program, font_texture_id, "Press Enter to Start", 0.3f, 0.1f, glm::vec3(-3.27f, 0.5f, 0.0f));
}