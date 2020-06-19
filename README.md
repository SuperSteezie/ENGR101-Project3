# ENGR101-Project3
## SFML Installation (Windows 10)
1)	Install SFML 2.5.1 from https://www.sfml-dev.org/download/sfml/2.5.1/ .
    -	Which are either: **GCC 7.3.0 MinGW (DW2) - 32-bit** or **GCC 7.3.0 MinGW (SEH) - 64-bit** link.
2)	Ensure that SFML version installed is the same as the compiler. Meaning that if 64 bit MinGW compiler is used then download 64 bit SFML 2.5.1.
    -	To check Geany compiler version type ‘g++ --version’ into command prompt. If there is no result then download MinGW compiler via the same SFML site. 
    -	If compiler version is not **x86_64-posix-seh-rev0**, for when 64-bit version of SFML was downloaded then redownload the correct version by clicking the MinGW Builds 7.3.0(64-Bit) on the same SFML site. Or, download the 32-bit version of SFML. In summary:
    	- If 32-bit wanted use: **GCC 7.3.0 MinGW (DW2) - 32-bit** SFML and **i686-7.3.0-release-posix-dwarf-rt_v5-rev0** compiler.
        - If 64-bit wanted use: **GCC 7.3.0 MinGW (SEH) - 64-bit** SFML and **x86_64-posix-seh-rev0** compiler.
    -	Ensure compiler is added as new Environment Path Variable if MinGW compiler was changed or implemented. To add as new Environmental Path:
    	- Find extracted folder of compiler.
        - Navigate to mingw64/bin.
        - Copy address/file path.
        - Type ‘environment variable’ into Windows search.
        - Under **Advanced**, go to **Environment Variables** -> click **Path** (under User variables) -> click **Edit** button -> **New** -> then paste copied address.
        - Restart PC.
3)	Unzip/extract SFML folder anywhere.

## Running The Program
1)  Download zip of repository in https://github.com/SuperSteezie/ENGR101-Project3-Team13 by clicking the **Clone or download** button and downloading as zip.
2)  Create new file named ‘makefile’ via Geany in both *Team 13 AVC_Robot* and *Team 13 AVC_Server* folders. Copy paste indented below into makefile either via Text Editor or Geany.  (There should be an indent before every **g++** !)<br/>
> DIR = *C:\SFML-2.5.1*<br/>
> CFLAGS = -I ${DIR}\include <br/>
> LFLAGS = -L ${DIR}\lib <br/>
> LIBS = -lsfml-window  -lsfml-graphics -lsfml-system -lsfml-network <br/>
> **robot**: **robot**.o <br/>
> g++ $(LFLAGS) -o **robot** **robot**.o ${LIBS} <br/>
> **robot**.o: **robot**.cpp <br/>
> g++  -c $(CFLAGS) **robot**.cpp<br/>
3)	To change name of files, edit everything in bold above to whatever name you desire (need to also change .cpp file name if so). Then edit path (in italic above) to whichever path you extracted SFML to. 
    -	For example, for the makefile of the server, need to change everything in bold to ‘server3’ because that is what the .cpp file is called.
4)	Cut and paste robot.cpp into *Team 13 AVC_Robot*.
5)	In the SFML folder extracted in the installation notes above, go to **bi**n and copy paste all **.dll** files into *Team 13 AVC_Robot* and *Team 13 AVC_Server folders*.
6)	In Geany, go to Build -> Set Build Commands, and replace **make** with **mingw32-make**. Regardless of if 64 bit was downloaded.
7)	Hereafter, rather than using the **compile**, **build**, and **run** commands, use **make** instead (shift+F9) and **execute** as normal (F5).
    -	Order of program execution matters. Execute server first before the robot always.
8)	To change the maze. Look for config.txt under *Team 13 AVC_Server* folder and edit the first line to whichever maze desired. Possible mazes listed below.
    -	mazeFile,core.txt
    -	mazeFile,completion.txt
    -	mazeFile,challenge.txt

