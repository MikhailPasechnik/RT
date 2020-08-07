GREEN='\033[0;32m'
PURPLE='\033[0;35m'
BOLD='\033[1m'
NBOLD='\033[22m'
BLUE='\033[0;34m'
NORMAL='\033[0m'
BREW=Homebrew
LIB_1=SDL2
LIB_2=glfw
LIB_3=glew
brew list > /dev/null
if [ $? -eq 0 ]
then
	echo "${GREEN}${BREW} already installed (*≧ω≦*)${NORMAL}"
else
	echo "${PURPLE}${BREW} not installed ¯\_(ツ)_/¯" >&2
	echo "${BLUE}Installing now..."
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	if [ $? -eq 0 ]
		then
			echo "${BOLD}${GREEN}${BREW} installed successfully(*≧ω≦*)${NBOLD}${PURPLE}"
		else
			echo "${PURPLE}An error has occurred ¯\_(ツ)_/¯" >&2
	fi	
fi
brew list ${LIB_1} > /dev/null
if [ $? -eq 0 ]
then
	echo "${GREEN}Library ${LIB_1} already installed (*≧ω≦*)${NORMAL}"
else
	echo "${PURPLE}Library ${LIB_1} not installed ¯\_(ツ)_/¯" >&2
	echo "${BLUE}Installing now..."
	brew install ${LIB_1} > /dev/null
	if [ $? -eq 0 ]
		then
			echo "${BOLD}${GREEN}Library ${LIB_1} installed successfully(*≧ω≦*)${NBOLD}${PURPLE}"
		else
			echo "${PURPLE}An error has occurred ¯\_(ツ)_/¯" >&2
	fi	
fi
brew list ${LIB_2} > /dev/null
if [ $? -eq 0 ]
then
	echo "${GREEN}Library ${LIB_2} already installed (*≧ω≦*)${NORMAL}"
else
	echo "${PURPLE}Library ${LIB_2} not installed ¯\_(ツ)_/¯" >&2
	echo "${BLUE}Installing now..."
	brew install ${LIB_2} > /dev/null
	if [ $? -eq 0 ]
		then
			echo "${BOLD}${GREEN}Library ${LIB_2} installed successfully(*≧ω≦*)${NBOLD}${PURPLE}"
		else
			echo "${PURPLE}An error has occurred ¯\_(ツ)_/¯" >&2
	fi	
fi
brew list ${LIB_3} > /dev/null
if [ $? -eq 0 ]
then
  echo "${GREEN}Library ${LIB_3} already installed (*≧ω≦*)${NORMAL}"
else
	echo "${PURPLE}Library ${LIB_3} not installed ¯\_(ツ)_/¯" >&2
	echo "${BLUE}Installing now..."
	brew install ${LIB_3} > /dev/null
	if [ $? -eq 0 ]
		then
			echo "${BOLD}${GREEN}Library ${LIB_3} installed successfully(*≧ω≦*)${NDOLD}${PURPLE}"
		else
			echo "${PURPLE}An error has occurred ¯\_(ツ)_/¯${NORMAL}" >&2
	fi	
fi