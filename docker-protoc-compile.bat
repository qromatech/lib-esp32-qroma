set IMAGE_NAME=devalbo/qroma-protobuf-compiler:v2
set CONTAINER_NAME=qroma-protobuf-compiler-1

rmdir /S /Q protofiles-out

set LOCAL_SOURCE_DIR=%CD%\protofiles-in
set DOCKER_SOURCE_DIR=/usr/src/app/protofiles

set LOCAL_BUILD_DIR=%CD%\protofiles-out
set DOCKER_BUILD_DIR=/usr/src/app/outfiles

docker container run -it --name %CONTAINER_NAME% -v %LOCAL_SOURCE_DIR%:%DOCKER_SOURCE_DIR% -v %LOCAL_BUILD_DIR%:%DOCKER_BUILD_DIR% %IMAGE_NAME%

docker container rm %CONTAINER_NAME%


set OUT_DIR=.\src\proto-nanopb
set PYTHON_OUT_DIR=..\py-qroma-strip\qroma_pb

rmdir /S /Q %OUT_DIR%
mkdir %OUT_DIR%
copy protofiles-out\nanopb\* %OUT_DIR%


copy protofiles-out\python\* %PYTHON_OUT_DIR%
