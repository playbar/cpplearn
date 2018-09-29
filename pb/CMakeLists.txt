# protobuf version 2.5.0
#
add_library(protobuflib STATIC
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/io/coded_stream.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/io/tokenizer.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/io/zero_copy_stream.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/io/zero_copy_stream_impl.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/io/zero_copy_stream_impl_lite.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/stubs/common.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/stubs/once.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/stubs/strutil.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/stubs/substitute.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/stubs/stringprintf.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/stubs/structurally_valid.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/descriptor.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/descriptor.pb.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/descriptor_database.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/dynamic_message.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/extension_set.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/extension_set_heavy.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/generated_message_reflection.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/generated_message_util.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/message.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/message_lite.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/reflection_ops.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/repeated_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/service.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/text_format.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/unknown_field_set.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/wire_format.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/wire_format_lite.cc
            )

target_include_directories(protobuflib PRIVATE
                          ${CMAKE_CURRENT_SOURCE_DIR}
		)
####
add_library(libprotoc STATIC
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/code_generator.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/command_line_interface.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/importer.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/parser.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/plugin.pb.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/subprocess.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/zip_writer.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_enum.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_enum_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_extension.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_field.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_file.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_generator.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_helpers.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_message.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_message_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_primitive_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_service.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/cpp/cpp_string_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_doc_comment.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_enum.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_enum_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_extension.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_file.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_generator.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_helpers.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_message.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_message_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_primitive_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_service.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/java/java_string_field.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/python/python_generator.cc
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/io/printer.cc
		)

target_include_directories(libprotoc PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/
		)
########

set(protoc_files
		${CMAKE_CURRENT_SOURCE_DIR}/google/protobuf/compiler/main.cc
		)

add_executable(protoc ${protoc_files})
target_link_libraries(protoc protobuflib libprotoc)
target_include_directories(protoc PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR})


########
set(data_write_SRCS
		data_write.cc
		data.pb.cc)
add_executable(data_write ${data_write_SRCS})
target_include_directories(data_write  PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(data_write protobuflib)


set(data_read_SRCS
		data_read.cc
		data.pb.cc)
add_executable(data_read ${data_read_SRCS})
target_include_directories(data_read  PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(data_read protobuflib)
