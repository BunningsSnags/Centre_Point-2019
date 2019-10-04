@echo off
set input=%1
if %input% == master (
  echo Uploading and Monitoring to Master
  cd MasterTeensy
  py -m platformio run -t upload
  pio device monitor
  cd ..
)
if %input% == slave (
  echo Uploading and Monitoring to Slave
  cd SlaveTeensy
  platformio run -t upload
  pio device monitor
  cd ..
)