# FAST-LIO2 ROS 2 Runtime Package

This is the Fast-LIO front-end used by the parent [`FAST_LIO_SLAM_ROS2`](https://github.com/ravnbudde/FAST_LIO_SLAM_ROS2) stack.

For full SLAM usage, composed launch commands, topic wiring, and SC-PGO integration, see the parent repository README.

## What This Fork Provides

- ROS 2 package name: `fast_lio`
- Standalone executable: `fastlio_mapping`
- Composable node plugin: `fast_lio::LaserMappingNode`
- Standard PointCloud2 input support by default
- Optional Livox support behind the `FAST_LIO_ENABLE_LIVOX` CMake option
- Runtime configs under `config/`
- Runtime RViz config under `rviz/`

## Why This Package Is Trimmed

The upstream Fast-LIO repository includes papers, GIFs, result images, debug examples, and other documentation assets. Those files are useful for research/reference, but they are not needed on an onboard robot or in the composed full SLAM runtime. They were removed here to keep the submodule small and deployment-focused.

Removed from this fork/runtime branch:

- `doc/` papers, GIFs, screenshots, and result images
- `.github/` maintenance metadata
- old `rviz_cfg/` duplicate config
- old ROS 1-style GDB debug launch

Kept intentionally:

- `src/`, `include/`, `msg/`, `config/`, `launch/`, `rviz/`
- `Log/` and `PCD/` placeholders, because optional runtime logging/PCD saving still writes there
- `.gitmodules`, because `include/ikd-Tree` is a nested submodule dependency

## Standalone Usage

Build from the workspace root:

```bash
colcon build --packages-select fast_lio
source install/setup.bash
```

Run standalone:

```bash
ros2 run fast_lio fastlio_mapping --ros-args --params-file <config.yaml>
```

Or use the package launch files:

```bash
ros2 launch fast_lio mapping.launch.py config_file:=lw_vlp16.yaml
ros2 launch fast_lio mapping_composed.launch.py config_file:=lw_vlp16.yaml
```

## Full Stack Usage

The preferred full SLAM path is through the parent bringup package:

```bash
ros2 launch fast_lio_slam_bringup fast_lio_slam.launch.py
```

That launch composes this node with SC-PGO in one component container and remaps Fast-LIO outputs to stable stack topics such as `/fast_lio_slam/odometry/local` and `/fast_lio_slam/points/body`.
