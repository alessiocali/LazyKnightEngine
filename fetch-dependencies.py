import os.path
import subprocess
import json

is_on_windows = os.name == "nt"

def is_vcpkg_initialized():
    if is_on_windows:
        return os.path.isfile("vcpkg/vcpkg.exe")
    else:
        return os.path.isfile("vcpkg/vcpkg")

if not is_vcpkg_initialized():
    vcpkg_script = "vcpkg\\bootstrap-vcpkg.bat" if is_on_windows else "./vcpkg/bootstrap-vcpkg.sh"
    print("Initializing vcpkg: {0}".format(vcpkg_script))
    subprocess.check_call(vcpkg_script)

dependencies_root = { }

with open("dependencies.json") as deps_file:
    dependencies_root = json.load(deps_file)

for dependency in dependencies_root["dependencies"]:
    print("Installing {0}...".format(dependency["name"]))
    vcpkg_command = "vcpkg\\vcpkg" if is_on_windows else "./vcpkg/vcpkg"
    subprocess.call([ vcpkg_command, "install", dependency["VCPKG-ID"] ])