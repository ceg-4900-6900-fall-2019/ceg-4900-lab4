# Privilege Escalation

### Introduction


### Background


### Resources
* [`/code`](../blob/master/code/)
* [AWS educate (Login link)](https://www.awseducate.com/signin/SiteLogin)
* [AWS Build link](https://console.aws.amazon.com/cloudformation/home?region=us-east-1#/stacks/new?stackName=CEG-4900Lab02&templateURL=https:%2F%2Fs3.amazonaws.com%2Fwsu-cecs-cf-templates%2Fceg4900lab1.yml)


## Linux Privilege Escalation

### Task 1 - Enter the dragon
For this lab I have configured a special linux vm.  You can use your usual 
method of signing in via the `ubuntu` user and the ssh key specified when
you created the AWS instance.

Instead use the SSH key in this repository: [/code/first.key](../blob/master/code/first.key)
along with the user named `first` on your Ubuntu Public instance. Note you may
need to `chmod 600 first.key`.

To start with, the first user does not have any sort of special permissions.
For much of this lab you will be performing some basic enumeration on the system
in order to gain elevated privileges.

In the home directory of the user `first` is a file named `example-setuid`  This
file has some special permissions set on it.  An `ls -l` gives us the following:
```
-rwsr-xr-x 1 root root 8304 Apr  9 02:08 example-setuid
```
1. What is special about these file permissions?
2. Using `ltrace` what can you determine that this executable does?
3. Which ssh is this executable calling?  Can you effect that in any way?
4. Add `.` to your path with the following commands: 
```
PATH=PATH=.:${PATH}
export PATH
echo $PATH
```
   Now you just need to replace ssh.  If you create an executable file in the
   same directory (`/home/first/`) and name it SSH, your setuid file should now
   call it instead of `/usr/bin/ssh`.  Create an executable that will give you
   root access and document your process.  Execute `ssh-lolit` and demonstrate
   that your malicious `ssh` executable gives you root access.

### Task 2 - Finding more setuid
`find / -perm +4000 -user root -type f -print` will find all files on the system
that have the setuid bit AND are owned by root.  Go ahead and run it, its worth
noting that there are a good number of these types of files by default.  On this
server there are two notable programs with setuid bit set and owned by root,
`find` and `vim.basic`.
1. Using `find` with the `-exec` option, develop a find command that will give
   you elevated privileges.  Document your command here and explain how it
   works.
2. `vim.basic` having setuid is bad.  Using your elevated vim powers find a
   file to edit that would give you root.  Document which file you chose,
   what you changed, and how that would give you more privileges.

### Task 3 - Cron

[linux privilege escalation](https://blog.g0tmi1k.com/2011/08/basic-linux-privilege-escalation/)
[linux enumeration](https://www.rebootuser.com/?p=1623)
[payatu linux privilege escalation](https://payatu.com/guide-linux-privilege-escalation/)

## Task 2 - Windows Privilege Escalation





[riccardoancarani](https://www.riccardoancarani.it/exploting-setuid-setgid-binaries/)

