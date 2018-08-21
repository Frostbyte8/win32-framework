REM: A batch program to rebuild the Win32++ samples using VS2015 Community.
REM: The contents of the log file is erased 

REM: Set the paths and environment variables
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86


::Cleanup
call CleanSamples
call CleanTutorials

REM: Change the directory to the Samples parent
pushd ..\Samples
if exist "..\output\VS2015\Debug" rmdir /s /q "..\output\VS2015\Debug"
if exist "..\output\VS2015\Release" rmdir /s /q "..\output\VS2015\Release"
if exist "..\output\VS2015\Tutorials" rmdir /s /q "..\output\VS2015\Tutorials"

@echo on

::Compile code
MSBuild Animation\ProjectFiles\Animation_2015.sln /p:Configuration=Debug                 > "..\output\VS2015.log"
MSBuild Animation\ProjectFiles\Animation_2015.sln /p:Configuration=Release               >>"..\output\VS2015.log"
MSBuild Browser\ProjectFiles\Browser_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild Browser\ProjectFiles\Browser_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild CommonDialogs\ProjectFiles\CommonDialogs_2015.sln /p:Configuration=Debug         >>"..\output\VS2015.log"
MSBuild CommonDialogs\ProjectFiles\CommonDialogs_2015.sln /p:Configuration=Release       >>"..\output\VS2015.log"
MSBuild ContextHelp\ProjectFiles\ContextHelp_2015.sln /p:Configuration=Debug             >>"..\output\VS2015.log"
MSBuild ContextHelp\ProjectFiles\ContextHelp_2015.sln /p:Configuration=Release           >>"..\output\VS2015.log"
MSBuild CustomControl\ProjectFiles\CustomControl_2015.sln /p:Configuration=Debug         >>"..\output\VS2015.log"
MSBuild CustomControl\ProjectFiles\CustomControl_2015.sln /p:Configuration=Release       >>"..\output\VS2015.log"
MSBuild DateTime\ProjectFiles\DateTime_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild DateTime\ProjectFiles\DateTime_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild DDXDemo\ProjectFiles\DDXDemo_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild DDXDemo\ProjectFiles\DDXDemo_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild Dialog\ProjectFiles\Dialog_2015.sln /p:Configuration=Debug                       >>"..\output\VS2015.log"
MSBuild Dialog\ProjectFiles\Dialog_2015.sln /p:Configuration=Release                     >>"..\output\VS2015.log"
MSBuild DialogBars\ProjectFiles\DialogBars_2015.sln /p:Configuration=Debug               >>"..\output\VS2015.log"
MSBuild DialogBars\ProjectFiles\DialogBars_2015.sln /p:Configuration=Release             >>"..\output\VS2015.log"
MSBuild DialogDemo\ProjectFiles\DialogDemo_2015.sln /p:Configuration=Debug               >>"..\output\VS2015.log"
MSBuild DialogDemo\ProjectFiles\DialogDemo_2015.sln /p:Configuration=Release             >>"..\output\VS2015.log"
MSBuild DialogResizing\ProjectFiles\DialogResizing_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild DialogResizing\ProjectFiles\DialogResizing_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild DialogTab\ProjectFiles\DialogTab_2015.sln /p:Configuration=Debug                 >>"..\output\VS2015.log"
MSBuild DialogTab\ProjectFiles\DialogTab_2015.sln /p:Configuration=Release               >>"..\output\VS2015.log"
MSBuild Direct2D\ProjectFiles\Direct2D_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild Direct2D\ProjectFiles\Direct2D_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild DirectX9\ProjectFiles\DirectX9_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild DirectX9\ProjectFiles\DirectX9_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild DirectX11\ProjectFiles\DirectX11_2015.sln /p:Configuration=Debug                 >>"..\output\VS2015.log"
MSBuild DirectX11\ProjectFiles\DirectX11_2015.sln /p:Configuration=Release               >>"..\output\VS2015.log"
MSBuild DLL\ProjectFiles\MakeDLL_2015.sln /p:Configuration=Debug                         >>"..\output\VS2015.log"
MSBuild DLL\ProjectFiles\MakeDLL_2015.sln /p:Configuration=Release                       >>"..\output\VS2015.log"
MSBuild DLL\ProjectFiles\TestDLL_2015.sln /p:Configuration=Debug                         >>"..\output\VS2015.log"
MSBuild DLL\ProjectFiles\TestDLL_2015.sln /p:Configuration=Release                       >>"..\output\VS2015.log"
MSBuild Dock\ProjectFiles\Dock_2015.sln /p:Configuration=Debug                           >>"..\output\VS2015.log"
MSBuild Dock\ProjectFiles\Dock_2015.sln /p:Configuration=Release                         >>"..\output\VS2015.log"
MSBuild DockContainer\ProjectFiles\DockContainer_2015.sln /p:Configuration=Debug         >>"..\output\VS2015.log"
MSBuild DockContainer\ProjectFiles\DockContainer_2015.sln /p:Configuration=Release       >>"..\output\VS2015.log"
MSBuild DockTabbedMDI\ProjectFiles\DockTabbedMDI_2015.sln /p:Configuration=Debug         >>"..\output\VS2015.log"
MSBuild DockTabbedMDI\ProjectFiles\DockTabbedMDI_2015.sln /p:Configuration=Release       >>"..\output\VS2015.log"
MSBuild DoubleBuffer\ProjectFiles\DoubleBuffer_2015.sln /p:Configuration=Debug           >>"..\output\VS2015.log"
MSBuild DoubleBuffer\ProjectFiles\DoubleBuffer_2015.sln /p:Configuration=Release         >>"..\output\VS2015.log"
MSBuild Explorer\ProjectFiles\Explorer_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild Explorer\ProjectFiles\Explorer_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild FastGDI\ProjectFiles\FastGDI_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild FastGDI\ProjectFiles\FastGDI_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild FilePrintPreview\ProjectFiles\FilePrintPreview_2015.sln /p:Configuration=Debug   >>"..\output\VS2015.log"
MSBuild FilePrintPreview\ProjectFiles\FilePrintPreview_2015.sln /p:Configuration=Release >>"..\output\VS2015.log"
MSBuild FormDocView\ProjectFiles\FormDemo_2015.sln /p:Configuration=Debug                >>"..\output\VS2015.log"
MSBuild FormDocView\ProjectFiles\FormDemo_2015.sln /p:Configuration=Release              >>"..\output\VS2015.log"
MSBuild Frame\ProjectFiles\Frame_2015.sln /p:Configuration=Debug                         >>"..\output\VS2015.log"
MSBuild Frame\ProjectFiles\Frame_2015.sln /p:Configuration=Release                       >>"..\output\VS2015.log"
MSBuild INIFrame\ProjectFiles\INIFrame_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild INIFrame\ProjectFiles\INIFrame_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild GDIPlus\ProjectFiles\GDIPlus_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild GDIPlus\ProjectFiles\GDIPlus_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild MDIDockFrame\ProjectFiles\MDIDockFrame_2015.sln /p:Configuration=Debug           >>"..\output\VS2015.log"
MSBuild MDIDockFrame\ProjectFiles\MDIDockFrame_2015.sln /p:Configuration=Release         >>"..\output\VS2015.log"
MSBuild MDIFrame\ProjectFiles\MDIFrame_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild MDIFrame\ProjectFiles\MDIFrame_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild MDIFrameDemo\ProjectFiles\MDIDemo_2015.sln /p:Configuration=Debug                >>"..\output\VS2015.log"
MSBuild MDIFrameDemo\ProjectFiles\MDIDemo_2015.sln /p:Configuration=Release              >>"..\output\VS2015.log"
MSBuild MDIFrameSplitter\ProjectFiles\MDIFrameSplitter_2015.sln /p:Configuration=Debug   >>"..\output\VS2015.log"
MSBuild MDIFrameSplitter\ProjectFiles\MDIFrameSplitter_2015.sln /p:Configuration=Release >>"..\output\VS2015.log"
MSBuild MetaFile\ProjectFiles\MetaFile_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild MetaFile\ProjectFiles\MetaFile_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild NetClient\ProjectFiles\NetClient_2015.sln /p:Configuration=Debug                 >>"..\output\VS2015.log"
MSBuild NetClient\ProjectFiles\NetClient_2015.sln /p:Configuration=Release               >>"..\output\VS2015.log"
MSBuild NetClientAsync\ProjectFiles\NetClientAsync_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild NetClientAsync\ProjectFiles\NetClientAsync_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild NetServer\ProjectFiles\NetServer_2015.sln /p:Configuration=Debug                 >>"..\output\VS2015.log"
MSBuild NetServer\ProjectFiles\NetServer_2015.sln /p:Configuration=Release               >>"..\output\VS2015.log"
MSBuild NetServerAsync\ProjectFiles\NetServerAsync_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild NetServerAsync\ProjectFiles\NetServerAsync_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild NotePad\ProjectFiles\Notepad_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild NotePad\ProjectFiles\Notepad_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild Performance\ProjectFiles\Performance_2015.sln /p:Configuration=Debug             >>"..\output\VS2015.log"
MSBuild Performance\ProjectFiles\Performance_2015.sln /p:Configuration=Release           >>"..\output\VS2015.log"
MSBuild Picture\ProjectFiles\Picture_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild Picture\ProjectFiles\Picture_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild PrintPreview\ProjectFiles\PrintPreview_2015.sln /p:Configuration=Debug           >>"..\output\VS2015.log"
MSBuild PrintPreview\ProjectFiles\PrintPreview_2015.sln /p:Configuration=Release         >>"..\output\VS2015.log"
MSBuild PropertySheet\ProjectFiles\PropertySheet_2015.sln /p:Configuration=Debug         >>"..\output\VS2015.log"
MSBuild PropertySheet\ProjectFiles\PropertySheet_2015.sln /p:Configuration=Release       >>"..\output\VS2015.log"
MSBuild ReBarDemo\ProjectFiles\ReBarDemo_2015.sln /p:Configuration=Debug                 >>"..\output\VS2015.log"
MSBuild ReBarDemo\ProjectFiles\ReBarDemo_2015.sln /p:Configuration=Release               >>"..\output\VS2015.log"
MSBuild RibbonDockFrame\ProjectFiles\RibbonDockFrame_2015.sln /p:Configuration=Debug     >>"..\output\VS2015.log"
MSBuild RibbonDockFrame\ProjectFiles\RibbonDockFrame_2015.sln /p:Configuration=Release   >>"..\output\VS2015.log"
MSBuild RibbonFrame\ProjectFiles\RibbonFrame_2015.sln /p:Configuration=Debug             >>"..\output\VS2015.log"
MSBuild RibbonFrame\ProjectFiles\RibbonFrame_2015.sln /p:Configuration=Release           >>"..\output\VS2015.log"
MSBuild RibbonMDIFrame\ProjectFiles\RibbonMDIFrame_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild RibbonMDIFrame\ProjectFiles\RibbonMDIFrame_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild RibbonSimple\ProjectFiles\SimpleRibbon_2015.sln /p:Configuration=Debug           >>"..\output\VS2015.log"
MSBuild RibbonSimple\ProjectFiles\SimpleRibbon_2015.sln /p:Configuration=Release         >>"..\output\VS2015.log"
MSBuild RoundWindow\ProjectFiles\Round_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild RoundWindow\ProjectFiles\Round_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild Scribble\ProjectFiles\Scribble_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild Scribble\ProjectFiles\Scribble_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild ScrollTextFile\ProjectFiles\ScrollTextFile_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild ScrollTextFile\ProjectFiles\ScrollTextFile_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Simple\ProjectFiles\Simple_2015.sln /p:Configuration=Debug                       >>"..\output\VS2015.log"
MSBuild Simple\ProjectFiles\Simple_2015.sln /p:Configuration=Release                     >>"..\output\VS2015.log"
MSBuild Splitter\ProjectFiles\Splitter_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild Splitter\ProjectFiles\Splitter_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild StatusBar\ProjectFiles\StatusBar_2015.sln /p:Configuration=Debug                 >>"..\output\VS2015.log"
MSBuild StatusBar\ProjectFiles\StatusBar_2015.sln /p:Configuration=Release               >>"..\output\VS2015.log"
MSBuild StatusBarEx\ProjectFiles\StatusBarEx_2015.sln /p:Configuration=Debug             >>"..\output\VS2015.log"
MSBuild StatusBarEx\ProjectFiles\StatusBarEx_2015.sln /p:Configuration=Release           >>"..\output\VS2015.log"
MSBuild TabDemo\ProjectFiles\TabDemo_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild TabDemo\ProjectFiles\TabDemo_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild TaskDialog\ProjectFiles\TaskDialog_2015.sln /p:Configuration=Debug               >>"..\output\VS2015.log"
MSBuild TaskDialog\ProjectFiles\TaskDialog_2015.sln /p:Configuration=Release             >>"..\output\VS2015.log"
MSBuild Themes\ProjectFiles\Themes_2015.sln /p:Configuration=Debug                       >>"..\output\VS2015.log"
MSBuild Themes\ProjectFiles\Themes_2015.sln /p:Configuration=Release                     >>"..\output\VS2015.log"
MSBuild Threads\ProjectFiles\Threads_2015.sln /p:Configuration=Debug                     >>"..\output\VS2015.log"
MSBuild Threads\ProjectFiles\Threads_2015.sln /p:Configuration=Release                   >>"..\output\VS2015.log"
MSBuild TimeDemo\ProjectFiles\TimeDemo_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild TimeDemo\ProjectFiles\TimeDemo_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild ToolBarDemo\ProjectFiles\ToolBarDemo_2015.sln /p:Configuration=Debug             >>"..\output\VS2015.log"
MSBuild ToolBarDemo\ProjectFiles\ToolBarDemo_2015.sln /p:Configuration=Release           >>"..\output\VS2015.log"
MSBuild ToolTips\ProjectFiles\ToolTips_2015.sln /p:Configuration=Debug                   >>"..\output\VS2015.log"
MSBuild ToolTips\ProjectFiles\ToolTips_2015.sln /p:Configuration=Release                 >>"..\output\VS2015.log"
MSBuild Tray\ProjectFiles\Tray_2015.sln /p:Configuration=Debug                           >>"..\output\VS2015.log"
MSBuild Tray\ProjectFiles\Tray_2015.sln /p:Configuration=Release                         >>"..\output\VS2015.log"

