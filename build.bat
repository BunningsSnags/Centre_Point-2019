@echo off
set input=%1
if %input% == master (
  echo Building Master
  cd MasterTeensy
  py -m platformio run
  cd ..
)
if %input% == slave (
  echo Building Slave
  cd SlaveTeensy
  platformio run
  cd..
)
