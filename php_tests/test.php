<?php

if ($handle = opendir('.'))
{
	while (false !== ($entry = readdir($handle)))
	{
		$exp = explode('.', $entry);
		if ($exp[count($exp) - 1] != "test")
			continue;

		exec("../42sh < " . $entry . " > stdin_42sh.log 2> stderr_42sh.log");
		exec("bash < " . $entry . " > stdin_bash.log 2> stderr_bash.log");
		if (sha1(file_get_contents("stdin_42sh.log")) != sha1(file_get_contents("stdin_bash.log")))
		{
			file_put_contents("diff_stdin.log", "\nDIFF " . $entry . " STDIN\n", FILE_APPEND);
			exec("diff stdin_42sh.log stdin_bash.log >> diff_stdin.log");
			echo "\033[0;31m[KO]\033[0;0m " . $entry . " STDIN diff saved to diff_stdin.log\n";
		}
		else if (sha1(file_get_contents("stderr_42sh.log")) != sha1(file_get_contents("stderr_bash.log")))
		{
			file_put_contents("diff_stderr.log", "\nDIFF " . $entry . " STDERR\n", FILE_APPEND);
			exec("diff stderr_42sh.log stderr_bash.log >> diff_stderr.log");
			echo "\033[0;31m[KO]\033[0;0m " . $entry . " STDERR diff saved to diff_stderr.log\n";
		}
		else
			echo "\033[0;32m[OK]\033[0;0m " . $entry . "\n"; 
	}
	exec("rm -rf std*");
    closedir($handle);
}

?>