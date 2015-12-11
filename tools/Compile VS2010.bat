REM: A batch program to rebuild the Win32++ samples using VS2010.
REM: The contents of the log file is erased 

REM: Set the paths and environment variables
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86

::Cleanup
call CleanSamples
call CleanTutorials

@echo on

REM: Change the directory to the Samples parent
pushd ..\Samples
if exist "..\output\VS2010\Debug" rmdir /s /q "..\output\VS2010\Debug"
if exist "..\output\VS2010\Release" rmdir /s /q "..\output\VS2010\Release"
if exist "..\output\VS2010\Tutorials" rmdir /s /q "..\output\VS2010\Tutorials"


::Compile code
devenv /build Debug Browser\ProjectFiles\Browser_2010.sln               > "..\output\VS2010.log"
devenv /build Release Browser\ProjectFiles\Browser_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug CustomControl\ProjectFiles\CustomControl_2010.sln   >>"..\output\VS2010.log"
devenv /build Release CustomControl\ProjectFiles\CustomControl_2010.sln >>"..\output\VS2010.log"
devenv /build Debug DateTime\ProjectFiles\DateTime_2010.sln             >>"..\output\VS2010.log"
devenv /build Release DateTime\ProjectFiles\DateTime_2010.sln           >>"..\output\VS2010.log"
devenv /build Debug DDXDemo\ProjectFiles\DDXDemo_2010.sln               >>"..\output\VS2010.log"
devenv /build Release DDXDemo\ProjectFiles\DDXDemo_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug Dialog\ProjectFiles\Dialog_2010.sln                 >>"..\output\VS2010.log"
devenv /build Release Dialog\ProjectFiles\Dialog_2010.sln               >>"..\output\VS2010.log"
devenv /build Debug DialogBars\ProjectFiles\DialogBars_2010.sln         >>"..\output\VS2010.log"
devenv /build Release DialogBars\ProjectFiles\DialogBars_2010.sln       >>"..\output\VS2010.log"
devenv /build Debug DialogDemo\ProjectFiles\DialogDemo_2010.sln         >>"..\output\VS2010.log"
devenv /build Release DialogDemo\ProjectFiles\DialogDemo_2010.sln       >>"..\output\VS2010.log"
devenv /build Debug DialogResizing\ProjectFiles\DialogResizing_2010.sln   >>"..\output\VS2010.log"
devenv /build Release DialogResizing\ProjectFiles\DialogResizing_2010.sln >>"..\output\VS2010.log"
devenv /build Debug DialogTab\ProjectFiles\DialogTab_2010.sln           >>"..\output\VS2010.log"
devenv /build Release DialogTab\ProjectFiles\DialogTab_2010.sln         >>"..\output\VS2010.log"
devenv /build Debug DirectX\ProjectFiles\DirectX_2010.sln               >>"..\output\VS2010.log"
devenv /build Release DirectX\ProjectFiles\DirectX_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug DLL\ProjectFiles\MakeDLL_2010.sln                   >>"..\output\VS2010.log"
devenv /build Release DLL\ProjectFiles\MakeDLL_2010.sln                 >>"..\output\VS2010.log"
devenv /build Debug DLL\ProjectFiles\TestDLL_2010.sln                   >>"..\output\VS2010.log"
devenv /build Release DLL\ProjectFiles\TestDLL_2010.sln                 >>"..\output\VS2010.log"
devenv /build Debug Dock\ProjectFiles\Dock_2010.sln                     >>"..\output\VS2010.log"
devenv /build Release Dock\ProjectFiles\Dock_2010.sln                   >>"..\output\VS2010.log"
devenv /build Debug DockContainer\ProjectFiles\DockContainer_2010.sln   >>"..\output\VS2010.log"
devenv /build Release DockContainer\ProjectFiles\DockContainer_2010.sln >>"..\output\VS2010.log"
devenv /build Debug DockMDI\ProjectFiles\DockMDIFrame_2010.sln          >>"..\output\VS2010.log"
devenv /build Release DockMDI\ProjectFiles\DockMDIFrame_2010.sln        >>"..\output\VS2010.log"
devenv /build Debug DockTabbedMDI\ProjectFiles\DockTabbedMDI_2010.sln   >>"..\output\VS2010.log"
devenv /build Release DockTabbedMDI\ProjectFiles\DockTabbedMDI_2010.sln >>"..\output\VS2010.log"
devenv /build Debug DoubleBuffer\ProjectFiles\DoubleBuffer_2010.sln     >>"..\output\VS2010.log"
devenv /build Release DoubleBuffer\ProjectFiles\DoubleBuffer_2010.sln   >>"..\output\VS2010.log"
devenv /build Debug Explorer\ProjectFiles\Explorer_2010.sln             >>"..\output\VS2010.log"
devenv /build Release Explorer\ProjectFiles\Explorer_2010.sln           >>"..\output\VS2010.log"
devenv /build Debug FastGDI\ProjectFiles\FastGDI_2010.sln               >>"..\output\VS2010.log"
devenv /build Release FastGDI\ProjectFiles\FastGDI_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug FormDocView\ProjectFiles\FormDemo_2010.sln          >>"..\output\VS2010.log"
devenv /build Release FormDocView\ProjectFiles\FormDemo_2010.sln        >>"..\output\VS2010.log"
devenv /build Debug Frame\ProjectFiles\Frame_2010.sln                   >>"..\output\VS2010.log"
devenv /build Release Frame\ProjectFiles\Frame_2010.sln                 >>"..\output\VS2010.log"
devenv /build Debug INIFrame\ProjectFiles\INIFrame_2010.sln             >>"..\output\VS2010.log"
devenv /build Release INIFrame\ProjectFiles\INIFrame_2010.sln           >>"..\output\VS2010.log"
devenv /build Debug GDIPlus\ProjectFiles\GDIPlus_2010.sln               >>"..\output\VS2010.log"
devenv /build Release GDIPlus\ProjectFiles\GDIPlus_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug MDIFrame\ProjectFiles\MDIFrame_2010.sln             >>"..\output\VS2010.log"
devenv /build Release MDIFrame\ProjectFiles\MDIFrame_2010.sln           >>"..\output\VS2010.log"
devenv /build Debug MDIFrameDemo\ProjectFiles\MDIDemo_2010.sln          >>"..\output\VS2010.log"
devenv /build Release MDIFrameDemo\ProjectFiles\MDIDemo_2010.sln        >>"..\output\VS2010.log"
devenv /build Debug MDIFrameSplitter\ProjectFiles\MDIFrameSplitter_2010.sln >>"..\output\VS2010.log"
devenv /build Release MDIFrameSplitter\ProjectFiles\MDIFrameSplitter_2010.sln >>"..\output\VS2010.log"
devenv /build Debug NetClient\ProjectFiles\NetClient_2010.sln           >>"..\output\VS2010.log"
devenv /build Release NetClient\ProjectFiles\NetClient_2010.sln         >>"..\output\VS2010.log"
devenv /build Debug NetServer\ProjectFiles\NetServer_2010.sln           >>"..\output\VS2010.log"
devenv /build Release NetServer\ProjectFiles\NetServer_2010.sln         >>"..\output\VS2010.log"
devenv /build Debug NotePad\ProjectFiles\Notepad_2010.sln               >>"..\output\VS2010.log"
devenv /build Release NotePad\ProjectFiles\Notepad_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug Performance\ProjectFiles\Performance_2010.sln       >>"..\output\VS2010.log"
devenv /build Release Performance\ProjectFiles\Performance_2010.sln     >>"..\output\VS2010.log"
devenv /build Debug Picture\ProjectFiles\Picture_2010.sln               >>"..\output\VS2010.log"
devenv /build Release Picture\ProjectFiles\Picture_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug PropertySheet\ProjectFiles\PropertySheet_2010.sln   >>"..\output\VS2010.log"
devenv /build Release PropertySheet\ProjectFiles\PropertySheet_2010.sln >>"..\output\VS2010.log"
devenv /build Debug ReBarDemo\ProjectFiles\ReBarDemo_2010.sln           >>"..\output\VS2010.log"
devenv /build Release ReBarDemo\ProjectFiles\ReBarDemo_2010.sln         >>"..\output\VS2010.log"
devenv /build Debug RibbonFrame\ProjectFiles\RibbonFrame_2010.sln       >>"..\output\VS2010.log"
devenv /build Release RibbonFrame\ProjectFiles\RibbonFrame_2010.sln     >>"..\output\VS2010.log"
devenv /build Debug RibbonSimple\ProjectFiles\SimpleRibbon_2010.sln     >>"..\output\VS2010.log"
devenv /build Release RibbonSimple\ProjectFiles\SimpleRibbon_2010.sln   >>"..\output\VS2010.log"
devenv /build Debug RoundWindow\ProjectFiles\Round_2010.sln             >>"..\output\VS2010.log"
devenv /build Release RoundWindow\ProjectFiles\Round_2010.sln           >>"..\output\VS2010.log"
devenv /build Debug Scribble\ProjectFiles\Scribble_2010.sln             >>"..\output\VS2010.log"
devenv /build Release Scribble\ProjectFiles\Scribble_2010.sln           >>"..\output\VS2010.log"
devenv /build Debug Simple\ProjectFiles\Simple_2010.sln                 >>"..\output\VS2010.log"
devenv /build Release Simple\ProjectFiles\Simple_2010.sln               >>"..\output\VS2010.log"
devenv /build Debug Splitter\ProjectFiles\Splitter_2010.sln             >>"..\output\VS2010.log"
devenv /build Release StatusBar\ProjectFiles\StatusBar_2010.sln         >>"..\output\VS2010.log"
devenv /build Debug StatusBar\ProjectFiles\StatusBar_2010.sln           >>"..\output\VS2010.log"
devenv /build Release Splitter\ProjectFiles\Splitter_2010.sln           >>"..\output\VS2010.log"
devenv /build Debug TabDemo\ProjectFiles\TabDemo_2010.sln               >>"..\output\VS2010.log"
devenv /build Release TabDemo\ProjectFiles\TabDemo_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug TaskDialog\ProjectFiles\TaskDialog_2010.sln         >>"..\output\VS2010.log"
devenv /build Release TaskDialog\ProjectFiles\TaskDialog_2010.sln       >>"..\output\VS2010.log"
devenv /build Debug Themes\ProjectFiles\Themes_2010.sln                 >>"..\output\VS2010.log"
devenv /build Release Themes\ProjectFiles\Themes_2010.sln               >>"..\output\VS2010.log"
devenv /build Debug Threads\ProjectFiles\Threads_2010.sln               >>"..\output\VS2010.log"
devenv /build Release Threads\ProjectFiles\Threads_2010.sln             >>"..\output\VS2010.log"
devenv /build Debug ToolBarDemo\ProjectFiles\ToolBarDemo_2010.sln       >>"..\output\VS2010.log"
devenv /build Release ToolBarDemo\ProjectFiles\ToolBarDemo_2010.sln     >>"..\output\VS2010.log"
devenv /build Debug Tray\ProjectFiles\Tray_2010.sln                     >>"..\output\VS2010.log"
devenv /build Release Tray\ProjectFiles\Tray_2010.sln                   >>"..\output\VS2010.log"

