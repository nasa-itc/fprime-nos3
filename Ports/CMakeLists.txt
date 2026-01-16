# Include project-wide components here

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ADCSports.fpp"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

set(MOD_DEPS
    ${ITC_Common_LIBRARIES}
    ${NOSENGINE_LIBRARIES}
)

register_fprime_module()