# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "bebop_controller: 1 messages, 1 services")

set(MSG_I_FLAGS "-Ibebop_controller:/home/sunho/catkin_ws/src/bebop_controller/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(bebop_controller_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv" NAME_WE)
add_custom_target(_bebop_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "bebop_controller" "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv" ""
)

get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg" NAME_WE)
add_custom_target(_bebop_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "bebop_controller" "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(bebop_controller
  "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bebop_controller
)

### Generating Services
_generate_srv_cpp(bebop_controller
  "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bebop_controller
)

### Generating Module File
_generate_module_cpp(bebop_controller
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bebop_controller
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(bebop_controller_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(bebop_controller_generate_messages bebop_controller_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(bebop_controller_generate_messages_cpp _bebop_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg" NAME_WE)
add_dependencies(bebop_controller_generate_messages_cpp _bebop_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bebop_controller_gencpp)
add_dependencies(bebop_controller_gencpp bebop_controller_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bebop_controller_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(bebop_controller
  "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bebop_controller
)

### Generating Services
_generate_srv_lisp(bebop_controller
  "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bebop_controller
)

### Generating Module File
_generate_module_lisp(bebop_controller
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bebop_controller
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(bebop_controller_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(bebop_controller_generate_messages bebop_controller_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(bebop_controller_generate_messages_lisp _bebop_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg" NAME_WE)
add_dependencies(bebop_controller_generate_messages_lisp _bebop_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bebop_controller_genlisp)
add_dependencies(bebop_controller_genlisp bebop_controller_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bebop_controller_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(bebop_controller
  "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bebop_controller
)

### Generating Services
_generate_srv_py(bebop_controller
  "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bebop_controller
)

### Generating Module File
_generate_module_py(bebop_controller
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bebop_controller
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(bebop_controller_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(bebop_controller_generate_messages bebop_controller_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(bebop_controller_generate_messages_py _bebop_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/sunho/catkin_ws/src/bebop_controller/msg/Num.msg" NAME_WE)
add_dependencies(bebop_controller_generate_messages_py _bebop_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bebop_controller_genpy)
add_dependencies(bebop_controller_genpy bebop_controller_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bebop_controller_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bebop_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bebop_controller
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(bebop_controller_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bebop_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bebop_controller
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(bebop_controller_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bebop_controller)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bebop_controller\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bebop_controller
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(bebop_controller_generate_messages_py std_msgs_generate_messages_py)
