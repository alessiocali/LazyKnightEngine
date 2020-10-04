import os
import sys
import pathlib
import shutil
import json
import subprocess

DIR_ARG_IDX = 1

is_on_windows = os.name == "nt"

def is_empty(dir : pathlib.Path):
    return len(dir.glob('*')) > 0

argn = len(sys.argv)

## RUN PRECONDITIONS ##

if argn <= DIR_ARG_IDX:
    print("Usage: python generate-projects.py <project-directory>")
    exit(0)

target_dir = pathlib.Path(sys.argv[DIR_ARG_IDX])

if (target_dir.exists()):
    print("Error: destination exists ")
    exit(1)

vcpkg_dir = pathlib.Path().cwd() / "vcpkg"
if (not vcpkg_dir.exists()):
    print("VCPKG directory cannot be found. Are you running from a different directory or forgot to initialize the submodule?")
    exit(3)

vcpkg_exe = vcpkg_dir / ("vcpkg.exe" if is_on_windows else "vcpkg")
if (not vcpkg_exe.exists()):
    print("VCPKG executable cannot be found. Run fetch-dependencies.py first.")
    exit(4)

## GENERATION CODE ##

print("Copying template...")
template_dir = pathlib.Path().cwd() / "project_template"
shutil.copytree(template_dir, target_dir)

dependencies_root = { }
with open("dependencies.json") as deps_file:
    dependencies_root = json.load(deps_file)

dependency_list = list()
for dependency in dependencies_root["dependencies"]:
    dependency_list += [dependency["VCPKG-ID"]]

print("Generating VCPKG exports...")
command_list = [ str(vcpkg_exe), "export" ] + dependency_list + ["--raw"]
subprocess.check_call(command_list)

matched_exports = [ export for export in vcpkg_dir.glob("vcpkg-export*") if export.is_dir() ]
export_count = len(matched_exports)

if export_count == 0:
    print("Error: vcpkg doesn't seem to have generated an export directory correctly.")
    exit(5)

elif export_count > 1:
    print("Warning: more than one export detected. The latest export will be used")

export_to_move = matched_exports[export_count - 1]
vcpkg_dst = target_dir / "vcpkg"

print("Moving export " + str(export_to_move) + "...")
shutil.copytree(export_to_move, vcpkg_dst)

print("Cleaning up...")
shutil.rmtree(export_to_move)