mkdir "..\output\VS2010"
mkdir "..\output\VS2010\Debug"

ECHO "Copying Debug Samples" >>"..\output\VS2010.log"
copy Browser\ProjectFiles\Debug\Browser.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy CustomControl\ProjectFiles\Debug\CustomControl.exe       "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DateTime\ProjectFiles\Debug\DateTime.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DDXDemo\ProjectFiles\Debug\DDXDemo.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Dialog\ProjectFiles\Debug\Dialog.exe                     "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DialogBars\ProjectFiles\Debug\DialogBars.exe             "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DialogDemo\ProjectFiles\Debug\DialogDemo.exe             "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DialogResizing\ProjectFiles\Debug\DialogResizing.exe     "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DialogTab\ProjectFiles\Debug\DialogTab.exe               "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DirectX\ProjectFiles\Debug\DirectX.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DLL\ProjectFiles\Debug\MyDLL.dll                         "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DLL\ProjectFiles\Debug\TestDLL.exe                       "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Dock\ProjectFiles\Debug\Dock.exe                         "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DockContainer\ProjectFiles\Debug\DockContainer.exe       "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DockMDI\ProjectFiles\Debug\DockMDIFrame.exe              "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DockTabbedMDI\ProjectFiles\Debug\DockTabbedMDI.exe       "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy DoubleBuffer\ProjectFiles\Debug\DoubleBuffer.exe         "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Explorer\ProjectFiles\Debug\Explorer.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy FastGDI\ProjectFiles\Debug\FastGDI.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy FormDocView\ProjectFiles\Debug\FormDemo.exe              "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Frame\ProjectFiles\Debug\Frame.exe                       "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy INIFrame\ProjectFiles\Debug\INIFrame.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy GDIPlus\ProjectFiles\Debug\GDIPlus.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy MDIFrame\ProjectFiles\Debug\MDIFrame.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy MDIFrameDemo\ProjectFiles\Debug\MDIDemo.exe              "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy MDIFrameSplitter\ProjectFiles\Debug\MDIFrameSplitter.exe "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy NetClient\ProjectFiles\Debug\NetClient.exe               "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy NetServer\ProjectFiles\Debug\NetServer.exe               "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy NotePad\ProjectFiles\Debug\Notepad.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Performance\ProjectFiles\Debug\Performance.exe           "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Picture\ProjectFiles\Debug\Picture.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy PropertySheet\ProjectFiles\Debug\PropertySheet.exe       "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy ReBarDemo\ProjectFiles\Debug\ReBarDemo.exe               "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy RibbonFrame\ProjectFiles\Debug\RibbonFrame.exe           "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy RibbonSimple\ProjectFiles\Debug\SimpleRibbon.exe         "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy RoundWindow\ProjectFiles\Debug\Round.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Scribble\ProjectFiles\Debug\Scribble.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Simple\ProjectFiles\Debug\Simple.exe                     "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Splitter\ProjectFiles\Debug\Splitter.exe                 "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy StatusBar\ProjectFiles\Debug\StatusBar.exe               "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy TabDemo\ProjectFiles\Debug\TabDemo.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy TaskDialog\ProjectFiles\Debug\TaskDialog.exe             "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Themes\ProjectFiles\Debug\Themes.exe                     "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Threads\ProjectFiles\Debug\Threads.exe                   "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy ToolBarDemo\ProjectFiles\Debug\ToolBarDemo.exe           "..\output\VS2010\Debug"    >>"..\output\VS2010.log"
copy Tray\ProjectFiles\Debug\Tray.exe                         "..\output\VS2010\Debug"    >>"..\output\VS2010.log"

