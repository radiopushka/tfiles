# Tfiles - Terminal-Based File Manager

`tfiles` is a terminal-based file manager designed for efficient file navigation and management directly from the command line interface.
It should work over SSH.

## Features
- **Directory Navigation:** Traverse through directories using keyboard arrows.
- **File Preview:** Preview images and file details within the terminal.
- **Command Execution:** Run terminal commands on selected files and directories.
- **Search Functionality:** Search for files within a directory using `/`.
- **File Operations:**
  - Default configurations for programs located in ~/.local/share/tfiles/mimetypes
    - It follows a pattern of extension to type and then a type to command. 
  - Copy, move, and delete files and directories.
  - Set and paste file buffers for file transfers.
- **Keyboard Driven:** Fully controlled using the keyboard for maximum efficiency.

## Requirements
- GCC or compatible C compiler
- libpng library
- libjpeg library
  - you can disable image support by following the instructions in the IMAGE_SUPPORT header file. They are enabled by default.
- POSIX-compliant system
- 256 color terminal like st

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
- **ESC:** Quit the program

### File Operations
- **Delete:** Press `Space` -> `d` to delete the selected file
- **Copy:** Press `Space` -> `b` to set file buffer, then `Space` -> `c` to paste here
- **Move:** Press `Space` -> `b` to set file buffer, then `Space` -> `m` to move here
- Press `Space` for more information

### Terminal Commands
- Press `Space` -> `t` to enter a custom terminal command for the selected file or directory.
- "%b" signifies the buffer variable (for copy and pasting), double quotes are recommended
- "%f" signifies the highlighted file, double quotes are recommended
- "%d" signifies the current directory, double quotes are recommended
- "%q" signifies an element in the queue, double quotes are recommended
  - for each element in the queue it will run the command manipulating "%q"


## Code Structure
- **main.c:** The main entry point and core logic
- **command_processor.c:** Handles parsing and processing of terminal commands
- **rendered/**: UI rendering and key definitions
- **rendered/icons.h**: this is where the default applications are defined as well as the 16x7 icons
  - the icon color in the default set is #1c80bf with a white to alpha gradient

## Contributing
Feel free to fork and submit pull requests. Contributions for performance improvements and feature additions are welcome.

## License
This project is licensed under the GPL License.

![2025-01-07_23-06](https://github.com/user-attachments/assets/776beb66-5c0b-46d4-ada9-14d94f828f54)

![2025-01-07_23-09](https://github.com/user-attachments/assets/63209e2b-d066-48e4-b4d5-a6f813ec08ef)

![2025-01-07_23-12](https://github.com/user-attachments/assets/3e2d7a74-ee51-45e5-b0ae-982183cb8a72)

