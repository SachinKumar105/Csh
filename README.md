# Csh
A Linux shell, implemented in C
This is a guide for the C shell.

All the source code is written in a single C file "shell.c".

IMPORTANT:
        I've used readline library in my coded.So, readline library should be installed.Open terminal and type following command
 ```
 sudo apt-get install libreadline-dev
```

Guide for Specifications.

Specification 1: Display requirement  

- For every prompt,the prompt line starts with the following form
        <username@system_name:curr_dir   
- For this I've used utsbuf struct (in display() function) and for the curr_dir,
        I've took the link from /proc/<pid>/exe and made it into "~".  
- If the curr_diris in the ~ branch the curr_dir is printed as relative path with respect to ~.But if the curr_dir is not in the ~ branch,the absolute path is shown.  
        
Specification 2: Builtin commands  
        
- Here we talk about only pwd,cd & echo commands.  
- There can be any number of spaces between the arguements of any command.  
- Flags for the above three commands are not allowed.  
- Every command has been hard-coded. 
    
Specification 3: ls command  

- It works similar(almost) to the actual ls command.  

Specification 4: System commands with and without arguments  

- To run a process in foreground, type the command normally.  
- To run a process in background, tpye the command and type & and then press Enter.  
- Any flags can be used.  

Specification 5: pinfo command (user defined)  

- To know info of the running C shell, Just type pinfo.  
- To know info of a process with known pid, type pinfo and then pid.  

Specification 6: Finished Background Processes  

- After any background process ends,it shows the exit status and print it on stderr.  

Bonus Specification
    history
    
- This is inbuilt function in readline library.
- It prints the last 10(without -n flag) commands in the present C shell.
- If mentioned with -n flag, it prints the last n commands(n<20).
- Once the shell is closed, the history is flushed.

How to run the C shell.
    Run the following commands.
    
      ```
        make
        ./shell
      ```
      
How to use the C shell.
- As the shell prompts, type the commands with flags, options and arguements.
- Now press Enter.
- The command will be executed.
