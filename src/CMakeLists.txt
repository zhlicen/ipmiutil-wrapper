# <license_header>
# Copyright (c) Celestica Inc. 2017
# </license_header>


add_subdirectory(wrapper/ipmi)

add_library(ipmiutil-wrapper STATIC 
	$<TARGET_OBJECTS:ipmiutil-wrapper-ipmi>
)

install(TARGETS ipmiutil-wrapper
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
