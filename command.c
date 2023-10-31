/*
 * Lab 3: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 * 
 */

// 1.1 Parsing and Executing Commands
// To begin, you will write a scanner and parser for your shell using Lex and Yacc. Look through
// the skeleton code and try to understand how it works. Lex will produce tokens by matching
// regular expressions; Yacc will then match these tokens to grammatical expressions and call your
// corresponding code.
// The file command.h implements a data structure that represents a shell command. A shell command
// can consist of multiple parts; the struct single_command implements an argument list for a single
// command (i.e. a command of the form mycmd arg1 arg2 arg3). Then, when pipes are used, the
// command will be composed of multiple single_command’s. The struct command represents such a
// list of simple commands (Which can also be just one single_command). Additionally, command has
// fields which allow the user to specify the files to use for input, output, and error redirection.

#include "command.h"

#include <stdio.h>
#include <stdlib.h>

#include "shell.h"

/*
 *  Initialize a command_t
 */
void initCommand(command_t* cmd) {
  cmd->single_commands = NULL;
  cmd->out_file = NULL;
  cmd->in_file = NULL;
  cmd->err_file = NULL;
  cmd->append_out = false;
  cmd->append_err = false;
  cmd->background = false;
  cmd->num_single_commands = 0;
}



void create_command(command_t *command) {
  command->single_commands = NULL;

  command->out_file = NULL;
  command->in_file = NULL;
  command->err_file = NULL;

  command->append_out = false;
  command->append_err = false;
  command->background = false;

  command->num_single_commands = 0;
} /* create_command() */

/*
 *  Insert a single command into the list of single commands in a command_t
 */

void insert_single_command(command_t *command, single_command_t *simp) {
  if (simp == NULL) {
    return;
  }

  command->num_single_commands++;
  int new_size = command->num_single_commands * sizeof(single_command_t *);
  command->single_commands = (single_command_t **)
                              realloc(command->single_commands,
                                      new_size);
  command->single_commands[command->num_single_commands - 1] = simp;
} /* insert_single_command() */

/*
 *  Free a command and its contents
 */

void free_command(command_t *command) {
  for (int i = 0; i < command->num_single_commands; i++) {
    free_single_command(command->single_commands[i]);
  }

  if (command->out_file) {
    free(command->out_file);
    command->out_file = NULL;
  }

  if (command->in_file) {
    free(command->in_file);
    command->in_file = NULL;
  }

  if (command->err_file) {
    free(command->err_file);
    command->err_file = NULL;
  }

  command->append_out = false;
  command->append_err = false;
  command->background = false;

  free(command);
} /* free_command() */

/*
 *  Print the contents of the command in a pretty way
 */

void print_command(command_t *command) {
  printf("\n\n");
  printf("              COMMAND TABLE                \n");
  printf("\n");
  printf("  #   single Commands\n");
  printf("  --- ----------------------------------------------------------\n");

  // iterate over the single commands and print them nicely
  for (int i = 0; i < command->num_single_commands; i++) {
    printf("  %-3d ", i );
    print_single_command(command->single_commands[i]);
  }

  printf( "\n\n" );
  printf( "  Output       Input        Error        Background\n" );
  printf( "  ------------ ------------ ------------ ------------\n" );
  printf( "  %-12s %-12s %-12s %-12s\n",
            command->out_file?command->out_file:"default",
            command->in_file?command->in_file:"default",
            command->err_file?command->err_file:"default",
            command->background?"YES":"NO");
  printf( "\n\n" );
} /* print_command() */

/*
 *  Execute a command
 */

void execute_command(command_t *command) {
  // Don't do anything if there are no single commands
  if (command->single_commands == NULL) {
    print_prompt();
    return;
  }

  // Print contents of Command data structure
  print_command(command);

  // Add execution here
  // For every single command fork a new process
  // Setup i/o redirection
  // and call exec

  // Clear to prepare for next command
  free_command(command);

  // Print new prompt
  print_prompt();
} /* execute_command() */
