add_library(ui "Button.h" "Button.cpp" "UIScript.h" "UIScript.cpp" 
"UIScriptTypes.h" "UIScriptTypes.cpp" 
"UIScriptMethods.h" "UIScriptMethods.cpp" 
"Slider.h" "Slider.cpp" 
"UIHelperScripts.h" "UIHelperScripts.cpp"
"UIElement.h" "UIElement.cpp"
"ShaderTimer.h" "ShaderTimer.cpp" "Timer.h" "Timer.cpp")

set(LINUX_EXTRA_LIBS "")
if(UNIX)
	set(LINUX_EXTRA_LIBS "dl")
endif()

target_link_libraries(ui graphics drawables engine lua ${LINUX_EXTRA_LIBS} )