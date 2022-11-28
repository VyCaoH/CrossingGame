#include "Sound.h"
bool Sound::audioMenu()
{
	
	return PlaySound(TEXT("Music\\Menu.wav"), NULL, SND_ASYNC);

}
bool Sound::audioUpScore()
{
	return PlaySound(TEXT("Music\\Level-win.wav"), NULL, SND_ASYNC);
}
bool Sound::audioButton()
{
	return PlaySound(TEXT("Music\\Button.wav"), NULL, SND_ASYNC);
}
bool Sound::audioDie()
{
	return PlaySound(TEXT("Music\\Die.wav"), NULL, SND_ASYNC);
}
