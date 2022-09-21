#ifndef GAME_H
#define GAME_H

#include <array>
#include "player.h"
#include "window.h"
#include "texture.h"
#include "cstdlib"
#include "memory"
#include <time.h>

class Game
{
    public:
        Game(int screen_width, int screen_height);

        bool init();

        void close();

        void load_media();

        void assign_textures();

        void render_all();

        void handle_events();

        bool game_over();

        static const int grid_size{3};
        
    private:
        int m_screen_height{};
        int m_screen_width{};
        int m_cell_size{};

        bool m_computers_turn{false};
        bool m_game_over{false};
        
        // 0 = empty, 1 = o, -1 = x
        std::array<std::array<int, grid_size>, grid_size> m_positions{};
        std::string m_window_title = "Tic Tac Toe";

        std::string m_x_file_path = "assets/x.png";
        std::string m_o_file_path = "assets/o.png";
        std::string m_grid_file_path = "assets/grid.png";

        Texture m_x_texture;
        Texture m_o_texture;
        Texture m_grid_texture;

        std::unique_ptr<Window> m_window;
        
        std::unique_ptr<Player> m_player;
        std::unique_ptr<Player> m_npc;

        bool check_for_win();
        bool check_for_draw();
        void add_random_position(Player* player);
        void add_position(Player* player, int x=-1, int y=-1);
        void render_new_markers();

};

#endif