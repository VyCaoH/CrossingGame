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
	return PlaySound(TEXT("Music\\Button.wav"), NULL,SND_NOSTOP|SND_ASYNC);
	//eturn PlaySound(TEXT(""), NULL, SND_NOSTOP|SND_SYNC);
}
bool Sound::audioDie()
{
	return PlaySound(TEXT("Music\\Die.wav"), NULL, SND_ASYNC);
}
bool Sound::audioEnter()
{
	return PlaySound(TEXT("Music\\Enter.wav"), NULL, SND_NOSTOP | SND_ASYNC);
}
bool Sound::audioGamePlay()
{
	return PlaySound(TEXT("Music\\Game.wav"), NULL, SND_NOSTOP | SND_ASYNC);

}
void Sound::audioStop()
{
	PlaySound(NULL, 0, 0);
}
