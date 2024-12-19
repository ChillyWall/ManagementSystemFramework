# 添加一个executable target 名叫demo(最后cmake将东西输出到一个名叫demo的文件里)
add_executable(demo src/demo.cpp)
# 添加include文件夹到demo的头文件搜索目录（作用是cmake生成的文件找到库文件？）
target_include_directories(demo PUBLIC include)
# 链接库demo_lib
target_link_libraries(demo PUBLIC demolib)

install(TARGETS demo)