
#include "excercise_1_12.h"
#include "excercise_1_13.h"

void ui(void);

// User command specific data
#define UI_EXCERCISE_1_12 "1-12"
#define UI_EXCERCISE_1_13 "1-13"
#define UI_INFO "info"
#define UI_HELP "help"

#define DESC_EXCERCISE_1_12 "Run excercise 1-12 from the book \"C Programming Language\""
#define DESC_EXCERCISE_1_13 "Run excercise 1-13 from the book \"C Programming Language\""
#define DESC_INFO "Get more information on this program"
#define DESC_HELP "List all commands"

void ui_info(char* userInput);
void ui_help(char* userInput);
void ui_excercise_1_12(char* userInput);
void ui_excercise_1_13(char* userInput);

typedef struct userCommand_t
{
	char *command;
	char *command_description;
	void (*command_function)(char*);
} userCommand_t;

static const userCommand_t commandTable[] = 
{
	{UI_INFO, DESC_INFO, &ui_info},
	{UI_HELP, DESC_HELP, &ui_help},
	{UI_EXCERCISE_1_12, DESC_EXCERCISE_1_12, &ui_excercise_1_12},
	{UI_EXCERCISE_1_13, DESC_EXCERCISE_1_13, &ui_excercise_1_13},
};