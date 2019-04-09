#  CEG 4900 Lab 4 - Privilege Escalation

### Introduction
From Wikipedia:

> Privilege escalation is the act of exploiting a bug, design flaw or 
> configuration oversight in an operating system or software application
> to gain elevated access to resources that are normally protected from an
> application or user. The result is that an application with more privileges
> than intended by the application developer or system administrator can 
> perform unauthorized actions. 

### Background
While there are many ways to gain some form of access to a system, its fairly
rare that an exploit immediately grants you (or the person hacking in) `root` or
other administrative access.  Typically you gain access as a low level system or
user and have to further enumerate through a system looking for vulnerabilities
or mis-configurations that you might use to further increase your privileges.

Typically this is not a single step process, but instead relies on a number of
vulnerabilities across a system.  For this lab we are trying to introduce
several of the more common avenues for escalation of privileges via a contrived
lab experience.  In the real world these avenues will still be useful but will
not be so easily exploited.

### Resources
* [`/code`](../blob/master/code/)
* [AWS educate (Login link)](https://www.awseducate.com/signin/SiteLogin)
* [AWS Build link](https://console.aws.amazon.com/cloudformation/home?region=us-east-1#/stacks/new?stackName=CEG-4900Lab04&templateURL=https:%2F%2Fs3.amazonaws.com%2Fwsu-cecs-cf-templates%2Fceg4900lab4.yml)

### Useful linux stuff:
* `/etc/shadow`
* `/etc/groups`
* `crontab`
* `/etc/sudoers`
* `visudo`


## Linux Privilege Escalation

### A note on this lab:
For this lab I have configured a special linux vm.  You can use your usual 
method of signing in via the `ubuntu` user and the ssh key specified when
you created the AWS instance.  I understand that this account gives you `sudo`
priveleges, and feel free to use these to skip around the lab if you get stuck,
but try not to use these privileges to "cheat" the question (or, if you do, explain
how you got stuck and what you did).

To start with, the first user does not have any sort of special permissions.
For much of this lab you will be performing some basic enumeration on the system
in order to gain elevated privileges.


### Task 1 - setuid
For task 1 please switch over to the `first` user using `sudo su first` and
`cd` to their home directory.

In the home directory of the user `first` is a file named `example-setuid`  This
file has some special permissions set on it.  An `ls -l` gives us the following:
```
-rwsr-xr-x 1 root root 8304 Apr  9 02:08 example-setuid
```
1. What is special about these file permissions?
2. Explain what setuid is.
3. Find a way to gain root priveleges using `example-setuid`.  Document your
   process here.

### Task 2 - Finding more setuid
It should be apparent that the above setuid program is pretty unlikely to be
found on a system.  Instead what you should be concerned about is finding what
other programs may have been (mis)configured with setuid privileges and how you
might exploit them.

For this Task switch to the user named `second` which also has no special
privileges on the system.

First we would need to find what other applications have the setuid bit set, and
to do that we would use find.
`find / -perm +4000 -user root -type f -print` will find all files on the system
that have the setuid bit AND are owned by root.  Go ahead and run it, its worth
noting that there are a good number of these types of files by default.  On this
server there are two notable programs with setuid bit set and owned by root,
`find` and `vim.basic`.  Both of these programs would typically NOT have setuid.

1. Using `find` with the `-exec` option, develop a find command that will give
   you elevated privileges.  Document your command here and explain how it
   works.
2. `vim.basic` having setuid is bad but the power this gives you may not be
   obvious.  Using your elevated vim powers find a file to edit that would give
   you root.  Document which file you chose, what you changed, and how that
   would give you more privileges.
3. What reasons might an administrator have for using setuid on an application?

### Task 3 - Cron
For this Task switch to the user named `third` which also has no special
privileges on the system.

Read up on what `cron` is for linux.

1. What is describe what `cron` does.
2. Cron tables for each user are typically kept in `/var/spool/cron/crontab/`.
   What users have cron tables on this system?
3. What are the contents of the root cron table?  How often do they run?
4. Investigate the first cron table entry.  What are the permissions on the 
   file specified?  What is it doing?
4. Use the first root cron job to escalate your privileges.  Describe all steps you
   took and how it elevates your privileges.
5. How would you prevent this escalation?

### Task 4 - Cron-tinued
I'm so sorry...  Anyways, switch to the user named `fourth` as we have been
doing for each task.  Now we are going to use the second root cron job to
escalate privileges.

1. The second crontable entry for root is NOT writable by everyone.  Without
   changing this file you are able to escalate privileges.  This has to do with
   how linux parses the `*` character in the command line.  Investigate and find
   a way to escalate privileges *without* editing the `/cron-scripts/logRotate`
2. How would you prevent this escalation?

### Task 5 - Poor paths
Using the user `fifth`, you will exploit another user's poor configuration.

Investigate the user `farmerjoe`.  Pay particular attention to his PATH
variable in his `~/.bashrc`.  It appears `farmerjoe` is a lazy admin and has
added the local directory `.` to his PATH.  Lets exploit this.

You have made an innocuous request to farmerjoe stating that you are having some
issues running an `ls` in your home directory.  Farmerjoe will definitely help
you by using `cd` to get into your directory and then running `sudo ls`.

1. Where will `farmerjoe`'s environment look for `ls` first?
2. Exploit this by creating a malicious `ls` program in this directory.  Upload
   this `ls` along with your submission with tar.gz.  Explain how your `ls`
   program gives you elevated privileges.
3. How would you prevent *this* escalation?

### Task 6 - More enumeration
**WITHOUT** using `sudo` or other elevated privileges, take a look at the
`sixth` user.

1. What `groups` are they a part of?
2. Use the data that is readable by everyone in `/home/sixth/` to gain access to
   their account.
3. How would you prevent this?

### Task 7 - Choose your own vulnerability
A huge part of privilege escalation in linux is enumeration.  There are a lot of
areas to inspect and you are simply looking for one vulnerability to exploit.  

Read through the following incomplete guides that cover enumeration of potential
means of privilege escalation.
* *[linux privilege escalation](https://blog.g0tmi1k.com/2011/08/basic-linux-privilege-escalation/)
* [linux enumeration](https://www.rebootuser.com/?p=1623)

Choose one command covered in the above (that we have not already gone over).
Answer the following:
1. What command did you choose?
2. What does the command do?
3. How is this useful for privilege escalation?
4. What misconfiguration is the command looking for (if any)?
5. How would you protect against this command or misconfiguration being used to
   elevate privilges on a system?


##### Special Thanks:
[riccardoancarani](https://www.riccardoancarani.it/exploting-setuid-setgid-binaries/)
[payatu linux privilege escalation](https://payatu.com/guide-linux-privilege-escalation/)

