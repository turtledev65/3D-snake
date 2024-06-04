#!/bin/bash

_usage(){
cat <<- EOF
Usage: ./setup.sh PROJECT_NAME

OPTION:
  init   This use the PROJECT_NAME as the folder name

EOF
}

_setup() {
	OLD_NAME="opengl-c-template"

	echo "Change CMakeLists.txt"
	sed -i -e "s/$OLD_NAME/$1/g" ./CMakeLists.txt

	echo "Change main.c"
	sed -i -e "s/$OLD_NAME/$1/g" ./src/main.c

	echo "Change README.md"
	sed -i -e "s/$OLD_NAME/$1/g" ./README.md

	echo "Clean git repository"
	rm -rf .git LICENSE REAMDE.md

}

if [[ "$1" == "" ]]; then
	_usage
	exit 1
fi

case $1 in
	"-h")
		_usage
		;;
	"--help")
		_usage
		;;
	*)
		if [[ $1 == "init" ]]; then
			NAME=${PWD##*/}
		else
			NAME=$1
		fi
		NAME=$(echo $NAME | sed -e 's/\(.*\)/\L\1/' | sed -e 's/ /-/g')
		echo -e "\033[44mChage project name to: $NAME\033[0m"
		_setup "$NAME"
		echo -e "\033[44mFinished; Rememder to add a LICENCE to your project!\033[0m"
		;;
esac
