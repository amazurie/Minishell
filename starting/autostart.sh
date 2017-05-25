inquire ()  {
	echo  "$1 [y/n]? "
	read answer
	finish="-1"
	while [ "$finish" = '-1' ]
	do
		finish="1"
		if [ "$answer" = '' ];
		then
			answer=""
		else
			case $answer in
				y | Y | yes | YES ) return 0;;
			n | N | no | NO ) return 1;;
		*) finish="-1";
			read answer;;
	esac
fi
done
}

echo "\033[0;36m"
cat starting/name
echo "\033[0m"
echo "Thanks for testing my minishell !"
echo "\033[31mThis is a simple shell like\033[0m"
echo "\033[31mPlease, I try to learn.
I'm not just an inconvenience you need to pass through even this is boring you\033[0m"
if inquire "would you like to clean temporary file ?"; then
	make clean
fi
echo "minishell is ready to launch"
