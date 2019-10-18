import subprocess
import os 
import sys 

i = 0
def execute_test(command, fi):
	global i
	print("----- ", fi, ": ", end='')
	proc = subprocess.Popen("../42sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
	proc.stdin.write(command)
	proc_stdout = proc.communicate()
	proc_value = proc.returncode

	shell = subprocess.Popen("/bin/bash", stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
	shell.stdin.write(command)
	shell_stdout = shell.communicate()
	shell_value = shell.returncode

	if shell_stdout != proc_stdout or shell_value != proc_value:
		print("\033[31m[ERROR]\033[0m")
		print("\033[35mcommand : \033[0m", command.decode())
		i = i + 1
		if shell_stdout[0] != proc_stdout[0]:
			print("\033[33m42sh stdout -> \033[0m")
			print(proc_stdout[0].decode())
			print("\033[33mbash stdout -> \033[0m")
			print(shell_stdout[0].decode())
		if shell_stdout[1] != proc_stdout[1]:
			print("\033[33m42sh stderr -> \033[0m")
			print(proc_stdout[1].decode())
			print("\033[33mbash stderr -> \033[0m")
			print(shell_stdout[1].decode())
		if shell_value != proc_value:
			print("\033[33m42sh returncode -> \033[0m", proc_value)
			print("\033[33mbash returncode -> \033[0m", shell_value)
	if i == 0:
		print("\033[32m[OK]\033[0m")

argc = 0
for arg in sys.argv:
	argc = argc + 1
if argc < 2:
	for r, d, f in os.walk("./tests"):
		for file in f:
			if ".t" in file:
				i = 0
				with open(os.path.join(r, file), "r") as content_file:
					command = content_file.read().encode("UTF-8")
					execute_test(command, file)
else:
	for arg in sys.argv:
		if ".t" in arg:
			i = 0
			with open(arg, "r") as content_file:
				command = content_file.read().encode("UTF-8")
				execute_test(command, arg)
		elif os.path.exists(arg):
			for r, d, f in os.walk(arg):
				for file in f:
					if ".t" in file:
						i = 0
						with open(os.path.join(r, file), "r") as content_file:
							command = content_file.read().encode("UTF-8")
							execute_test(command, file)
