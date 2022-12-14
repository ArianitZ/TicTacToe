#include "game.h"

Game::Game(int screen_width, int screen_height)
{
    m_screen_width = screen_width;
    m_screen_height = screen_height;
    m_cell_size = m_screen_height/grid_size;

    m_window.reset(new Window(screen_width, screen_height, m_window_title));
}

bool Game::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    if(!(m_window->init()))
    {
        return false;
    }
    // Initialize SDL image
    int img_flags = IMG_INIT_PNG;
    int innit = IMG_Init(img_flags);
    if(!(innit & img_flags) )
    {
        printf("Unable to initialze SDL_image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    
    return true;
}

void Game::close()
{
    printf("Closing down game!\n");
    m_o_texture.free();
    m_x_texture.free();
    m_grid_texture.free();
    m_window->free();

    SDL_Quit();
    IMG_Quit();
}

void Game::load_media()
{
    m_x_texture.loadFromFile(m_x_file_path, m_window->getRenderer());
    m_o_texture.loadFromFile(m_o_file_path, m_window->getRenderer());
    m_grid_texture.loadFromFile(m_grid_file_path, m_window->getRenderer());
}

void Game::assign_textures()
{
    // Initialize seed
    std::srand(time(NULL));
    
    int tmp{std::rand()%2};
    if(tmp)
    {
        m_player.reset(new Player(m_x_texture, "x"));
        m_npc.reset(new Player(m_o_texture, "o"));
    }
    else
    {
        m_player.reset(new Player(m_o_texture, "o"));
        m_npc.reset(new Player(m_x_texture, "x"));
    }
}

void Game::render_all()
{
    m_window->render_clear();
    m_window->render_single_object(&m_grid_texture, 0, 0);

    std::vector<IRenderable*> tmp;
    tmp.push_back(m_player.get());
    tmp.push_back(m_npc.get());
    m_window->render(tmp);

    m_window->render_present();
}

void Game::render_new_markers()
{
    for(Point point : (m_player.get()->getPositions()))
    {
        m_window->render_single_object(m_player.get()->getTexture(), point.getX(), point.getY());
    }
    m_window->render_present();

    SDL_Delay(300); // For visual effect, so that npc markers are not displayed too quick
    for(Point point : (m_npc.get()->getPositions()))
    {
        m_window->render_single_object(m_npc.get()->getTexture(), point.getX(), point.getY());
    }
    m_window->render_present();
}

void Game::handle_events()
{
    SDL_Event event;
    bool mouse_event{false};
    int x{},y{};

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            m_game_over = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            mouse_event = true;
            // Transform from window coordinates to grid coordinates
            x = event.button.x / m_cell_size;
            y = event.button.y / m_cell_size;
        }
    }

    if(mouse_event && !m_positions[x][y])
    {
        add_position(m_player.get(), x, y);
    
        if(check_for_win() || check_for_draw())
        {
            m_game_over = true;
        }
        else
        {
            add_random_position(m_npc.get());
            if(check_for_win() || check_for_draw())
            {
                m_game_over = true;
            }    
        }
        render_new_markers();
    }

    if(game_over())
    {
        SDL_Delay(1000);
    }
}

bool Game::game_over()
{
    return m_game_over;
}

bool Game::check_for_win()
{
    // Check all rows and columns
    for(int i{0}; i<grid_size; i++)
    {
        int col_sum{0}, row_sum{0};
        int col_prev{m_positions[i][i]};
        int row_prev{m_positions[i][i]};
        for(int j{0}; j<grid_size; j++)
        {
            int col_curr = m_positions[i][j];
            int row_curr = m_positions[j][i];
            col_sum += (col_curr == col_prev) ? col_curr : 0;
            row_sum += (row_curr == row_prev) ? row_curr : 0;
            if(std::abs(col_sum) == grid_size || std::abs(row_sum) == grid_size)
            {
                return true;
            }
            col_prev = col_curr;
            row_prev = row_curr;
        }
    }

    // Check diagonals
    int diag1_sum{0};
    int diag2_sum{0};
    int diag1_prev{m_positions[0][0]};
    int diag2_prev{m_positions[grid_size-1][0]};
    for(int i{0}; i<grid_size; i++)
    {
        int diag1_curr{m_positions[i][i]};
        int diag2_curr{m_positions[grid_size-1-i][i]};
        diag1_sum += (diag1_prev == diag1_curr) ? diag1_curr : 0;
        diag2_sum += (diag2_prev == diag2_curr) ? diag2_curr : 0;
        if(std::abs(diag1_sum) == grid_size || std::abs(diag2_sum) == grid_size)
        {
            return true;
        }
        diag1_prev = diag1_curr;
        diag2_prev = diag2_curr;
    }

    return false;
}

bool Game::check_for_draw()
{
    int n_player_markers = m_player.get()->getPositions().size();
    int n_npc_markers = m_npc.get()->getPositions().size();
    int total_markers = n_player_markers + n_npc_markers;

    return total_markers == (grid_size*grid_size);
}

void Game::add_random_position(Player* player)
{
    std::string marker{player -> getMarkerType()};
    int marker_type{marker == "o" ? 1 : -1};

    int x{std::rand() % grid_size};
    int y{std::rand() % grid_size};
    while(m_positions[x][y])
    {
        x = std::rand() % grid_size;
        y = std::rand() % grid_size;
    }

    m_positions[x][y] = marker_type;
    player -> addPosition(m_cell_size*x+x, m_cell_size*y+y);
}

void Game::add_position(Player* player, int x, int y)
{
    std::string marker{player -> getMarkerType()};
    int marker_type{marker == "o" ? 1 : -1};

    m_positions[x][y] = marker_type;
    player -> addPosition(m_cell_size*x+x, m_cell_size*y+y);
}
