MESSAGE=$1

if [ -z "$MESSAGE" ]
then
	echo "No Commit Message Provided!"
	echo "Exiting..."
else
	cd linear-algebra-notes
	git checkout master
	git pull
	cd ..
	git add .
	git commit -m "$MESSAGE"
	git push
fi
