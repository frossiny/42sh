import subprocess
import os
import sys

def execute_test(command, fi):
	global show
	print("----- ", fi, ": ", end='')

	before_test = ("").encode("UTF-8")
	if (os.path.exists("./tests/python_test/before_test.err")):
		before_test = open("./tests/python_test/before_test.err", "r").read().encode("UTF-8")
	else:
		print("need ./tests/python_test/before_test.err")
		exit()

	proc = subprocess.Popen("./42sh", stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)
	proc.stdin.write(before_test)
	proc.stdin.write(command)
	proc_stdout = proc.communicate()
	proc_value = proc.returncode

	shell = subprocess.Popen("bash --posix", stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE, shell=True)
	shell.stdin.write(before_test)
	shell.stdin.write(command)
	shell_stdout = shell.communicate()
	shell_value = shell.returncode

	proc_stderr = proc_stdout[1].decode()
	shell_stderr = shell_stdout[1].decode()
	shell_stderr = shell_stderr.replace("bash", "42sh")
	while "line" in shell_stderr:
		index = shell_stderr.find("line")
		if len(shell_stderr) > index:
			index_end = index + 5
			while shell_stderr[index_end].isdigit():
				index_end = index_end + 1
			shell_stderr = shell_stderr[0 : index] + shell_stderr[index_end + 2:]

	if shell_stdout[0] != proc_stdout[0] or shell_value != proc_value or proc_stderr != shell_stderr:
		print("\033[31m[ERROR]\033[0m")
	else:
		print("\033[32m[OK]\033[0m")
	if shell_stdout[0] != proc_stdout[0] or shell_value != proc_value or proc_stderr != shell_stderr or show:
		print("\033[35mcommand :\033[0m\n", command.decode())
	if shell_stdout[0] != proc_stdout[0] or show:
		print("\033[33m42sh stdout -> \033[0m")
		print(proc_stdout[0].decode())
		print("\033[33mbash stdout -> \033[0m")
		print(shell_stdout[0].decode())
	if proc_stderr != shell_stderr or show:
		print("\033[33m42sh stderr -> \033[0m")
		print(proc_stderr)
		print("\033[33mbash stderr -> \033[0m")
		print(shell_stdout[1].decode())
	if shell_value != proc_value or show:
		print("\033[33m42sh returncode -> \033[0m", proc_value)
		print("\033[33mbash returncode -> \033[0m", shell_value)

argc = 0
show = 0
for arg in sys.argv:
	if arg == "SHOW":
		show = 1
	argc = argc + 1
if argc < 2:
	for r, d, f in os.walk("./tests/python_test"):
		for file in f:
			if ".t" in file and ".swp" not in file:
				with open(os.path.join(r, file), "r") as content_file:
					command = content_file.read().encode("UTF-8")
					execute_test(command, os.path.join(r, file))
else:
	for arg in sys.argv:
		if ".t" in arg and ".swp" not in arg:
			i = 0
			with open(arg, "r") as content_file:
				command = content_file.read().encode("UTF-8")
				execute_test(command, arg)
		elif os.path.exists(arg):
			for r, d, f in os.walk(arg):
				for file in f:
					if ".t" in file and ".swp" not in file:
						with open(os.path.join(r, file), "r") as content_file:
							command = content_file.read().encode("UTF-8")
							execute_test(command, os.path.join(r, file))
