IF(OBD_ENABLE_DBUS)
	SET(OBD_SIMGEN_DBUS "On" CACHE BOOL "Enable DBUS obdsim generator")
	IF(OBD_SIMGEN_DBUS)
		FILE(GLOB OBDSIMGEN_DBUS_SRCS
			generators/dbus/*.c
		)
		ADD_LIBRARY(ckobdsim_dbus STATIC ${OBDSIMGEN_DBUS_SRCS})
		SET(GENERATOR_LIBS ${GENERATOR_LIBS} ckobdsim_dbus ${DBUS_LIBRARY})
		ADD_DEFINITIONS(-DOBDSIMGEN_DBUS)
	ENDIF(OBD_SIMGEN_DBUS)

	INSTALL(FILES ${OBDGPSLogger_SOURCE_DIR}/man/man5/obdsim-dbus.5
		DESTINATION share/man/man5)

ENDIF(OBD_ENABLE_DBUS)

