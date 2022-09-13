#include "game.h"

// TODO: Validate inputs (screen_width==scren_height)
Game::Game(int screen_width, int screen_height)
{
    m_screen_width = screen_width;
    m_screen_height = screen_height;
    m_cell_size = m_screen_height/3;

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
    m_window->free();

    SDL_Quit();
    IMG_Quit();
}

void Game::loadMedia()
{
    m_x_texture = Texture();
    m_o_texture = Texture();

    m_x_texture.loadFromFile(m_x_file_path, m_window->getRenderer());
    m_o_texture.loadFromFile(m_o_file_path, m_window->getRenderer());
}

void Game::assignTextures()
{
    int tmp{std::rand()%2};
    if(tmp)
    {
        m_player.reset(new Player(m_x_texture));
        m_npc.reset(new Player(m_o_texture));
    }
    else
    {
        m_player.reset(new Player(m_o_texture));
        m_npc.reset(new Player(m_x_texture));
    }
}

void Game::render()
{
    std::vector<Player*> tmp;
    tmp.push_back(m_player.get());
    tmp.push_back(m_npc.get());
    m_window->render(tmp);
}

void Game::handleEvents()
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
            x = event.button.x / m_cell_size;
            y = event.button.y / m_cell_size;
        }
    }

    if(mouse_event && !m_positions[x][y])
    {
        m_positions[x][y] = true;
        m_player -> addPosition(m_cell_size*x, m_cell_size*y);
        printf("Added position (%d, %d)\n", x, y);
    }
}

bool Game::gameOver()
{
    return m_game_over;
}

