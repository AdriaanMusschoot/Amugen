#ifndef PM_MUTE_GAME_SOUND_COMMAND_H
#define PM_MUTE_GAME_SOUND_COMMAND_H
#include "Command.h"

namespace amu
{

	class MuteSoundCommand final : public amu::Command
	{
	public:
		MuteSoundCommand() = default;
		virtual ~MuteSoundCommand() override = default;

		MuteSoundCommand(MuteSoundCommand const& other) = delete;
		MuteSoundCommand(MuteSoundCommand&& other) = delete;
		MuteSoundCommand& operator=(MuteSoundCommand const& other) = delete;
		MuteSoundCommand& operator=(MuteSoundCommand&& other) = delete;

		void Execute() override;
	private:
	};

}

#endif //PM_MUTE_GAME_SOUND_COMMAND_H