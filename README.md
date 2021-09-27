# `maliput_drake`

A clone of [`drake`](https://github.com/RobotLocomotion/drake)'s trajectory integration support for `maliput` backends.

## Build

1. Setup a maliput_drake (or a wider maliput) development workspace as described [here](https://github.com/ToyotaResearchInstitute/maliput_documentation/blob/main/docs/installation_quickstart.rst).

2. Bring up your development workspace:

```sh
cd path/to/my/workspace
source /opt/ros/$ROS_DISTRO/setup.sh
```

where `$ROS_DISTRO` could be either `foxy` or `dashing`.

3. Build `maliput_drake` packages and their dependencies:

   ```sh
   colcon build --packages-up-to maliput_drake
   ```

## Use `maliput_drake` as a dependency

### Installed targets

The following targets are installed and can be used when adding `maliput_drake`
as an `ament` dependency.

- `maliput_drake::common`
- `maliput_drake::trajectories`
- `maliput_drake::math`
- `maliput_drake::analysis`
- `maliput_drake::framework`

All of them are shared libraries.

### Adding `maliput_drake` to you `package.xml`

When creating the `ament` package, make sure to add `maliput_drake` to your `package.xml`:

```xml
<depend>maliput_drake</depend>
```

### Finding the package

In your project, add the following to your `CMakeLists.txt` file to import the package:

```cmake
find_package(maliput_drake REQUIRED)
```

### Export the `ament` dependency

Make sure to export the dependency as follows:

```cmake
ament_export_dependencies(maliput_drake)
```

### Linking against the libraries

To link against one or man of the aforementioned targets, simply do the following:

```cmake
target_link_libraries(
  my_fancy_target
    PUBLIC # PRIVATE
    maliput_drake::analysis
    maliput_drake::common
    maliput_drake::framework
    maliput_drake::math
    maliput_drake::trajectories
)
```

Prefer `PRIVATE` linkage when possible to avoid any unneeded exposure of `drake`-specific
types.
