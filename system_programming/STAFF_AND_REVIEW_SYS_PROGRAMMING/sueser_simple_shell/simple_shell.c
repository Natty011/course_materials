/************************************
* Name: simple_shell.c              *
* Author: Sauser Khone              *
* Reviewer: x                       *
* Date: 11/3/2025                   *
************************************/

#include <assert.h>                 /* assert()                         */
#include <stdlib.h>                 /* exit(), size_t                   */
#include <string.h>                 /* strtok(), strchr()               */
#include <stdio.h>                  /* printf(), fgets(), feof(), stdin */

#include <unistd.h>                 /* execvp(), fork()                 */
#include <sys/wait.h>               /* wait()                           */
#include <sys/types.h>              /* pid_t                            */

#include "utils.h"

/*==============================================================================
                                     Macros
==============================================================================*/

#define TOKEN_DELIM                 " \n"

/*==============================================================================
                                  Enumerations
==============================================================================*/

enum
{
    SHELL_INPUT_OK =                0               ,
    SHELL_INPUT_BAD =               1
};

enum
{
    SHELL_NEXT =                    -1              ,
    SHELL_NORM =                    0               ,
    SHELL_EXIT =                    1
};

enum
{
    ERR_VAL =                       -1
};

enum
{
    INPUT_MAX =                     32              ,
    ARG_MAX =                       16              ,
    ARG_SIZE =                      ARG_MAX + 2
};

typedef struct builtin_cmd_t
{
    char *cmd;
    int (*func)(char**);
} builtin_cmd_t;

/*==============================================================================
                              Function Declarations
==============================================================================*/

void ShellLoop(void);

char *ShellReadInput(char *buffer, size_t size);

int ShellHandleInput(char *input);
void ShellParseInput(char *input, char **ret_cmd, char **ret_args);

int ShellHandleBuiltin(char *cmd, char **args);
void ShellHandleExecutable(char *cmd, char **args);

void ShellPrintPrompt(void);
void ShellHandleError(void);

/*******************************************************************************

*******************************************************************************/

int ShellCommandExit(char **args);

/*==============================================================================
                                    Commands
==============================================================================*/

static const builtin_cmd_t G_BUILTIN_CMDS[] =
{
    {
        "exit",
        ShellCommandExit
    },
    /* End of Commands */
    {
        NULL
    }
};

/*==============================================================================
                              Main-caller Function
*=============================================================================*/

int main(void)
{
    /* Start shell program */
    ShellLoop();

    return 0;
}

/*==============================================================================
                              Function Definitions
==============================================================================*/

/*
    Reads an input from the user, handles the input, and loops until stopped
*/
void ShellLoop(void)
{
    char buffer[INPUT_MAX] = { 0 };
    char *input = NULL;

    int valid_session = 1;
    int event = 0;

    while (valid_session)
    {
        /* Print prompt */
        ShellPrintPrompt();

        /* Receive input from user */
        input = ShellReadInput(buffer, INPUT_MAX);

        /* Handle recieved command */
        event = ShellHandleInput(input);

        /* Handle event */
        switch (event)
        {
            /* Handle shell exit */
            case SHELL_EXIT:
                valid_session = 0;
                break;
        }
    }
}

/*******************************************************************************

*******************************************************************************/

/*
    Reads input from the user
*/
char *ShellReadInput(char *buffer, size_t size)
{
    assert(buffer);

    if (fgets(buffer, size, stdin) == NULL)
    {
        return NULL;
    }
    return buffer;
}

/*******************************************************************************

*******************************************************************************/

/*
    Handles the command inputted by the user
*/
int ShellHandleInput(char *input)
{
    char *args[ARG_SIZE] = { NULL };
    char *cmd = NULL;
    int ret = 0;

    assert(input);

    /* No input (EOF) */
    if (!input)
    {
        return SHELL_EXIT;
    }

    /* Tokenize commands and arguments */
    ShellParseInput(input, &cmd, args);

    /* Handle the command */
    if (cmd)
    {
        if (SHELL_NEXT != (ret = ShellHandleBuiltin(cmd, args)))
        {
            return ret;
        }

        /* Executed normally */
        ShellHandleExecutable(cmd, args);
    }

    return SHELL_NORM;
}

/*******************************************************************************

*******************************************************************************/

/*
    Parse an input buffer into null-terminated strings for a single command
    and multiple arguments if they are present
*/
void ShellParseInput(char *input, char **ret_cmd, char **ret_args)
{
    char *token = NULL;

    assert(input);
    assert(ret_cmd);
    assert(ret_args);

    /* Save the first token command in both variables */
    token = strtok(input, TOKEN_DELIM);
    *ret_cmd = token;
    *(ret_args++) = token;

    /* Insert tokens and the last NULL */
    do
    {
        token = strtok(NULL, TOKEN_DELIM);
        *(ret_args++) = token;
    }
    while (token);
}

/*******************************************************************************

*******************************************************************************/

/*
    Try to handle a command if is a built-in command
*/
int ShellHandleBuiltin(char *cmd, char **args)
{
    const builtin_cmd_t *chk_cmd = G_BUILTIN_CMDS;

    assert(cmd);
    assert(args);

    /* Iterate over the available commands */
    while (chk_cmd)
    {
        /* Command terminator */
        if (!chk_cmd->cmd)
        {
            break;
        }

        if (0 == strcmp(chk_cmd->cmd, cmd))
        {
            return chk_cmd->func(args);
        }

        ++chk_cmd;
    }

    /* Command could not be handled */
    return SHELL_NEXT;
}

/*
    Handle a command as an executable that should be able to run
*/
void ShellHandleExecutable(char *cmd, char **args)
{
    pid_t pid = 0;

    assert(cmd);
    assert(args);

    ExitIfBad(ERR_VAL != (pid = fork()), "Process fork failed");

    if (pid == 0)
    {
        /* Execute and only return on failure */
        execvp(cmd, args);
        /* Returned from failure */
        ShellHandleError();
    }
    else
    {
        wait(NULL);
    }
}

/*******************************************************************************

*******************************************************************************/

/*
    Built-in command
    Send an exit signal
*/
int ShellCommandExit(char **args)
{
    UNUSED(args);
    return SHELL_EXIT;
}

/*******************************************************************************

*******************************************************************************/

/*
    Prints a basic prompt for the user
*/
void ShellPrintPrompt(void)
{
    printf(">");
}

/*
    Handle shell execution error on failure
*/
void ShellHandleError(void)
{
    perror("shell");
    abort();
}