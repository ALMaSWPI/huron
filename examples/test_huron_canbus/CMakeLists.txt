add_executable(send_msg send_msg.cc)
add_executable(read_msg read_msg.cc)
add_executable(msg_conversion msg_conversion.cc)

target_link_libraries(send_msg
    PUBLIC
    mumei::mumei
)

target_link_libraries(read_msg
    PUBLIC
    mumei::mumei
)

target_link_libraries(msg_conversion
    PUBLIC
    mumei::mumei
)
