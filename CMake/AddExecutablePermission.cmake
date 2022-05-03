if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
	math(EXPR length "${CMAKE_ARGC} - 1") # ${CMAKE_ARGC} - 1 is the exact number of arguments

	foreach (item RANGE 3 ${length})
			File (CHMOD_RECURSE
				${CMAKE_ARGV${item}}
				FILE_PERMISSIONS OWNER_EXECUTE OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
			)
	endforeach()
endif()