# Tfiles - Terminal-Based File Manager

`tfiles` is a terminal-based file manager designed for efficient file navigation and management directly from the command line interface.

## Features
- **Directory Navigation:** Traverse through directories using keyboard arrows.
- **File Preview:** Preview images and file details within the terminal.
- **Command Execution:** Run terminal commands on selected files and directories.
- **Search Functionality:** Search for files within a directory using `/`.
- **File Operations:**
  - Copy, move, and delete files and directories.
  - Set and paste file buffers for file transfers.
- **Keyboard Driven:** Fully controlled using the keyboard for maximum efficiency.

## Requirements
- GCC or compatible C compiler
- ncurses library
- POSIX-compliant system

## Installation
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd tfiles
   ```
2. Compile the source code:
   ```bash
   make
   ```
3. Run the file manager:
   ```bash
   ./tfiles
   ```

## Usage
### Basic Controls
- **Arrow Keys:** Navigate files and directories
- **Enter:** Open selected file or directory, if there is no default application then you will be prompted for a command
- **Tab:** Preview image (if applicable)
- **/ (Forward Slash):** Search for a file
- **Spacebar:** Open options popup
- **r:** Refresh current directory view
- **q:** Quit the program

### File Operations
- **Delete:** Press `Space` -> `d` to delete the selected file
- **Copy:** Press `Space` -> `b` to set file buffer, then `Space` -> `c` to paste here
- **Move:** Press `Space` -> `b` to set file buffer, then `Space` -> `m` to move here

### Terminal Commands
- Press `Space` -> `t` to enter a custom terminal command for the selected file or directory.
- "%b" signifies the buffer variable (for copy and pasting), double quotes are recommended
- "%f" signifies the highlighted file, double quotes are recommended
- "%d" signifies the current directory, double quotes are recommended

## Code Structure
- **main.c:** The main entry point and core logic
- **command_processor.c:** Handles parsing and processing of terminal commands
- **rendered/**: UI rendering and key definitions
- **rendered/icons.h**: this is where the default applications are defined as well as the 16x7 icons
- - the icon color in the default set is #1c80bf with a white to alpha gradient

## Contributing
Feel free to fork and submit pull requests. Contributions for performance improvements and feature additions are welcome.

## License
This project is licensed under the MIT License.