mkdir "..\output\VS2015"
mkdir "..\output\VS2015\Debug"

ECHO "Copying Debug Samples" >>"..\output\VS2015.log"
copy Animation\ProjectFiles\Debug\Animation.exe               "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Browser\ProjectFiles\Debug\Browser.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy CommonDialogs\ProjectFiles\Debug\CommonDialogs.exe       "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy ContextHelp\ProjectFiles\Debug\ContextHelp.exe           "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy CustomControl\ProjectFiles\Debug\CustomControl.exe       "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DateTime\ProjectFiles\Debug\DateTime.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DDXDemo\ProjectFiles\Debug\DDXDemo.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Dialog\ProjectFiles\Debug\Dialog.exe                     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DialogBars\ProjectFiles\Debug\DialogBars.exe             "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DialogDemo\ProjectFiles\Debug\DialogDemo.exe             "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DialogResizing\ProjectFiles\Debug\DialogResizing.exe     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DialogTab\ProjectFiles\Debug\DialogTab.exe               "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Direct2D\ProjectFiles\Debug\Direct2D.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DirectX9\ProjectFiles\Debug\DirectX9.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DirectX11\ProjectFiles\Debug\DirectX11.exe               "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DirectX11\ProjectFiles\DirectX11.fx                      "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DLL\ProjectFiles\Debug\MyDLL.dll                         "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DLL\ProjectFiles\Debug\TestDLL.exe                       "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Dock\ProjectFiles\Debug\Dock.exe                         "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DockContainer\ProjectFiles\Debug\DockContainer.exe       "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DockTabbedMDI\ProjectFiles\Debug\DockTabbedMDI.exe       "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy DoubleBuffer\ProjectFiles\Debug\DoubleBuffer.exe         "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Explorer\ProjectFiles\Debug\Explorer.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy FastGDI\ProjectFiles\Debug\FastGDI.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy FilePrintPreview\ProjectFiles\Debug\FilePrintPreview.exe "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy FormDocView\ProjectFiles\Debug\FormDemo.exe              "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Frame\ProjectFiles\Debug\Frame.exe                       "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy INIFrame\ProjectFiles\Debug\INIFrame.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy GDIPlus\ProjectFiles\Debug\GDIPlus.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy MDIDockFrame\ProjectFiles\Debug\MDIDockFrame.exe         "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy MDIFrame\ProjectFiles\Debug\MDIFrame.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy MDIFrameDemo\ProjectFiles\Debug\MDIDemo.exe              "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy MDIFrameSplitter\ProjectFiles\Debug\MDIFrameSplitter.exe "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy MetaFile\ProjectFiles\Debug\MetaFile.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy NetClient\ProjectFiles\Debug\NetClient.exe               "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy NetClientAsync\ProjectFiles\Debug\NetClientAsync.exe     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy NetServer\ProjectFiles\Debug\NetServer.exe               "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy NetServerAsync\ProjectFiles\Debug\NetServerAsync.exe     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy NotePad\ProjectFiles\Debug\Notepad.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Performance\ProjectFiles\Debug\Performance.exe           "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Picture\ProjectFiles\Debug\Picture.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy PrintPreview\ProjectFiles\Debug\PrintPreview.exe         "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy PropertySheet\ProjectFiles\Debug\PropertySheet.exe       "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy ReBarDemo\ProjectFiles\Debug\ReBarDemo.exe               "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy RibbonDockFrame\ProjectFiles\Debug\RibbonDockFrame.exe   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy RibbonFrame\ProjectFiles\Debug\RibbonFrame.exe           "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy RibbonMDIFrame\ProjectFiles\Debug\RibbonMDIFrame.exe     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy RibbonSimple\ProjectFiles\Debug\SimpleRibbon.exe         "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy RoundWindow\ProjectFiles\Debug\Round.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Scribble\ProjectFiles\Debug\Scribble.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy ScrollTextFile\ProjectFiles\Debug\ScrollTextFile.exe     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Simple\ProjectFiles\Debug\Simple.exe                     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Splitter\ProjectFiles\Debug\Splitter.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy StatusBar\ProjectFiles\Debug\StatusBar.exe               "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy StatusBarEx\ProjectFiles\Debug\StatusBarEx.exe           "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy TabDemo\ProjectFiles\Debug\TabDemo.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy TaskDialog\ProjectFiles\Debug\TaskDialog.exe             "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Themes\ProjectFiles\Debug\Themes.exe                     "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Threads\ProjectFiles\Debug\Threads.exe                   "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy TimeDemo\ProjectFiles\Debug\TimeDemo.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy ToolBarDemo\ProjectFiles\Debug\ToolBarDemo.exe           "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy ToolTips\ProjectFiles\Debug\ToolTips.exe                 "..\output\VS2015\Debug"    >>"..\output\VS2015.log"
copy Tray\ProjectFiles\Debug\Tray.exe                         "..\output\VS2015\Debug"    >>"..\output\VS2015.log"

