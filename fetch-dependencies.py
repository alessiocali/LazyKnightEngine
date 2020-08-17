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
    vcpkg_script = "bootstrap-vcpkg.{0}".format("bat" if is_on_windows else "sh")
    print("Initializing vcpkg: vcpkg/{0}".format(vcpkg_script))
    subprocess.check_call(vcpkg_script, cwd="vcpkg", shell=True)

dependencies_root = { }

with open("dependencies.json") as deps_file:
    dependencies_root = json.load(deps_file)

for dependency in dependencies_root["dependencies"]:
    print("Installing {0}...".format(dependency["name"]))
    subprocess.call([ "vcpkg", "install", dependency["VCPKG-ID"] ], cwd="vcpkg", shell=True)
