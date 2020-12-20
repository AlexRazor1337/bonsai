# bonsai
This is really simple resource monitor for unix systems written on C using curses library.
Currently it shows CPU utilization, RAM usage and current time.
## How to use

1. Clone or download this repository.
2. Run Makefile:
  ```make```  
3. Run the binary: ```./bonsai```  


<p align="center">
  <img src="https://user-images.githubusercontent.com/26604491/102709816-73403180-42b6-11eb-8b2e-963a81a6b651.png" />
</p>

**Note:** you actually can change ASCII image to your own. For this just change the content of the "bs" file. Default one has date and time in the pot, for your custom image find a place where you want it to be and put "%s" here. Also, watch out for special formating characters (e.g no "random %" or "\n" in image). 

The goal of this little project is to practice with curses library, system interaction and 4coder text editor(although 4coder project files are not included here).