mkdir "..\output\VS2015\Release"

ECHO "Copying Release Samples" >>"..\output\VS2015.log"
copy Animation\ProjectFiles\Release\Animation.exe             "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Browser\ProjectFiles\Release\Browser.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy CommonDialogs\ProjectFiles\Release\CommonDialogs.exe     "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy ContextHelp\ProjectFiles\Release\ContextHelp.exe         "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy CustomControl\ProjectFiles\Release\CustomControl.exe     "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DateTime\ProjectFiles\Release\DateTime.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DDXDemo\ProjectFiles\Release\DDXDemo.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Dialog\ProjectFiles\Release\Dialog.exe                   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DialogBars\ProjectFiles\Release\DialogBars.exe           "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DialogDemo\ProjectFiles\Release\DialogDemo.exe           "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DialogResizing\ProjectFiles\Release\DialogResizing.exe   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DialogTab\ProjectFiles\Release\DialogTab.exe             "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Direct2D\ProjectFiles\Release\Direct2D.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DirectX9\ProjectFiles\Release\DirectX9.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DirectX11\ProjectFiles\Release\DirectX11.exe             "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DirectX11\ProjectFiles\DirectX11.fx                      "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DLL\ProjectFiles\Release\MyDLL.dll                       "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DLL\ProjectFiles\Release\TestDLL.exe                     "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Dock\ProjectFiles\Release\Dock.exe                       "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DockContainer\ProjectFiles\Release\DockContainer.exe     "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DockTabbedMDI\ProjectFiles\Release\DockTabbedMDI.exe     "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy DoubleBuffer\ProjectFiles\Release\DoubleBuffer.exe       "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Explorer\ProjectFiles\Release\Explorer.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy FastGDI\ProjectFiles\Release\FastGDI.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy FilePrintPreview\ProjectFiles\Release\FilePrintPreview.exe "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy FormDocView\ProjectFiles\Release\FormDemo.exe            "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Frame\ProjectFiles\Release\Frame.exe                     "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy INIFrame\ProjectFiles\Release\INIFrame.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy GDIPlus\ProjectFiles\Release\GDIPlus.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy MDIDockFrame\ProjectFiles\Release\MDIDockFrame.exe       "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy MDIFrame\ProjectFiles\Release\MDIFrame.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy MDIFrameDemo\ProjectFiles\Release\MDIDemo.exe            "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy MDIFrameSplitter\ProjectFiles\Release\MDIFrameSplitter.exe "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy MetaFile\ProjectFiles\Release\MetaFile.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy NetClient\ProjectFiles\Release\NetClient.exe             "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy NetClientAsync\ProjectFiles\Release\NetClientAsync.exe   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy NetServer\ProjectFiles\Release\NetServer.exe             "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy NetServerAsync\ProjectFiles\Release\NetServerAsync.exe   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy NotePad\ProjectFiles\Release\Notepad.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Performance\ProjectFiles\Release\Performance.exe         "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Picture\ProjectFiles\Release\Picture.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy PrintPreview\ProjectFiles\Release\PrintPreview.exe       "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy PropertySheet\ProjectFiles\Release\PropertySheet.exe     "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy ReBarDemo\ProjectFiles\Release\ReBarDemo.exe             "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy RibbonDockFrame\ProjectFiles\Release\RibbonDockFrame.exe "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy RibbonFrame\ProjectFiles\Release\RibbonFrame.exe         "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy RibbonMDIFrame\ProjectFiles\Release\RibbonMDIFrame.exe   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy RibbonSimple\ProjectFiles\Release\SimpleRibbon.exe       "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy RoundWindow\ProjectFiles\Release\Round.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Scribble\ProjectFiles\Release\Scribble.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy ScrollTextFile\ProjectFiles\Release\ScrollTextFile.exe   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Simple\ProjectFiles\Release\Simple.exe                   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Splitter\ProjectFiles\Release\Splitter.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy StatusBar\ProjectFiles\Release\StatusBar.exe             "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy StatusBarEx\ProjectFiles\Release\StatusBarEx.exe         "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy TabDemo\ProjectFiles\Release\TabDemo.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy TaskDialog\ProjectFiles\Release\TaskDialog.exe           "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Themes\ProjectFiles\Release\Themes.exe                   "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Threads\ProjectFiles\Release\Threads.exe                 "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy TimeDemo\ProjectFiles\Release\TimeDemo.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy ToolBarDemo\ProjectFiles\Release\ToolBarDemo.exe         "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy ToolTips\ProjectFiles\Release\ToolTips.exe               "..\output\VS2015\Release"    >>"..\output\VS2015.log"
copy Tray\ProjectFiles\Release\Tray.exe                       "..\output\VS2015\Release"    >>"..\output\VS2015.log"


