recurse () {
	for type in ./* ; do
		if [ -d "$type" ]
		then
			cd "$type"
			recurse
			cd ..
		else
			gbbs
		fi
	done
}

recurse
