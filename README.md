# `maliput_drake`

A clone of [`drake`](https://github.com/RobotLocomotion/drake)'s trajectory integration support for `maliput` backends.

## How to copy `drake` into `maliput_drake`?

### Copying files

To copy files from a [`drake`](https://github.com/RobotLocomotion/drake) release, please do the following:

1. Clone [`drake`](https://github.com/RobotLocomotion/drake) and point it to a
   specific release tag, e.g. [`v0.33.0`](https://github.com/RobotLocomotion/drake/releases/tag/v0.33.0):

```sh
git clone --depth 1 --branch v0.33.0 git@github.com:RobotLocomotion/drake.git $DRAKE_WS/drake
```

Please note the use of `DRAKE_WS` which is the path to `drake`'s workspace.

2. Follow the instructions for the release to prepare the environment and install `drake` dependencies.

3. Derive which dependencies are necessary up to `antiderivative_function` and `scalar_initial_value_problem`:

```sh
cd $DRAKE_WS/drake
bazel query 'deps(//systems/analysis:antiderivative_function)' | sed -e 's#:.*##g;' | sort | uniq
bazel query 'deps(//systems/analysis:scalar_initial_value_problem)' | sed -e 's#:.*##g;' | sort | uniq
```


4. Create a new branch in this repo (`maliput_drake`) to update the files.

```sh
cd src/maliput_drake
git checkout -b username/bump_to_drake_v0.33.0
```

5. Remove the previous contents of the folders in `maliput_drake/src` and `maliput_drake/include`:

```sh
find maliput_drake/src/ -name "*.cc" -type f -delete
find maliput_drake/include/ -name "*.h" -type f -delete
```

6. Copy the source files to the respective `maliput_drake/src` folder and the header files to the
   respective `maliput_drake/include/maliput` folder.

7. Make sure you remove unnecessary files:

```sh
maliput_drake/include/maliput/drake/common/drake_path.h
maliput_drake/include/maliput/drake/common/filesystem.h
maliput_drake/include/maliput/drake/common/find_loaded_library.h
maliput_drake/include/maliput/drake/common/find_resource.h
maliput_drake/include/maliput/drake/common/find_runfiles.h
maliput_drake/include/maliput/drake/common/temp_directory.h
maliput_drake/include/maliput/drake/systems/analysis/lyapunov.h
maliput_drake/include/maliput/drake/systems/analysis/region_of_attraction.h
maliput_drake/include/maliput/drake/systems/analysis/simulator_print_stats.h
maliput_drake/src/common/drake_path.cc
maliput_drake/src/common/filesystem.cc
maliput_drake/src/common/find_loaded_library.cc
maliput_drake/src/common/find_resource.cc
maliput_drake/src/common/find_runfiles.cc
maliput_drake/src/common/find_runfiles_stub.cc
maliput_drake/src/common/resource_tool.cc
maliput_drake/src/common/temp_directory.cc
maliput_drake/src/systems/analysis/lyapunov.cc
maliput_drake/src/systems/analysis/region_of_attraction.cc
maliput_drake/src/systems/analysis/simulator_print_stats.cc
```

8. Update the CMakeLists.txt under `maliput_drake/src/` for the library targets.
   Make sure all source files are properly listed.

9. Commit all the changes.

10. Run the steps listed in the `Namespacing` section. Make a new per change.

11. Test the workspace before making a PR.

### Namespacing

The following transformations are necessary to successfully namespace copied
files:

1. Replace occurrences of `namespace drake` by `namespace maliput::drake`.
2. Replace occurrences of `::drake` by `::maliput::drake`.
3. Replace occurrences of `#include "drake/` by `#include "maliput/drake`.
4. Replace occurrences of `<drake::` by `<maliput::drake`.
5. Replace occurrences of `(drake::` by `(maliput::drake::`.
6. Replace occurrences of ` drake::` by ` maliput::drake`.
7. Replace occurrences of `<::drake` by `<::maliput::drake`.

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
