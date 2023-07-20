#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
* exitShell - exits the shell
* @info: structure containing potential arguments. Used to maintain
*        constant function prototype.
*
* Return: Always 1 (to indicate the shell should exit).
*/
int exitShell(info_t *info)
{
if (info->argc > 1)
{
int exitStatus = convertToExitStatus(info->argv[1]);
if (exitStatus < 0)
{
printErrorMessage(info, "Illegal number: ");
printString(info->argv[1]);
printCharacter('\n');
}
else
{
info->exitStatus = exitStatus;
}
}

return (1);
}

/**
* changeDirectory - changes the current working directory
* @info: structure containing potential arguments. Used to maintain
*        constant function prototype.
*
* Return: Always 0.
*/
int changeDirectory(info_t *info)
{
char buffer[1024];
char *currentDir, *newDir;

if (info->argc < 2)
{
/* No arguments provided, change to HOME directory */
newDir = getEnvironmentVariable(info, "HOME");
changeDir(newDir ? newDir : "/");
}
else if (compareStrings(info->argv[1], "-") == 0)
{
/* Change to the previous working directory */
newDir = getEnvironmentVariable(info, "OLDPWD");
changeDir(newDir ? newDir : "/");
}
else
{
/* Change to the specified directory */
currentDir = getCurrentWorkingDirectory(buffer, sizeof(buffer));
if (!currentDir)
{
perror("getCurrentWorkingDirectory");
return (0);
}

changeDir((newDir = getEnvironmentVariable(info, "PWD")) ? newDir : "/");
setEnvironmentVariable(info, "OLDPWD", currentDir);
setEnvironmentVariable(info, "PWD", getCurrentWorkingDirectory(buffer, sizeof(buffer)));
}

return (0);
}
