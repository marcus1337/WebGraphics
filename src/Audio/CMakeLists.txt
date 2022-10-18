file(GLOB soloud_SRC
     "soloud/*.h"
     "soloud/*.cpp"
	 "soloud/audiosource/speech/*.h"
     "soloud/audiosource/speech/*.cpp"
	 "soloud/audiosource/wav/*.h"
     "soloud/audiosource/wav/*.cpp"
	 "soloud/audiosource/wav/*.c"
	 "soloud/filter/*.h"
     "soloud/filter/*.cpp"
)

add_library(audio "Audio.h" "Audio.cpp" ${soloud_SRC} "SoloudAudio.h" "SoloudAudio.cpp")

