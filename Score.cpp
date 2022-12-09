#include "Score.h"

int Score::getScore()
{
	return score;   
}
void Score::setScore(int x)
{
	if (x > 1)
		score = (x - 1) * 100;

}
void Score::DisplayScore()
{
	Renderer::draw_number(getScore(), 78, 31, 1.3, 0x0002D9);
}
void Score::readHighScore()
{
    ifstream file;
    string s; 
    file.open("Highscores.txt");
    if (file.is_open()) {
        int num;
        for (int i = 0 ; i < 3 ; i++)
        {
            file >> num;
            highscore[i] = num;
        }
        file.close();
    }
}
void Score::writeHighScore()
{
    if (score > highscore[2])
    {
        highscore[2] = score;
        ofstream file;
        file.open("Highscores.txt");
        if (file.is_open()) 
        {
            sort(highscore.begin(),highscore.end(), greater<int>());
            for (int i = 0; i < highscore.size(); i++)
            {
                file << highscore[i] << endl;
            }
            file.close();
        }
    }
}
void Score::DisplayHighScore()
{
    Renderer::draw_number(highscore[0], 77, 10.5, 0.9, 0xE30000);
}