# controller_client
# Run the package


```
roslaunch controllert_client joytotwist.launch
```

# topic

| message type | topic name |
| ---- | ---- |
| geometry_msgs::Twist       | /controller_client/cmd_vel |
| geometry_msgs::Twist       | /controller_client/manipulator_vel |
| std_msgs::Int32            | /controller_client/share_button |
| std_msgs::Bool             | /controller_client/emg_switch |
| std_msgs::Int32            | /controller_client/mode_switch |
| std_msgs::Int32MultiArray  | /controller_client/all_buttons |
