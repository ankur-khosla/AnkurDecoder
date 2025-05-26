@echo off

REM C:\Work\Git\APR2021\edabi\DecodeModule\DECODER\x64\Release\oltp_ab.dll
set TargetFile=%1
set ProjectName=%2

REM  1.---------------get parent folder from SolutionDir
cd..
cd..
cd..

echo Current Folder is: %cd%
set edabiFolder=%cd%
echo EDABI Folder is       : %edabiFolder%

REM is 'C:\GIT_REP\edabi\APP_Setup'
set AppSetupDir="%edabiFolder%\APP_Setup"
set ThirdLibDir="%edabiFolder%\EDA Project\3rdpartylib\decoder"
set DecodeLibDir="%edabiFolder%\EDA Project\DecodeLibrary"

echo "===================================================================="
echo TargetFile is           : %TargetFile%
echo AppSetupDir is			 : %AppSetupDir%
echo 3rdLibraryDir is	     : %ThirdLibDir%
echo DecodeLibraryDir is     : %DecodeLibDir%
echo "===================================================================="

REM MAIN START
echo copy /y "%TargetFile%\%ProjectName%.dll" %AppSetupDir%
copy /y "%TargetFile%\%ProjectName%.dll" %AppSetupDir%

echo copy /y "%TargetFile%\%ProjectName%.dll" %ThirdLibDir%
copy /y "%TargetFile%\%ProjectName%.dll" %ThirdLibDir%

echo copy /y "%TargetFile%\%ProjectName%.dll" %DecodeLibDir%
copy /y "%TargetFile%\%ProjectName%.dll" %DecodeLibDir%

REM MAIN END
	
:bat_end
echo END 

REM BAT END
 
