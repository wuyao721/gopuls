solution "GoPlus"
   location("build/")
   targetdir "bin"              
   libdirs { "C:/devenv/lib" }
   includedirs { "C:/devenv/include", "include", "."}
   implibdir "lib"              
   defines { "WIN32" }         
   configurations { "Debug", "Release" }
   flags { "NoIncrementalLink" }   
   
   configuration "Debug"
      defines { "DEBUG", "_DEBUG" }
      flags { "Symbols" }
      objdir "build/intermediate/Debug"
      targetsuffix "d"
   
   configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
      objdir "build/intermediate/Release"

   project "GoPlus"
      kind "WindowedApp"
      language "C++"
      files { 
	 "src/main.cpp",
	 "src/GoPlusContext.cpp",
         "src/SettingDialog.cpp",
         "src/MainDialog.cpp",
         "src/BaseDialog.cpp",
	 "src/ActiveObjectShell.cpp",
	 "res/StealthDialog.rc",
	 "include/GoPlusContext.h",

         --"src/GoPlusApp.cpp",
         "src/GoGameWatcher.cpp",
         "src/GoBoard.cpp",
	 "src/ScalableGoBoard.cpp",
	 "src/FixedGoBoard.cpp",
	 "src/EWeiQiGoBoard.cpp",
         "src/QQGoBoard.cpp",
         "src/GoGameFrame.cpp",
         "src/GoGamePiece.cpp",
         "src/GoGameRule.cpp",
	 "src/WindowBitmap.cpp",
	 "src/MetaMachine.cpp",
	 "src/ProcessHack_WIN32.cpp",

         --"include/GoPlusApp.h",
         "include/SettingDialog.h",
         "include/MainDialog.h",
         "include/BaseDialog.h",
         "include/GoGameWatcher.h",
         "include/GoBoard.h",
	 "include/ScalableGoBoard.h",
	 "include/FixedGoBoard.h",
	 "include/EWeiQiGoBoard.h",
         "include/QQGoBoard.h",
         "include/GoGameFrame.h",
         "include/GoGamePiece.h",
         "include/GoGameRule.h",
	 "include/WindowBitmap.h",
	 "include/MetaMachine.h",
	 "include/ProcessHack_WIN32.h",

      }
      includedirs { "include" }
      objdir "intermediate"
      flags { "WinMain" }
      --links {"comctl32"}

   project "hellowin"
      kind "WindowedApp"
      language "C++"
      files { 
         "ui/hellowin.cpp",
      }
      includedirs { "include" }
      objdir "intermediate"
      flags { "WinMain" }

   project "GetPixelApp"
      kind "ConsoleApp"
      language "C++"
      files { 
         "samples/GetPixelApp.cpp"
      }
      includedirs { "include" }
      objdir "intermediate"

   project "WindowBitmapTest"
      kind "ConsoleApp"
      language "C++"
      files { 
         "src/WindowBitmap.cpp",
         "include/WindowBitmap.h",
         "samples/WindowBitmapTest.cpp"
      }
      includedirs { "include" }
      objdir "intermediate"

   project "MetaMachineTest"
      kind "ConsoleApp"
      language "C++"
      files { 
         "samples/MetaMachineTest.cpp"
      }
      includedirs { "include" }
      objdir "intermediate"
      links { "MetaMachine" }

   project "MouseEventTest"
      kind "ConsoleApp"
      language "C++"
      files { 
         "samples/MouseEventTest.cpp"
      }
      includedirs { "include" }
      objdir "intermediate"

   project "atest"
      kind "ConsoleApp"
      language "C++"
      files { 
         "src/point.cpp"
      }
      includedirs { "include" }

   project "UIApp"
      kind "WindowedApp"
      language "C++"
      files { 
	 "ui/BaseWindow.cpp",
         "ui/DerivedWindow.cpp",
	 "ui/winmain.cpp"
      }
      includedirs { "include" }
      objdir "intermediate"
      flags { "WinMain" }

   project "testsuite"
      kind "WindowedApp"
      language "C++"
      files { 
         "testsuite/src/*.cpp"
      }
      includedirs { 
	 "include",
	 "include/CppUnit",
	 "include/CppUnit/WinTestRunner"
      }
      objdir "testsuite/intermediate"
      links{
	 "CppUnitd",
	 "WinTestRunnerd",
	 "PocoFoundationd"
      }
      flags { "WinMain", "MFC" }
