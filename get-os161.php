<?php

$name = posix_getpwuid(posix_geteuid());
$id = $name['name'];

$source = 'ftp://ftp.eecs.harvard.edu/pub/os161/os161-1.11.tar.gz';

//$homedir = '/home/'.$name;
$h=$name['dir'];
$homedir=$name['dir']; // .'/t1';

chdir($h);

print 'Home directory: '.$homedir."\n";

$d = implode(file($h.'/.bash_profile'));

$fail=true;

if (preg_match('/PATH=\$PATH:\$HOME\/bin/', $d) && !preg_match('/sys161/', $d)) {
	$d = str_replace('PATH=$PATH:$HOME/bin', 'PATH=$PATH:$HOME/bin:/usr/local/sys161:/usr/local/sys161/bin', $d);
	//print $d;
	
	$fp = fopen('.bash_profile', 'w');
	if ($fp === false) {
		print "Could not open .bash_profile.\n";
	} else {
		$w = fwrite($fp, $d);
		if ($w) {
			print "Edited .bash_profile.\n";
			$fail = false;
		} else {
			print "Failed to write .bash_profile.\n";
		}
		fclose($fp);
	}

} else {
	print "PATH is already correct.\n";
	$fail = false;
}

if ($fail) {
	print "\$PATH could not be set in .bash_profile.\n";
	print "You should edit it manually:\n";
	print "   Open ~/.bash_profile in a text editor.\n";
	print "   BEFORE the export command:\n";
	print "   Add PATH=\$PATH:/usr/local/sys161:/usr/local/sys161/bin\n";
	die();
}

// make directory
print 'Making os161 directory...'."\n";
if (!mkdir($homedir.'/os161', 0755)) {
	print 'Failed to make directory.'."\n";
}

print "Attempting to copy OS/161 source code.\n";
if (!copy($source, $homedir.'/os161/os161-1.11.tar.gz')) {
	print 'Failed to copy source archive.'."\n";
}

print "Decompressing source archive.\n";
shell_exec('tar -xzf '.$homedir.'/os161/os161-1.11.tar.gz -C '.$homedir.'/os161');

print "Acquired OS/161 Source tree in directory:\n";
print $homedir."/os161/os161-1.11/\n";

/*
print "Initial OS/161 configuration.\n";
$os161_dir = $homedir.'/os161/os161-1.11';

chdir($os161_dir);
print shell_exec('./configure --ostree='.$homedir.'/os161/root');

chdir($os161_dir.'/kern/conf/');
print shell_exec('./config ASST0');

print "OS/161 configuration complete.\n";
print "  Source directory: ".$os161_dir."\n";
print "  Kernel output directory: ".$homedir."/os161/root\n";
*/

?>
