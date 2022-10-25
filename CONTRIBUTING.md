# TYRBO-on-terminal CONTRIBUTION GUIDELINES

## File Structure
This project contains the following files:
  - `client.c`: Contains the main function for the program. Functions which directly interact with user are defined here
  - `type_content.c`: Contains all the functions required for the typing functionality and all the game modes
  - `type_content.h`: Contains header files of the functions defined in `type_content.c`
  - `tc.c`: Contains all the functions required for controlling the cursor and output on the terminal
  - `tc.h`: Contains header files of the functions defined in `tc.c` and the macros for terminal control
  - `mktyrbo.sh`: Shell script to compile the code / clean the output files. Invokes `make -f mktyrbo.mk`
  - `init_terminal.bat`: Batchfile to configure the terminal on windows to accept utf-8 encoding characters
  - ~~`kendi.sh`: THIS WILL NOT WORK ON ALL DEVICES. Script file that disables the keyboard on linux. Not the best implementation as it's hardcoded to work only for Repo owner's device~~ This script is not needed anymore! Leaving it here for a while though :D


## PR Guidelines
Make sure to follow these guidelines to create quality PRs for this repo
  - Fork the repo and work on changes only on your fork of the repo
  - Request to be assigned to an issue of your interest and do not submit PRs until assigned
  - Tag the issue number in your PRs in the description
  - Add screenshots and description of what you changed in the PR
  - **MAKE SURE TO DELETE ALL `.o` and `.exe` or `.out` FILES BEFORE COMMITTING. PRs THAT DO NOT COMPLY WITH THIS WILL NOT BE ACCEPTED**
  - To do this, add the command "clean" after the compile instructions. eg: `mktyrbo clean` or `./mktyrbo.sh clean`

## Issue Guidelines
Make sure to follow these guidelines if you wish to create an issue for this repo:
  - Add an issue 
  - Create a clear title and quality description explaining the problem clearly
  - If the issue is specific to a particular OS, prefix the title with the name of the OS in all caps within []. eg: [LINUX]This is an issue
  - Tag a maintainer to review the Issue

If you wish to work on this issue you created, tag a maintainer and ask to be assigned

## Other Guidelines
Make sure to add some documentation for the code you have added/changed! This will be appreciated <3
