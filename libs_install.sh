GREEN='\033[0;32m'
PURPLE='\033[0;35m'
BOLD='\033[1m'
NBOLD='\033[22m'
BLUE='\033[0;34m'
NORMAL='\033[0m'
LIB1=glfw
LIB2=glew
LIB3=glm
brew list ${LIB1} > /dev/null
if [ $? -eq 0 ]
then
	echo "${GREEN}Library ${LIB1} is installed (*≧ω≦*)${PURPLE}"
else
	brew install ${LIB1} > /dev/null
	echo "${PURPLE}Library not installed ¯\_(ツ)_/¯" >&2
	echo "${BLUE}Installing now..."
	if [ $? -eq 0 ]
		then
		echo "${BOLD}${GREEN}Library ${LIB1} is installed successfully(*≧ω≦*)${NBOLD}${PURPLE}"
		else
		echo "${PURPLE}An error has occurred ¯\_(ツ)_/¯" >&2
	fi	
fi
brew list ${LIB2} > /dev/null
if [ $? -eq 0 ]
then
  echo "${GREEN}Library ${LIB2} is installed (*≧ω≦*)${PURPLE}"
else
	brew install ${LIB2} > /dev/null
	echo "${PURPLE}Library not installed ¯\_(ツ)_/¯" >&2
	echo "${BLUE}Installing now..."
	if [ $? -eq 0 ]
		then
		echo "${BOLD}${GREEN}Library ${LIB2} is installed successfully(*≧ω≦*)${NDOLD}${PURPLE}"
		else
		echo "${PURPLE}An error has occurred ¯\_(ツ)_/¯" >&2
	fi	
fi
brew list ${LIB3} > /dev/null
if [ $? -eq 0 ]
then
  echo "${GREEN}Library ${LIB3} is installed (*≧ω≦*)${PURPLE}"
else
  brew install ${LIB3} > /dev/null
  echo "${PURPLE}Library not installed ¯\_(ツ)_/¯" >&2
	echo "${BLUE}Installing now..."
	if [ $? -eq 0 ]
		then
		echo "${BOLD}${GREEN}Library ${LIB3} is installed successfully(*≧ω≦*)${PURPLE}${NBOLD}"
		else
		echo "${PURPLE}An error has occurred ¯\_(ツ)_/¯${NORMAL}" >&2
	fi	
fi