mkdir "..\output\VS2010\Release"

ECHO "Copying Release Samples" >>"..\output\VS2010.log"
copy Browser\ProjectFiles\Release\Browser.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy CustomControl\ProjectFiles\Release\CustomControl.exe       "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DateTime\ProjectFiles\Release\DateTime.exe                 "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DDXDemo\ProjectFiles\Release\DDXDemo.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Dialog\ProjectFiles\Release\Dialog.exe                     "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DialogBars\ProjectFiles\Release\DialogBars.exe             "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DialogDemo\ProjectFiles\Release\DialogDemo.exe             "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DialogResizing\ProjectFiles\Release\DialogResizing.exe     "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DialogTab\ProjectFiles\Release\DialogTab.exe               "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DirectX\ProjectFiles\Release\DirectX.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DLL\ProjectFiles\Release\MyDLL.dll                         "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DLL\ProjectFiles\Release\TestDLL.exe                       "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Dock\ProjectFiles\Release\Dock.exe                         "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DockContainer\ProjectFiles\Release\DockContainer.exe       "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DockMDI\ProjectFiles\Release\DockMDIFrame.exe              "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DockTabbedMDI\ProjectFiles\Release\DockTabbedMDI.exe       "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy DoubleBuffer\ProjectFiles\Release\DoubleBuffer.exe         "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Explorer\ProjectFiles\Release\Explorer.exe                 "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy FastGDI\ProjectFiles\Release\FastGDI.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy FormDocView\ProjectFiles\Release\FormDemo.exe              "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Frame\ProjectFiles\Release\Frame.exe                       "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy INIFrame\ProjectFiles\Release\INIFrame.exe                 "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy GDIPlus\ProjectFiles\Release\GDIPlus.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy MDIFrame\ProjectFiles\Release\MDIFrame.exe                 "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy MDIFrameDemo\ProjectFiles\Release\MDIDemo.exe              "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy MDIFrameSplitter\ProjectFiles\Release\MDIFrameSplitter.exe "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy NetClient\ProjectFiles\Release\NetClient.exe               "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy NetServer\ProjectFiles\Release\NetServer.exe               "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy NotePad\ProjectFiles\Release\Notepad.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Performance\ProjectFiles\Release\Performance.exe           "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Picture\ProjectFiles\Release\Picture.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy PropertySheet\ProjectFiles\Release\PropertySheet.exe       "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy ReBarDemo\ProjectFiles\Release\ReBarDemo.exe               "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy RibbonFrame\ProjectFiles\Release\RibbonFrame.exe           "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy RibbonSimple\ProjectFiles\Release\SimpleRibbon.exe         "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy RoundWindow\ProjectFiles\Release\Round.exe                 "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Scribble\ProjectFiles\Release\Scribble.exe                 "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Simple\ProjectFiles\Release\Simple.exe                     "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Splitter\ProjectFiles\Release\Splitter.exe                 "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy StatusBar\ProjectFiles\Release\StatusBar.exe               "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy TabDemo\ProjectFiles\Release\TabDemo.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy TaskDialog\ProjectFiles\Release\TaskDialog.exe             "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Themes\ProjectFiles\Release\Themes.exe                     "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Threads\ProjectFiles\Release\Threads.exe                   "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy ToolBarDemo\ProjectFiles\Release\ToolBarDemo.exe           "..\output\VS2010\Release"    >>"..\output\VS2010.log"
copy Tray\ProjectFiles\Release\Tray.exe                         "..\output\VS2010\Release"    >>"..\output\VS2010.log"

