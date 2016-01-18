if [ -z "$1" ]
then
	echo "No File Provided."
else
	lualatex --shell-escape "$1"
	bibtex $(basename $1 .tex)
	lualatex --shell-escape "$1"
fi
