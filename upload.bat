@echo off
set input=%1
if %input% == master (
  echo Uploading to Master
  cd MasterTeensy
  py -m platformio run -t upload
  cd ..
)
if %input% == slave (
  echo Uploading to Slave
  cd SlaveTeensy
  platformio run -t upload
  cd..
)