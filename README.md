# General things
- */Release/Bin* Dictionary is the folder that includes terms (**metadata**) after extracting
- */Release/File* is the folder that includes **Set of files** to search. ( **format** : *folder/subfolder/** )
- */Release/Config*
	- *stopwords.txt* 
	- *index.txt*
- */Release/Bin/ExtractMeta.exe* is the executive file for extracting metadata directly from *index.txt*

# Non-GUI
There are two executive files in the folder named */Release/Bin*:
- *Query.exe* 
- *ModifyIndex.exe* ( ***For the file-modified purpose***)
# GUI
To run GUI version, run this command in **cmd** and ensure that **Python has already installed**.
```
python Gui.py
```
Adding function in GUI version only supports */folder/**
