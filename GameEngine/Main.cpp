#include <stdlib.h>
#include "Application.h"
#include "MemLeaks.h"
#include "Globals.h"

#include "SDL.h"

#include <chrono>

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char ** argv)
{
	LOGT(LogsType::SYSTEMLOG, "Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	long long timeElapsed = 0;

	while (state != MAIN_EXIT)
	{
		auto start = chrono::steady_clock::now();
		switch (state)
		{
		case MAIN_CREATION:

			LOGT(LogsType::SYSTEMLOG, "-------------- Application Creation --------------");
			App = Application::GetInstance();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOGT(LogsType::SYSTEMLOG, "-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOGT(LogsType::WARNINGLOG, "Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOGT(LogsType::SYSTEMLOG, "-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			//Set DT
			App->SetDT((float)timeElapsed / 1000.0f);

			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)	
			{
				LOGT(LogsType::WARNINGLOG, "Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOGT(LogsType::SYSTEMLOG, "-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOGT(LogsType::WARNINGLOG, "Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

		//Calculate next frame DT
		auto end = chrono::steady_clock::now();
		timeElapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	}

	delete App;
	LOGT(LogsType::SYSTEMLOG, "Exiting game '%s'...\n", TITLE);

	ReportMemoryLeaks();

	return main_return;
}