recurse () {
	for type in ./* ; do
		if [ -d "$type" ]
		then
			cd "$type"
			recurse
			cd ..
		else
			gbbs.sh
		fi
	done
}

recurse
