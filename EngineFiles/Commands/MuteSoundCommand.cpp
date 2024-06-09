#include "MuteSoundCommand.h"
#include "ServiceLocator.h"

void amu::MuteSoundCommand::Execute()
{
	ServiceLocator::GetInstance().GetSoundSystem()->Mute();
}
