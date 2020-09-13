
#define UI_EXCERCISE_1_12 "1-12"
#define UI_EXCERCISE_1_13 "1-13"
#define UI_INFO "info"
#define UI_HELP "help"

void ui_info(char* userInput);
void ui_help(char* userInput);
void ui_excercise_1_12(char* userInput);
void ui_excercise_1_13(char* userInput);

typedef struct userCommand_t
{
	char *command;
	void (*command_function)(char*);
} userCommand_t;

const userCommand_t commandTable[] = 
{
	{UI_INFO, &ui_info},
	{UI_HELP, &ui_help},
	{UI_EXCERCISE_1_12, &ui_excercise_1_12},
	{UI_EXCERCISE_1_13, &ui_excercise_1_13},
};
