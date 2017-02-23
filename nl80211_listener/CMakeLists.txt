# find libnl

INCLUDE(FindPkgConfig)

pkg_check_modules(LIBNL3 libnl-tiny)
if (NOT LIBNL3_FOUND)
    pkg_check_modules(LIBNL3 libnl-genl-3.0)
endif(NOT LIBNL3_FOUND)

if (LIBNL3_FOUND)
    include_directories(${LIBNL3_INCLUDE_DIRS})
    link_directories(${LIBNL3_LIBRARY_DIRS})

    # set library name
    SET (source nl80211_listener.c 
                nl80211_get_interface.c
                nl80211_get_wiphy.c
                nl80211_get_survey.c
                nl80211_get_mpp.c
                nl80211_get_station_dump.c
                genl_get_family.c)

    SET (include nl80211_listener.h)

    message(STATUS "Using '${LIBNL3_LIBRARIES}' for nl80211 access")

    # use generic plugin maker
    oonf_create_plugin("nl80211_listener" "${source}" "${include}" "${LIBNL3_LIBRARIES}")
ENDIF (LIBNL3_FOUND)
