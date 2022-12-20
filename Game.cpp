#include "Game.h"
//dp: derivative of position: Van toc
//ddp:  derivative of derivative of positon: Gia toc
float arena_half_size_x = 85, arena_half_size_y = 45;

int Game::getLv()
{
	return lv;
}

vector<Threat*> Game::getThreat()
{
	return threat;
}
Player Game::getPlayer()
{
	return player;
}
void Game::startGame()
{
	player = Player();
	threat.clear();
	lv = 1;
	score.readHighScore();
}

void Game::setHighScore()
{
	score.writeHighScore();
}
void Game::simulate_menu(Input* input)
{
	menu.loadMenuGame(input);
	if (menu.getMenuMode() == LOAD_GAME)
	{
		vector<string>listName; 
		vector<int> listLevel;
		static int name_count = 0;

		FileLoadGame(listName, listLevel);
		loadGame(input, listName, listLevel , name_count);
	}
}
void Game::simulate_game(Input* input, float dt)
{
	if (pressed(BUTTON_B))
	{
		is_down(BUTTON_B) = false;
		menu.setMenuMode(MAIN);
	}
	else
	{
		render_state = getRender();
		float speed = 5.f;
		Renderer::draw_Background(0, 0, 73, 45);
		player.move(input, dt, speed);
		player.checkWall(-28.5, 0, 71.5, 45);
		player.isImpact(threat);
		Renderer::draw_trees(0, 0);
		updatePosThreat();
		threatMove(dt);
		score.DisplayScore();
		score.DisplayHighScore();
		next_level();
	}
}
void Game::FileLoadGame(vector<string>&listName, vector<int> &listLevel)
{
	fstream fin("SaveGame.txt", std::ios::in);
	string temp;
	while (!fin.eof())
	{
		string player_name;
		fin >> player_name;
		stringstream ss(player_name);
		string temp;
		getline(ss, temp, '.');
		listName.push_back(temp);
		string temp_file = "temp\\" + player_name;
		fstream fin_player(temp_file, std::ios::in);
		while (!fin_player.eof()) {
			fin_player >> lv >> playerScore;
			listLevel.push_back(lv);
			fin_player >> temp;
			player.setX(stof(temp));
			fin_player >> temp;
			player.setY(stof(temp));
			fin_player >> temp;
			player.setIsDead(stof(temp));
		}
		fin_player.close();
	}
	fin.close();
}
void Game::loadGame(Input*input, vector<string>listName, vector<int> listLevel , int name_count) {
	
	render_state = getRender();
	if (pressed(BUTTON_S))
	{

		g_music_button = !g_music_button;
		if (g_music_button)
		{
			Sound::audioButton();
		}
		g_music_button = !g_music_button;
		name_count = name_count + 1;
		if (name_count > 10)name_count = 10;
	}
	if (pressed(BUTTON_W)) {
		g_music_button = !g_music_button;
		if (g_music_button)
		{
			Sound::audioButton();
		}
		g_music_button = !g_music_button;
		name_count = name_count - 1;
		if (name_count < 0)name_count = 0;
	}
	/*Do something in menu*/;
	if (pressed(BUTTON_ENTER))
	{
		//gan thong so cho player 

	}
	Renderer::draw_Load(listName, listLevel, name_count);
}


bool Game::saveGame(Input*input)
{
	Renderer::draw_rect(0, 0, 20, 10, 0x0000FF);
	Renderer::draw_text(name.c_str(), -15, 0, 0.3f, 0xFFFFFF);
	for (int i = 4; i < 40; i++)
		if (pressed(i))
		{
			is_down(i) = false;
			name += (char)(i + 61);
		}

	if (pressed(BUTTON_ENTER)) {
		string load = name.erase(0, 13) + ".txt";
		string temp_file = "temp\\" + load;
		fstream file(temp_file, ios::out);
		fstream file_save("SaveGame.txt", ios::out|ios::app);
		file_save <<endl<< load ;
		file << lv << " " << playerScore << " "
			<< player.getX() << " " << player.getY() << " "
			<< player.getIsDead() << " ";
		name = "YOUR NAME IS ";
		file_save.close();
		file.close();
		return true;
	}
	return false;
}

void Game::reset_game()
{
	player.setY(-45);
	threat.clear();
}
void Game::restartGame()
{
	startGame();
}
bool Game::next_level()
{
	//Bien tren Y
	if (player.getY() == 40)
	{
		lv++;
		Sound::audioUpScore();
		score.setScore(lv);
		reset_game();
	}
	return false;
}
int Game::overGame(Input* input)
{
	if (pressed(BUTTON_Y))
		return 1;
	else if (pressed(BUTTON_ESC))
		return -1;
	else if (pressed(BUTTON_B))
		return 2;
	else return 0;
}
bool Game::quit(Input* input)
{
	if (is_down(BUTTON_ESC))
		return false;
	return true;
}

void Game::threatMove(float dt)
{
	for (auto x : threat)
	{

		x->move(0.5,0.4*lv*dt);

	}
	return;
}
void Game::updatePosThreat()
{
	if (threat.empty())
	{
		threat.push_back(new Threat(-28));
		threat.push_back(new Threat(-13));
		threat.push_back(new Threat(13));
		threat.push_back(new Threat(28));
	}
	for (auto x : threat)
	{
		x->setThreatInRow(lv);
		int randomDir = 0 + rand() % 2;
		int randomType;
		if (lv == 1)
		{
			while (true)
			{
				randomType = 0 + rand() % 8;
				if (randomType % 2 == randomDir)
				{
					break;
				}
			}
		}
		if (lv == 2)
		{
			while (true)
			{
				randomType = 8 + rand() % 10;
				if (randomType % 2 == randomDir)
				{
					break;
				}
			}
		}
		if (lv > 2)
		{
			while (true)
			{
				randomType = 0 + rand() % 18;
				if (randomType % 2 == randomDir)
				{
					break;
				}
			}
		}
		x->setListEntity((TYPE)randomType, randomDir);
	}
	// draw traffic light 
}

bool Game::exitGame(thread& t1)
{
	t1.join();
	return true;
}

void Game::pauseGame(HANDLE hd)
{
	Renderer::draw_Pause(0, 0);
}

void Game::resumeGame(HANDLE hd)
{
	//g_pause = false;
	ResumeThread(hd);
}