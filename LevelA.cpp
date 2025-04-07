/**
* Author:Yannairis Cruz
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelA.h"
#include "Utility.h"
//#include <windows.h>

#define LEVELA_WIDTH 20
#define LEVELA_HEIGHT 8


constexpr int LEVELA_ENEMY_COUNT = 1;


unsigned int LEVELA_DATA[] =
{

	1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0,  0,   0 , 0 , 0,
	1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0,  0,   0 , 0 , 0,
	1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0,  0,   0 , 0 , 0,
	1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0, 0,  0,   0 , 0 , 0,
	1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  1,  0, 0,  0,   0 , 0 , 0,
	1,  0,  0,  0,  0,  0,  0,  0,  1,  0, 1,  1,  1,  17, 0, 0,  0,   0 , 0 , 0,
	1,  1,  1,  1,  1,  1,  1,  1,  17, 0, 16, 16, 16, 16, 0 ,0 , 1,   1,  1,  1,
	17, 17, 17, 17, 17, 17, 17, 17, 0,  0, 17, 17, 17, 17, 0, 0,  17,  17, 17, 17

};


LevelA::~LevelA()
{
	delete[] m_game_state.enemies;
	delete    m_game_state.player;
	delete    m_game_state.map;
	delete    m_game_state.flag;
	//Mix_FreeChunk(m_game_state.jump_sfx);
	//Mix_FreeMusic(m_game_state.bgm);
}

void LevelA::initialise() {
	m_game_state.next_scene_id = -1;
	GLuint map_texture_id = Utility::load_texture("assests/ice_mountain_tileset.png");
	m_game_state.map = new Map(LEVELA_WIDTH, LEVELA_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 16, 16);

	int player_walking_animation[4][3] = {
		{0,1,2}, //moving up, can see penguin back
		{6,7,8}, //moving down
		{9,10,11}, //moving left
		{3,4,5} //moving right
	};

	glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

	GLuint player_texture_id = Utility::load_texture("assests/penguin-gray.png");
	m_game_state.player = new Entity(
		player_texture_id,        // texture_id
		1.5f,                     // speed
		acceleration,             // acceleration
		5.0f,                     // jumping power
		player_walking_animation, // walking (4x4 array)
		0.0f,                     // animation time
		3,                        // animation frames (3 frames per direction)
		0,                        // animation index (start at 0)
		3,                        // columns in sprite sheet
		4,                        // rows in sprite sheet
		1.0f,                     // width
		1.0f,                     // height
		PLAYER                    // entity type
	);

	m_game_state.player->set_position(glm::vec3(2.5f, -2.75f, 0.0f));
	m_game_state.player->face_right();

	//Enemy attributes
	GLuint enemy_texture_id = Utility::load_texture("assests/snowman.png");

	m_game_state.enemies = new Entity[LEVELA_ENEMY_COUNT];

	m_game_state.enemies[0] = Entity(enemy_texture_id, 1.7f, 1.0f, 1.0f, ENEMY, WALKER, WALKING);
	m_game_state.enemies[0].set_entity_type(ENEMY);
	m_game_state.enemies[0].set_position(glm::vec3(6.0f, -1.75f, 0.0f));
	m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
	m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.18f, 0.0f));

	//flag
	GLuint flag_texture_id = Utility::load_texture("assests/flag.png");
	m_game_state.flag = new Entity();
	m_game_state.flag->set_entity_type(FLAG);
	m_game_state.flag->set_texture_id(flag_texture_id);
	m_game_state.flag->set_position(glm::vec3(18.0f, -5.0f, 0.0f));
	m_game_state.flag->set_movement(glm::vec3(0.0f));
	m_game_state.flag->set_width(1.0f);
	m_game_state.flag->set_height(1.0f);


};

void LevelA::update(float delta_time)
{
	m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, LEVELA_ENEMY_COUNT, m_game_state.map);
	m_game_state.flag->update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
	for (int i = 0; i < LEVELA_ENEMY_COUNT; i++) {
		m_game_state.enemies[i].update(delta_time, m_game_state.player, nullptr, 0, m_game_state.map);
	}

	for (int i = 0; i < LEVELA_ENEMY_COUNT; i++) 
	{
		if (m_game_state.player->check_collision(&m_game_state.enemies[i]))
		{
			std::cout << "Players Lives LevelA" << get_player_lives() << std::endl;
			int lives = get_player_lives();
			set_player_lives(lives - 1);
			std::cout << "A: Players Lives After Collision" << get_player_lives() << std::endl;
			m_game_state.player->set_position(glm::vec3(2.5f, -2.75f, 0.0f));
		}
	}

	if (m_game_state.player->get_position().y < -10.0f) 
	{
		int lives = get_player_lives();
		set_player_lives(lives - 1);
		std::cout << "A: Players Lives After Falling" << get_player_lives() << std::endl;
		m_game_state.next_scene_id = 1;
	}
		
	if (m_game_state.flag != nullptr && m_game_state.player->check_collision(m_game_state.flag))
	{
		if (m_game_state.player_lives > 0)
		{
			m_game_state.next_scene_id = 2;
		}
	}

	if (m_game_state.player_lives <= 0) {
		m_game_state.next_scene_id = 4;
	}


};

void LevelA::render(ShaderProgram* program)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.8f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_game_state.map->render(program);
	m_game_state.player->render(program);
	m_game_state.flag->render(program);


	for (int i = 0; i < LEVELA_ENEMY_COUNT; i++) {
		m_game_state.enemies[i].render(program);
	};



};

