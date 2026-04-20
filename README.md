**Service definitions (input/output) :** ira2_ws/src/haptic_teleop/srv
- AppControlService.srv
- ContactPointService.srv
- SystemStateService.srv

**My scripts :** ira2_ws/src/haptic_teleop/src/service_tests
- unity_bridge_node.cpp : est le script qui combine les 3 autres scripts dans ce dossier


## Topic / Service Information
| Name         |  Type   | Direction (Client → Server) | Note                                                                    |
| :----------- | :-----: | :-------------------------- | :---------------------------------------------------------------------- |
| cp_position  | service | ROS → Unity                 | Request contact point position from Unity (returns geometry_msgs/Point) |
| system_state | service | ROS → Unity                 | Change experiment state (PreCalibration, Calibration, Punch, Push)      |
| app_control  | service | ROS → Unity                 | Control Unity app state (Play, Stop, Reset)                             |