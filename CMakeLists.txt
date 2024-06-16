cmake_minimum_required(VERSION 3.2)

project(chatProject)
#设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g )
#设置可执行文件编译输出位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#项目头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/client)
include_directories(${PROJECT_SOURCE_DIR}/include/DB)
include_directories(${PROJECT_SOURCE_DIR}/include/DAO)

#muduo头文件路径
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/include/muduo/net)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/include/muduo/base)
#json头文件路径
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/include/json)

#formatter头文件
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/include/others)

#mysql C++连接器头文件路径
include_directories(/usr/include/cppconn)


aux_source_directory(./src/server SRC_LIST)
aux_source_directory(./src/DB DB_LIST)
aux_source_directory(./src/DAO DAO_LIST)

#muduo库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/thirdparty/lib/muduo)
link_directories(${PROJECT_SOURCE_DIR}/thirdparty/lib/mysqlcppconn)

add_executable(chatServer ${SRC_LIST} ${DB_LIST} ${DAO_LIST})

target_link_libraries(chatServer muduo_net muduo_base mysqlcppconn  mysqlclient    pthread)