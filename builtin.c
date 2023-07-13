#include "shell.h"

/**
* exitShell - exits the shell
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Exits with a given exit status
* (0) if info.argv[0] != "exit"
*/
int exitShell(info_t *info)
{
int exitStatus;
if (info->argv[1]) /* If there is an exit argument */
{
exitStatus = convertToExitStatus(info->argv[1]);
if (exitStatus == -1)
{
info->status = 2;
printErrorMessage(info, "Illegal number: ");
printString(info->argv[1]);
printCharacter('\n');
return (1);
}
info->err_num = convertToExitStatus(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
* changeDirectory - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int changeDirectory(info_t *info)
{
char *currentDir, *newDir, buffer[1024];

int chdirResult;
currentDir = getCurrentWorkingDirectory(buffer, 1024);
if (!currentDir)
printString("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
newDir = getEnvironmentVariable(info, "HOME=");
if (!newDir)
chdirResult = /* TODO: what should this be? */
changeDir((newDir = getEnvironmentVariable(info, "PWD=")) ? newDir : "/");
else
chdirResult = changeDir(newDir);
}
else if (compareStrings(info->argv[1], "-") == 0)
{
if (!getEnvironmentVariable(info, "OLDPWD="))
{
printString(currentDir);
printCharacter('\n');
return (1);
}
printString(getEnvironmentVariable(info, "OLDPWD="));
printCharacter('\n');
chdirResult = /* TODO: what should this be? */
changeDir((newDir = getEnvironmentVariable(info, "OLDPWD=")) ? newDir : "/");
}
else
chdirResult = changeDir(info->argv[1]);
if (chdirResult == -1)
{
printErrorMessage(info, "can't cd to ");
printString(info->argv[1]);
printCharacter('\n');
}
else
{
setEnvironmentVariable(info, "OLDPWD", getEnvironmentVariable(info, "PWD="));
setEnvironmentVariable(info, "PWD", getCurrentWorkingDirectory(buffer, 1024));
}
return (0);
}
/**
* displayHelp - displays help information
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int displayHelp(info_t *info)
{
char **argArray;
argArray = info->argv;
printString("help call works. Function not yet implemented \n");
if (0)
printString(*argArray); /* temp att_unused workaround */
return (0);
}
