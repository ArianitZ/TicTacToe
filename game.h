#ifndef GAME_H
#define GAME_H

#include <array>
#include "player.h"
#include "window.h"
#include "texture.h"
#include "cstdlib"
#include "memory"

class Game
{
    public:
        Game(int screen_width, int screen_height);

        bool init();

        void close();

        void loadMedia();

        void assignTextures();

        void render();

        void handleEvents();

        bool gameOver();

        static const int grid_size{3};
        
    private:
        int m_screen_height{};
        int m_screen_width{};
        int m_cell_size{};

        bool m_computers_turn{false};
        bool m_game_over{false};
        
        std::array<std::array<bool, grid_size>, grid_size> m_positions{};
        std::string m_window_title = "Tic Tac Toe";

        std::string m_x_file_path = "assets/x.png";
        std::string m_o_file_path = "assets/o.png";

        Texture m_x_texture;
        Texture m_o_texture;

        std::unique_ptr<Window> m_window;
        
        std::unique_ptr<Player> m_player;
        std::unique_ptr<Player> m_npc;


};

#endif