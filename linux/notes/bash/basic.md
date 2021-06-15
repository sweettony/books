## Contents

## bash exit code
- When a command terminates on a fatal **signal** whose number is N, Bash uses the value 128+N as the exit status.  
- If a command is not found, the child process created to execute it returns a status of 127. If a command is found but is not executable, the return status is 126.  