REM: Change the directory to the Tutorials parent
popd
pushd ..\Tutorials

REM: Compile Tutorials
ECHO "Compiling Tutorials" >>"..\output\VS2010.log"
::Compile code
devenv /build Debug Tutorial1\Tutorial1_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial1\Tutorial1_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial2\Tutorial2_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial2\Tutorial2_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial3\Tutorial3_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial3\Tutorial3_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial4\Tutorial4_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial4\Tutorial4_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial5\Tutorial5_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial5\Tutorial5_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial6\Tutorial6_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial6\Tutorial6_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial7\Tutorial7_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial7\Tutorial7_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial8\Tutorial8_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial8\Tutorial8_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial9\Tutorial9_2010.sln      >>"..\output\VS2010.log"
devenv /build Release Tutorial9\Tutorial9_2010.sln    >>"..\output\VS2010.log"
devenv /build Debug Tutorial10\Tutorial10_2010.sln    >>"..\output\VS2010.log"
devenv /build Release Tutorial10\Tutorial10_2010.sln  >>"..\output\VS2010.log"

mkdir "..\output\VS2010\Tutorials"
mkdir "..\output\VS2010\Tutorials\Debug"

ECHO "Copying Debug Tutorials" >>"..\output\VS2010.log"
copy Tutorial1\Debug\Tutorial1.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial2\Debug\Tutorial2.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial3\Debug\Tutorial3.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial4\Debug\Tutorial4.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial5\Debug\Tutorial5.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial6\Debug\Tutorial6.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial7\Debug\Tutorial7.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial8\Debug\Tutorial8.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial9\Debug\Tutorial9.exe         "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"
copy Tutorial10\Debug\Tutorial10.exe       "..\output\VS2010\Tutorials\Debug"    >>"..\output\VS2010.log"

mkdir "..\output\VS2010\Tutorials\Release"

ECHO "Copying Release Tutorials" >>"..\output\VS2010.log"
copy Tutorial1\Release\Tutorial1.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial2\Release\Tutorial2.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial3\Release\Tutorial3.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial4\Release\Tutorial4.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial5\Release\Tutorial5.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial6\Release\Tutorial6.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial7\Release\Tutorial7.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial8\Release\Tutorial8.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial9\Release\Tutorial9.exe       "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"
copy Tutorial10\Release\Tutorial10.exe     "..\output\VS2010\Tutorials\Release"    >>"..\output\VS2010.log"

REM: Pop the directory change off the stack
popd


