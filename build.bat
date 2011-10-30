@call "%VS100COMNTOOLS%\vsvars32.bat"
@mkdir build
@cd build
@..\configure.py
@build.py
@cd ..
@pause