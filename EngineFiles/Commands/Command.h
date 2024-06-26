#ifndef AMU_COMMANDS_H
#define AMU_COMMANDS_H

namespace amu
{
	//is only interface (no ctor or rule of 5)
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

}

#endif //AMU_COMMANDS_H