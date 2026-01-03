alias c='g++ -Wall -Wconversion -Wextra -Wfatal-errors -g -std=c++20 \
	-fsanitize=undefined,address -D_GLIBCXX_DEBUG'
xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>
