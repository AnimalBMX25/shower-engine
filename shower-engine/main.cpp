#include <iostream>
using namespace std;

#include <XboxInput.h>
#include <Timer.h>
#include <Pulse.h>
#include <SoundManager.h>
#include <Globals.h>

void TestTimer();
void TestXinput();
void TestSound();


int main()
{
	//TestSound();

	cout << "TEST COMPLETED\n";
	//TestTimer();

	Globals::GlobalsManager::SetGlobals("../data/settings/global_settings_files.txt");

	return 0;
}

void TestTimer()
{
	Utility::Timer timer;

	timer.StartTimer();

	Utility::Pulse pulse(5.0);

	cout << "WAIT 5 SECONDS\n";

	while(!pulse.IsReady())
	{
		timer.TimeStep();
		pulse.Update(timer.GetDeltaTime());
	}

	cout << "DONE\n";
	cout << "WAIT 2 SECONDS\n";

	pulse.SetPulseTime(2.0);

	while(!pulse.IsReady())
	{
		timer.TimeStep();
		pulse.Update(timer.GetDeltaTime());
	}

	cout << "DONE\n";
}

void TestXinput()
{
	if(Input::XboxInput::IsConnected(Input::XBOX_CONTROLLER_INDEX::ONE))
	{
		cout << "TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}
}

void TestSound()
{
	Sound::SoundManager::Init();

	Sound::SoundManager::Play();

	Sound::SoundManager::Cleanup();
}