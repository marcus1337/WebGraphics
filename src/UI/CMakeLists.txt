add_library(ui "Script/UIScript.h" "Script/UIScript.cpp" 
"Script/UIScriptTypes.h" "Script/UIScriptTypes.cpp" 
"Script/UIScriptMethods.h" "Script/UIScriptMethods.cpp" 
"Script/UIHelperScripts.h" "Script/UIHelperScripts.cpp"
"Script/UITypes.h" "Script/UITypes.cpp" 
"Script/DrawableTypes.h" "Script/DrawableTypes.cpp"

"Widgets/Button.h" "Widgets/Button.cpp" 
"Widgets/Slider.h" "Widgets/Slider.cpp" 
"Widgets/UIElement.h" "Widgets/UIElement.cpp"

"ShaderTimer.h" "ShaderTimer.cpp" 
"Timer.h" "Timer.cpp" )

set(LINUX_EXTRA_LIBS "")
if(UNIX)
	set(LINUX_EXTRA_LIBS "dl")
endif()

target_link_libraries(ui graphics drawables engine lua ${LINUX_EXTRA_LIBS} )