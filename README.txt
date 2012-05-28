These are Xcode file templates for creating varies files.

Created by Rowland O'Flaherty on 7/09/2010

--------------------------------------------------------------------------------
Instructions
--------------------------------------------------------------------------------

To install:
1.	Place ???.xctemplate folder containing the file template in
	the user file templates folder. Create folders if necessary.

	An example full path to directory containing project template is
	~/Library/Developer/Xcode/Templates/File Templates/C and C++/C++ Class.xctemplate

2.	Edit the com.apple.Xcode PBXCustomTemplateMacroDefinitions.plist to
	include a property named EMAIL, which stores your email address.

	*	Either edit the file
		~/Library/Preferences/com.apple.Xcode.plist
		with the Property List Editor.

	*	Or use this command in the Termainl:
		defaults write com.apple.Xcode PBXCustomTemplateMacroDefinitions '{ "EMAIL" = "email@address.com";}'

Note:	To insert Xcode template macros wrap the macro name with ___ and ___
	characters.

To use:
1.	Open Xcode select "File" > "New File".
	
2.	Enter name of the file.

3.	Hit finish.
	
--------------------------------------------------------------------------------
REVISION HISTORY
--------------------------------------------------------------------------------
1. July 9, 2010
	Initial Revision.

2. August 16, 2010
	Reorganized Templates Folder.

3. November 6, 2011
	Updated to work with Xcode 4.