REM: Change the directory to the Tutorials parent
popd
pushd ..\Tutorials

REM: Compile Tutorials
ECHO "Compiling Tutorials" >>"..\output\VS2015.log"
::Compile code
MSBuild Tutorial1\Tutorial1_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial1\Tutorial1_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial2\Tutorial2_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial2\Tutorial2_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial3\Tutorial3_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial3\Tutorial3_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial4\Tutorial4_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial4\Tutorial4_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial5\Tutorial5_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial5\Tutorial5_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial6\Tutorial6_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial6\Tutorial6_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial7\Tutorial7_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial7\Tutorial7_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial8\Tutorial8_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial8\Tutorial8_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial9\Tutorial9_2015.sln /p:Configuration=Debug       >>"..\output\VS2015.log"
MSBuild Tutorial9\Tutorial9_2015.sln /p:Configuration=Release     >>"..\output\VS2015.log"
MSBuild Tutorial10\Tutorial10_2015.sln /p:Configuration=Debug     >>"..\output\VS2015.log"
MSBuild Tutorial10\Tutorial10_2015.sln /p:Configuration=Release   >>"..\output\VS2015.log"

mkdir "..\output\VS2015\Tutorials"
mkdir "..\output\VS2015\Tutorials\Debug"

