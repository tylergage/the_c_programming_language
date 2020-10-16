
#include "excercise_1_12.h"
#include "excercise_1_13.h"
#include "arrays_and_strings.h"
#include "linked_lists.h"
#include "bit_manipulation.h"
#include "pool_test.h"

void ui(void);

// User command specific data
#define UI_EXCERCISE_1_12 "1-12"
#define UI_EXCERCISE_1_13 "1-13"
#define UI_CCI_1_1 "cci-1-1"
#define UI_CCI_1_2 "cci-1-2"
#define UI_CCI_2_1 "cci-2-1"
#define UI_CCI_2_2 "cci-2-2"
#define UI_CCI_5_1 "cci-5-1"
#define UI_CCI_5_3 "cci-5-3"
#define UI_POOL_ALLOC "pool"
#define UI_INFO "info"
#define UI_HELP "help"

#define DESC_EXCERCISE_1_12 "Run excercise 1-12 from the book \"C Programming Language\""
#define DESC_EXCERCISE_1_13 "Run excercise 1-13 from the book \"C Programming Language\""
#define DESC_CCI_1_1 "Run excercise 1-1 from the book \"Cracking the Coding Interview\""
#define DESC_CCI_1_2 "Run excercise 1-2 from the book \"Cracking the Coding Interview\""
#define DESC_CCI_2_1 "Run excercise 2-1 from the book \"Cracking the Coding Interview\""
#define DESC_CCI_2_2 "Run excercise 2-2 from the book \"Cracking the Coding Interview\""
#define DESC_CCI_5_1 "Run excercise 5-1 from the book \"Cracking the Coding Interview\""
#define DESC_CCI_5_3 "Run excercise 5-3 from the book \"Cracking the Coding Interview\""
#define DESC_POOL_ALLOC "Test pool allocator, take home interview"
#define DESC_INFO "Get more information on this program"
#define DESC_HELP "List all commands"

void ui_excercise_1_12(char* userInput);
void ui_excercise_1_13(char* userInput);
void ui_cci_1_1(char* userInput);
void ui_cci_1_2(char* userInput);
void ui_cci_2_1(char* userInput);
void ui_cci_2_2(char* userInput);
void ui_cci_5_1(char* userInput);
void ui_cci_5_3(char* userInput);
void ui_pool_alloc(char* userInput);
void ui_info(char* userInput);
void ui_help(char* userInput);

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
	{UI_CCI_1_1, DESC_CCI_1_1, &ui_cci_1_1},
	{UI_CCI_1_2, DESC_CCI_1_2, &ui_cci_1_2},
	{UI_CCI_2_1, DESC_CCI_2_1, &ui_cci_2_1},
	{UI_CCI_2_2, DESC_CCI_2_2, &ui_cci_2_2},
	{UI_CCI_5_1, DESC_CCI_5_1, &ui_cci_5_1},
	{UI_CCI_5_3, DESC_CCI_5_3, &ui_cci_5_3},
	{UI_POOL_ALLOC, DESC_POOL_ALLOC, &ui_pool_alloc},
};