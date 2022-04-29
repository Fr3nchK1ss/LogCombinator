# LogCombinator
Given log files selected through the QML UI, LogCombinator creates one single log file where lines are ordered according to their timestamps.  
Uses the infamous FolderListModel (still a badly documented Qt.labs feature at time of coding)

## Build
Open the CMakeLists.txt with QtCreator, then follow the normal Qt build flow.

## Test files
Log files must have ISO timestamps. An ISO timestamp looks like yyyy-mm-ddThh:mm:ss[.mmm]
The test files are 
* file1.log
> 2022-04-12T19:52:33.328850 message 1 of file1
2022-04-12T19:52:33.900992 message 2 of file1
2022-04-12T19:52:34.273339 message 3 of file1
2022-04-12T19:52:34.764704 message 4 of file1
2022-04-12T19:52:35.540755 message 5 of file1

* file2.log
>  2022-04-12T19:52:33.328850 message 1 of file2
2022-04-12T19:52:33.900992 message 2 of file2
2022-04-12T19:52:34.440932 message 3 of file2
2022-04-12T19:52:34.764704 message 4 of file2
2022-04-12T19:52:35.540755 message 5 of file2