ECHO "Copying Debug Tutorials" >>"..\output\VS2015.log"
copy Tutorial1\Debug\Tutorial1.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial2\Debug\Tutorial2.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial3\Debug\Tutorial3.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial4\Debug\Tutorial4.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial5\Debug\Tutorial5.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial6\Debug\Tutorial6.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial7\Debug\Tutorial7.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial8\Debug\Tutorial8.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial9\Debug\Tutorial9.exe         "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"
copy Tutorial10\Debug\Tutorial10.exe       "..\output\VS2015\Tutorials\Debug"    >>"..\output\VS2015.log"

mkdir "..\output\VS2015\Tutorials\Release"

ECHO "Copying Release Tutorials" >>"..\output\VS2015.log"
copy Tutorial1\Release\Tutorial1.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial2\Release\Tutorial2.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial3\Release\Tutorial3.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial4\Release\Tutorial4.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial5\Release\Tutorial5.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial6\Release\Tutorial6.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial7\Release\Tutorial7.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial8\Release\Tutorial8.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial9\Release\Tutorial9.exe       "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"
copy Tutorial10\Release\Tutorial10.exe     "..\output\VS2015\Tutorials\Release"    >>"..\output\VS2015.log"

REM: Pop the directory change off the stack
popd


