Contains a few modifications for Win32++:

- Added an option to use the NS and WE sizing cursors for dockers instead resource file ones. (Tons of apps do this now)
- Added an option to pass style flags to windows being created.
  - This is because there are few windows that need to have their styles set at creation time and cannot have them altered after.
- Added ClearStrings to CListBox. This function clears all the strings in a Listbox by calling DeleteString until it returns 0.
- Add an option to keep the scrollbars always visible.
  - Scrollbars now show up as disabled if they are forced on.
