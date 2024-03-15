
import json
import os

print("GENERATING LIBRARY VERSION FILE - lib_version.h")

lib_json = json.load(open("library.json"))
lib_version = lib_json["version"]

header_contents = f"""
#ifndef LIB_VERSION_QROMA_LIB_H
#define LIB_VERSION_QROMA_LIB_H

#define QROMA_LIB_FW_VERSION  "{lib_version}"

extern const char * QromaProjectFirmwareVersion;


#endif
"""

with open(os.path.join("src", "qroma", "lib_version.h"), "w") as  header_file:
  header_file.write(header_contents)
