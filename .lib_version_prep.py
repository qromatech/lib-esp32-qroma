
import json
import os

print("GENERATING LIBRARY VERSION FILE - lib_ver.h")

lib_json = json.load(open("library.json"))
lib_version = lib_json["version"]

header_contents = f"""
#ifndef LIB_VER_QROMAPOINT_H
#define LIB_VER_QROMAPOINT_H

#define LIB_VER  "{lib_version}"


#endif
"""

with open(os.path.join("src", "qroma", "lib_ver.h"), "w") as  header_file:
  header_file.write(header_contents)
