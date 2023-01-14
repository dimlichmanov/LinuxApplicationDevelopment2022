cmake_minimum_required(VERSION 3.16)
project(I18n C)
set(PROJECT_NAME bhello)

# Setting up Internationalisation (i18n)
find_package (Intl REQUIRED)
if (Intl_FOUND)
    message(STATUS "Internationalization (i18n) found:")
    message(STATUS " INTL_INCLUDE_DIRS: ${Intl_INCLUDE_DIRS}")
    message(STATUS " INTL_LIBRARIES: ${Intl_LIBRARIES}")
    message(STATUS " Version: ${Intl_VERSION}")
    include_directories(${Intl_INCLUDE_DIRS})
    link_directories(${Intl_LIBRARY_DIRS})
else ()
    message(STATUS "Internationalization (i18n) Not found!")
endif ()

find_package(Gettext REQUIRED)
if (Gettext_FOUND)
    message(STATUS "Gettext found:")
    message(STATUS " Version: ${GETTEXT_VERSION_STRING}")
else ()
    message(STATUS "Gettext Not found!")
endif ()

add_executable(bhello bhello.c)
target_compile_definitions(bhello PRIVATE LOCALE_PATH="${CMAKE_SOURCE_DIR}/po/")

find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext)
find_program(GETTEXT_MSGMERGE_EXECUTABLE msgmerge)
find_program(GETTEXT_MSGFMT_EXECUTABLE msgfmt)

if (GETTEXT_XGETTEXT_EXECUTABLE)
    message(STATUS " xgettext: ${GETTEXT_XGETTEXT_EXECUTABLE}")
    file(GLOB_RECURSE C_FILES RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/*.c)
    add_custom_target(
            pot-update
            COMMENT "pot-update: Done."
    )
    add_custom_command(
            TARGET pot-update
            PRE_BUILD
            COMMAND
            ${GETTEXT_XGETTEXT_EXECUTABLE}
            --from-code=utf-8
            --c++
            --force-po
            --output=${CMAKE_SOURCE_DIR}/po/${PROJECT_NAME}.pot
            --keyword=_
            --width=80
            ${C_FILES}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "pot-update: Pot file generated: ${CMAKE_SOURCE_DIR}/po/${PROJECT_NAME}.pot"
    )

endif (GETTEXT_XGETTEXT_EXECUTABLE)

if (GETTEXT_MSGMERGE_EXECUTABLE)

    message(STATUS " msgmerge: ${GETTEXT_MSGMERGE_EXECUTABLE}")

    add_custom_target(
            pot-merge
            COMMENT "pot-merge: Done."
            DEPENDS ${CMAKE_SOURCE_DIR}/po/${PROJECT_NAME}.pot
    )

    file(GLOB PO_FILE ${CMAKE_SOURCE_DIR}/po/ru/${PROJECT_NAME}.po)

    add_custom_command(
            TARGET pot-merge
            PRE_BUILD
            COMMAND
            ${GETTEXT_MSGMERGE_EXECUTABLE} ${PO_FILE}
            ${CMAKE_SOURCE_DIR}/po/${PROJECT_NAME}.pot
            COMMENT "pot-merge: ${PO_FILE}"
    )

endif (GETTEXT_MSGMERGE_EXECUTABLE)

if (GETTEXT_MSGFMT_EXECUTABLE)

    message(STATUS " msgmerge: ${GETTEXT_MSGFMT_EXECUTABLE}")

    add_custom_target(
            po-compile
            COMMENT "po-compile: Done."
    )

    add_custom_command(
            TARGET po-compile
            PRE_BUILD
            COMMAND
            ${GETTEXT_MSGFMT_EXECUTABLE}
            --output-file=./LC_MESSAGES/${PROJECT_NAME}.mo
            ${PROJECT_NAME}.po
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/po/ru
            COMMENT "po-compile: ru ${PROJECT_NAME}.mo"
    )

endif (GETTEXT_MSGFMT_EXECUTABLE)

add_custom_target(
        po-clean
        COMMENT "po-clean: Done."
)

add_custom_command(
        TARGET po-clean
        COMMAND
        rm -f
        po/ru/LC_MESSAGES/${PROJECT_NAME}.mo
        po/${PROJECT_NAME}.pot
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "deleting mo-file and pot-file"
)
