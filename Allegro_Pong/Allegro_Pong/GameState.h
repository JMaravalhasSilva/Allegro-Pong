#ifndef ALLEGRO_PONG_GAMESTATE_HEADER
#define ALLEGRO_PONG_GAMESTATE_HEADER


class GameState {
	public:

		//Virtual game loop functions
		virtual void handle_events() = 0;
		virtual void logic() = 0;
		virtual void render() = 0;

		//Virtual destructor (necessary to make sure that derived classes implement their own destructors)
		virtual ~GameState() {};
};

class MainMenu : public GameState {
	public:

		//Constructor and destructor functions
		MainMenu();
		~MainMenu();

		//Game loop functions
		void handle_events();
		void logic();
		void render();
};

class InGame : public GameState {
	public:

		//Constructor and destructor functions
		InGame();
		~InGame();

		//Game loop functions
		void handle_events();
		void logic();
		void render();
};















#endif