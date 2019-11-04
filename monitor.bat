@echo off
set input=%1
if %input% == master (
  echo Monitoring Master
  cd MasterTeensy
  pio device monitor
  cd ..
)
if %input% == slave (
  echo Monitoring Slave
  cd SlaveTeensy
  pio device monitor
  cd ..
)